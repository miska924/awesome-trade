#pragma once

#include <cstdlib>
#include <fstream>

#include <jsoncpp/json/json.h>
#include <markets/market.h>
#include <util/http/client.h>
#include <util/macros/macros.h>


Json::Value SaveToJson(
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
);

void SaveToFile(
    const std::string& outFile,
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
);

void PlotRecord(
    const std::string& outFile,
    size_t size,
    const std::vector<TCandle>& candles,
    const std::vector<std::pair<time_t, double>>& balances,
    const std::vector<std::pair<time_t, TOrder>>& orders
);

struct IRecorder {
    virtual void AddOrder(TOrder order) = 0;
    virtual void AddCandle(TCandle candle) = 0;
    virtual void AddBalance(double balance) = 0;
};

template<typename T>
concept Recorder = std::derived_from<T, IRecorder>;

struct TFakeRecorder : IRecorder {
    void AddOrder(TOrder order) { UNUSED(order); }
    void AddCandle(TCandle candle) { UNUSED(candle); }
    void AddBalance(double balance) { UNUSED(balance); }
};

struct TBaseRecorder : IRecorder {
    TBaseRecorder() = default;

    void AddOrder(TOrder order) override;
    void AddCandle(TCandle candle) override;
    void AddBalance(double balance) override;

    std::vector<std::pair<time_t, TOrder>> orders;
    std::vector<TCandle> candles;
    std::vector<std::pair<time_t, double>> balances;
};


struct TFileRecorder : TBaseRecorder {
    TFileRecorder(std::string outFile);
    ~TFileRecorder();

    std::string outFile;
};

struct TTelegramRecorder : IRecorder {
    TTelegramRecorder(const std::string& token, const std::string& chatId, size_t windowSize);

    void AddOrder(TOrder order) override;
    void AddCandle(TCandle candle) override;
    void AddBalance(double balance) override;

private:
    void SendTelegramMessage(const std::string& chatId, const std::string& message);
    void SendTelegramPicture(const std::string& chatId, const std::string& path, const std::string& message = "");

    TBaseRecorder recorder;
    std::string chatId;
    THttpClient client;
    size_t windowSize;
};
