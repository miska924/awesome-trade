#pragma once

#include <vector>
#include <array>
#include <map>

#include <markets/market.h>
#include <util/vector_view/vector_view.h>
#include <markets/recorders.h>


constexpr size_t MAX_INSTRUMENTS = 10;


std::vector<TCandle> GenerateCandles(size_t seed, size_t size);


template <Recorder TRecorder>
struct TBacktestInstrument : IInstrument {
    TBacktestInstrument(TRecorder&& recorder, TVectorView<TCandle> candles, size_t offset,double currency, double fee)
        : recorder(std::forward<TRecorder>(recorder))
        , candles(candles)
        , currency(currency)
        , fee(fee)
    {
        for (size_t i = 0; i < offset; ++i) {
            Update();
        }
    };

    TVectorView<TCandle> GetCandles() const override;

    void Order(TOrder order) override;

    int GetLots() const override;
    double GetCurrency() const override;

    bool Update() override;
    bool Finished() const override;

    TRecorder recorder;
private:
    TVectorView<TCandle> candles;
    int lots = 0;
    double currency = 0;
    size_t currentCandlesEnd = 0;
    double fee = 0;
};


class TBacktestMarket {
public:
    template <Recorder TRecorder>
    TBacktestInstrument<TRecorder> GetInstrument(
        TRecorder&& recorder,
        size_t seed,
        size_t size,
        size_t offset,
        double currency,
        double fee
    ) {
        for (size_t i = 0; i < instrumentsCount; ++i) {
            if (candles[i].first == seed) {
                return TBacktestInstrument<TRecorder>(
                    std::forward<TRecorder>(recorder),
                    candles[i].second,
                    offset,
                    currency,
                    fee
                );
            }
        }
        if (instrumentsCount == MAX_INSTRUMENTS) {
            throw std::runtime_error("Too many instruments");
        }
        candles[instrumentsCount] = std::make_pair(seed, GenerateCandles(seed, size));
        return TBacktestInstrument<TRecorder>(
            std::forward<TRecorder>(recorder),
            candles[instrumentsCount++].second,
            offset,
            currency,
            fee
        );
    }

private:
    std::array<std::pair<size_t, std::vector<TCandle>>, MAX_INSTRUMENTS> candles;
    size_t instrumentsCount = 0;
};


template <Recorder TRecorder>
TVectorView<TCandle> TBacktestInstrument<TRecorder>::GetCandles() const {
    return candles.SubView(0, currentCandlesEnd);
}

template <Recorder TRecorder>
void TBacktestInstrument<TRecorder>::Order(TOrder order) {
    if (currentCandlesEnd == 0) {
        std::runtime_error("Order for not started instrument");
    }
    double price = candles[currentCandlesEnd - 1].close;
    if (order.type == EOrderType::BUY) {
        lots += order.lots;
        currency -= price * (1.0 + fee) * order.lots;
    } else {
        lots -= order.lots;
        currency += price * (1.0 - fee) * order.lots;
    }

    recorder.AddOrder(order);
    recorder.AddBalance(currency + lots * price);
}

template <Recorder TRecorder>
int TBacktestInstrument<TRecorder>::GetLots() const {
    return lots;
}

template <Recorder TRecorder>
double TBacktestInstrument<TRecorder>::GetCurrency() const {
    return currency;
}

template <Recorder TRecorder>
bool TBacktestInstrument<TRecorder>::Update() {
    if (Finished()) {
        return false;
    }
    recorder.AddBalance(currency + lots * candles[currentCandlesEnd].close);
    recorder.AddCandle(candles[currentCandlesEnd++]);
    return true;
}

template <Recorder TRecorder>
bool TBacktestInstrument<TRecorder>::Finished() const {
    return currentCandlesEnd == candles.Size();
}
