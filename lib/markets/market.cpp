#include <markets/market.h>


std::string ToString(EOrderType type) {
    return type == EOrderType::BUY ? "BUY" : "SELL";
}

EOrderType operator!(EOrderType type) {
    return type == EOrderType::BUY ? EOrderType::SELL : EOrderType::BUY;
}

bool TCandle::operator==(const TCandle& other) const {
    return time == other.time && open == other.open && close == other.close && high == other.high && low == other.low && volume == other.volume;
}
