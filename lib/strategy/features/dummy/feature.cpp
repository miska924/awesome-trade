#include <strategy/features/dummy/feature.h>
#include <util/macros/macros.h>


TDummyFeature::TDummyFeature(const TParams& params) {
    UNUSED(params);
}

double TDummyFeature::operator()(TVectorView<TCandle> candles) const {
    if (candles.Size() == 0) {
        throw std::invalid_argument("empty candles");
    }
    return candles.Back().close;
}