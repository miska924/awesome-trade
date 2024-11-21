#pragma once

#include <util/vector_view/vector_view.h>

#include <markets/market.h>
#include <strategy/openers/opener.h>
#include <strategy/params/params.h>


class TDummyOpener : public IOpener {
public:
    TDummyOpener(const TParams& params);
    EOpenSignal Signal(TVectorView<TCandle> candles) override;
};
