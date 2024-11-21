#include <markets/market.h>


EOperationType operator!(EOperationType type) {
    return type == EOperationType::BUY ? EOperationType::SELL : EOperationType::BUY;
}

TOperation::TOperation(TInstrument& instrument, size_t lots, EOperationType type)
    : instrument(instrument)
    , lots(lots)
    , type(type) {}

TOperation TOperation::close() {
    TOperation operation(*this);
    operation.type = !type;
    return instrument.order(operation);
}

TOperation TInstrument::buy(size_t lots) {
    // market.buy(*this, lots);
    return TOperation(*this, lots, EOperationType::BUY);
}

TOperation TInstrument::sell(size_t lots) {
    // market.buy(*this, lots);
    return TOperation(*this, lots, EOperationType::SELL);
}

TOperation TInstrument::order(TOperation operation) {
    return operation;
}

bool TCandle::operator==(const TCandle& other) const {
    return time == other.time && open == other.open && close == other.close && high == other.high && low == other.low && volume == other.volume;
}
