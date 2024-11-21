#include <strategy/signals.h>

#include <stdexcept>


ESignal ESignalFrom(EOpenSignal signal) {
    switch (signal) {
        case EOpenSignal::BUY:
            return ESignal::OPEN_BUY;
        case EOpenSignal::SELL:
            return ESignal::OPEN_SELL;
        case EOpenSignal::NONE:
            return ESignal::NONE;
    }
    throw std::runtime_error("EOpenSignal -> ESignal conversion error");
}

ESignal ESignalFrom(ECloseSignal signal) {
    switch (signal) {
        case ECloseSignal::CLOSE:
            return ESignal::CLOSE;
        case ECloseSignal::NONE:
            return ESignal::NONE;
    }
    throw std::runtime_error("ECloseSignal -> ESignal conversion error");
}
