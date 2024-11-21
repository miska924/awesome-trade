#include <cpr/cpr.h>

#include <markets/recorders.h>


Json::Value SaveToJson(
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
) {
    Json::Value root;
    root["orders"] = Json::Value(Json::objectValue);
    root["orders"]["buy"] = Json::Value(Json::arrayValue);
    root["orders"]["sell"] = Json::Value(Json::arrayValue);
    root["candles"] = Json::Value(Json::arrayValue);
    for (auto& candle : candles) {
        Json::Value candleJson;
        candleJson["time"] = candle.time;
        candleJson["open"] = candle.open;
        candleJson["high"] = candle.high;
        candleJson["low"] = candle.low;
        candleJson["close"] = candle.close;
        candleJson["volume"] = candle.volume;
        root["candles"].append(candleJson);
    }
    for (auto& [i, balance] : balances) {
        Json::Value balanceJson;
        balanceJson["time"] = candles[i].time;
        balanceJson["balance"] = balance;
        root["balances"].append(balanceJson);
    }
    for (auto& [i, order] : orders) {
        Json::Value orderJson;
        orderJson["time"] = candles[i - 1].time;
        orderJson["type"] = ToString(order.type);
        orderJson["lots"] = order.lots;
        orderJson["price"] = candles[i - 1].close;
        if (order.type == EOrderType::BUY) {
            root["orders"]["buy"].append(orderJson);
        } else {
            root["orders"]["sell"].append(orderJson);
        }
    }
    return root;
}

void SaveToFile(
    const std::string& outFile,
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
) {
    std::ofstream file(outFile);
    Json::Value json = SaveToJson(candles, balances, orders);
    file << json.toStyledString();
}

void PlotRecord(
    const std::string& outFile,
    size_t size,
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
) {
    SaveToFile("tmp.json", candles, balances, orders);
    std::string command = "python3 lib/markets/visualize.py tmp.json " + outFile + " " + std::to_string(size);
    int retCode = std::system(command.c_str());

    if (retCode != 0) {
        throw std::runtime_error("Plotting command failed");
    }
}

TFileRecorder::TFileRecorder(std::string outFile): outFile(outFile) {}

TFileRecorder::~TFileRecorder() {
    SaveToFile(outFile, candles, balances, orders);
}

void TBaseRecorder::AddOrder(TOrder order) {
    if (candles.empty()) {
        throw std::runtime_error("Order for not started instrument");
    }
    orders.push_back({candles.size(), order});
}

void TBaseRecorder::AddCandle(TCandle candle) {
    candles.push_back(candle);
}

void TBaseRecorder::AddBalance(double balance) {
    balances.push_back({candles.size(), balance});
}


TTelegramRecorder::TTelegramRecorder(
    const std::string& token,
    const std::string& chatId,
    size_t windowSize
)
    : chatId(chatId)
    , client("https://api.telegram.org/bot" + token)
    , windowSize(windowSize)
{
    client.SetHeader("Content-Type", "application/json");
}

void TTelegramRecorder::SendTelegramMessage(
    const std::string& chatId,
    const std::string& message
) {
    Json::Value json;
    json["chat_id"] = chatId;
    json["text"] = message;

    client.Post(
        "/sendMessage",
        json
    );
}

void TTelegramRecorder::SendTelegramPicture(
    const std::string& chatId,
    const std::string& path,
    const std::string& message
) {
    client.RemoveHeader("Content-Type");
    cpr::Multipart multipart{
        {"chat_id", chatId},
        {"photo", cpr::File{path}},
        {"caption", message},
    };

    Json::Value result = client.PostMultipart("/sendPhoto", multipart);
    client.SetHeader("Content-Type", "application/json");
}

void TTelegramRecorder::AddOrder(TOrder order) {
    recorder.AddOrder(order);

    std::string message = "Order " + ToString(order.type)
        + " " + std::to_string(order.lots)
        + " at " + std::to_string(recorder.candles.back().close);

    PlotRecord("telegram.png", windowSize, recorder.candles, recorder.balances, recorder.orders);
    SendTelegramPicture(chatId, "telegram.png", message);
}

void TTelegramRecorder::AddCandle(TCandle candle) {
    recorder.AddCandle(candle);
}

void TTelegramRecorder::AddBalance(double balance) {
    recorder.AddBalance(balance);
}
