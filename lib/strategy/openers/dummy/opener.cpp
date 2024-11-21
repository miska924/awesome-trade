#include <strategy/openers/dummy/opener.h>
#include <util/macros/macros.h>


TDummyOpener::TDummyOpener(const TParams& params) {
    UNUSED(params);
}

EOpenSignal TDummyOpener::Signal(TVectorView<TCandle> candles) {
    UNUSED(candles);
    return EOpenSignal::BUY;
}
