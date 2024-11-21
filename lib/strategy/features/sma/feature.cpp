#include <strategy/features/sma/feature.h>

#include <util/vector_view/vector_view.h>


TNaiveSmaFeature::TNaiveSmaFeature(const TParams& params)
    : period(std::get<int>(params["period"])) {}

double TNaiveSmaFeature::operator()(TVectorView<TCandle> candles) const {
    size_t sz = candles.Size();
    if (sz < period) {
        throw std::invalid_argument("Not enough candles");
    }

    double sum = 0;
    for (size_t i = 0; i < period; ++i) {
        sum += (candles[sz - period + i].close);
    }

    return sum / period;
}
