#pragma once

#include <time.h>
#include <unordered_map>

#include <util/vector_view/vector_view.h>


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

enum class EOrderType {
    BUY,
    SELL,
};

EOrderType operator!(EOrderType type);

struct TOrder {
    EOrderType type;
    size_t lots;
};

std::string ToString(EOrderType type);

struct IInstrument {
    virtual int GetLots() const = 0;
    virtual TVectorView<TCandle> GetCandles() const = 0;
    virtual void Order(TOrder order) = 0;
    virtual bool Update() = 0;
    virtual bool Finished() const = 0;
    virtual double GetCurrency() const = 0;
};

template <typename T>
concept Instrument = std::derived_from<T, IInstrument>;
