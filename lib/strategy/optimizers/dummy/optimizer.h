#pragma once

#include <strategy/optimizers/optimizer.h>

class TDummyOptimizer : public IOptimizer {
public:
    ~TDummyOptimizer() override = default;
};
