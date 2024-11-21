#pragma once

#include <strategy/features/feature.h>


class TDummyFeature : public IFeature {
public:
    TDummyFeature(const TParams& params);
    double operator()(TVectorView<TCandle> candles) const override;
};
