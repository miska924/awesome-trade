#pragma once

#include <time.h>
#include <unordered_map>


struct TCandle {
    time_t time = 0;
    double open = 0;
    double close = 0;
    double high = 0;
    double low = 0;
    double volume = 0;
    bool full = true;
    bool operator==(const TCandle& other) const;
};

enum class EOperationType {
    BUY,
    SELL,
};

EOperationType operator!(EOperationType type);

class TInstrument;

class TOperation {
    friend struct TInstrument;
public:
    TOperation close();
private:
    TInstrument& instrument;
    size_t lots;
    EOperationType type;
    TOperation(TInstrument& instrument, size_t lots, EOperationType type);
};

class IMarket;

struct TInstrument {
    int lotSize;
    IMarket& market;

    TOperation buy(size_t lots);
    TOperation sell(size_t lots);
    TOperation order(TOperation operation);
};

struct Balance {
    double balance;
};

class IMarket {
public:
    virtual ~IMarket() = default;
    virtual TInstrument GetInstrument() = 0;
    virtual void buy(TInstrument& instrument, size_t lots) = 0;
    virtual void sell(TInstrument& instrument, size_t lots) = 0;
};


namespace std {
    template<>
    struct hash<TCandle> {
        size_t operator()(const TCandle& candle) const {
            size_t h1 = hash<time_t>()(candle.time);
            size_t h2 = hash<double>()(candle.open);
            size_t h3 = hash<double>()(candle.close);
            size_t h4 = hash<double>()(candle.high);
            size_t h5 = hash<double>()(candle.low);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4);
        }
    };
}
