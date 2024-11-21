#include <markets/backtest/market.h>

#include <iostream>
#include <vector>
#include <map>
#include <math.h>

#include <util/vector_view/vector_view.h>


std::vector<TCandle> GenerateCandles(size_t seed, size_t size) {
    std::srand(seed);
    std::vector<TCandle> candles;
    double prev = 1000;
    for (size_t i = 0; i < size; ++i) {
        double open = prev + static_cast<double>(std::rand() % 200 - 100) / 100;
        double close = open + static_cast<double>(std::rand() % 200 - 100) / 10;
        double high = std::max(open, close) + static_cast<double>(std::rand() % 100) / 10;
        double low = std::min(open, close) - static_cast<double>(std::rand() % 100) / 10;
        double volume = std::sqrt(static_cast<double>(std::rand() % 1000) / 10);

        prev = close;

        candles.emplace_back(
            static_cast<time_t>(i + 1), // time
            open,
            close,
            high,
            low,
            volume,
            true // full
        );
    }
    return candles;
}
