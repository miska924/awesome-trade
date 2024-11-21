#define DEBUG

#include <random>
#include <iostream>
#include <chrono>

#include <strategy/closers/cross/closer.h>
#include <strategy/features/sma/feature.h>
#include <strategy/openers/cross/opener.h>
#include <strategy/params/params.h>
#include <strategy/strategy.h>


using TNaiveStrat = TStrategy<TCrossOpener<TNaiveSmaFeature>, TCrossCloser<TNaiveSmaFeature>>;
using TSmartStrat = TStrategy<TCrossOpener<TSmaFeature<2>>, TCrossCloser<TSmaFeature<2>>>;

constexpr size_t ITERATIONS = 1000;
constexpr size_t CANDLES = 10000;

constexpr int FAST = 10;
constexpr int SLOW = 300;

template<Strategy TStrat>
uint64_t Duration(const std::vector<TCandle>& candlesVector, TStrat strategy) {
    auto start = std::chrono::high_resolution_clock::now();

    uint64_t result = 0;
    for (size_t i = 0; i < ITERATIONS; ++i) {
        if (ITERATIONS % std::max(1ul, ITERATIONS / 100) == 0) {
            std::cerr << "\r\r\r\r" << i / std::max(1ul, ITERATIONS / 100) << "%" << std::flush;
        }
        for (size_t j = SLOW + 1; j < candlesVector.size(); ++j) {
            TVectorView<TCandle> candles(candlesVector, 0, j);
            result += strategy.Signal(candles) == ESignal::NONE ? 0 : 1;
        }
    }
    std::cerr << "\r\r\r\r100%" << " -> " << result << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

std::vector<TCandle> GenerateCandles() {
    std::vector<TCandle> candles;
    for (size_t i = 0; i < CANDLES; ++i) {
        candles.push_back({
            .time = static_cast<time_t>(i + 1),
            .close = static_cast<double>(std::rand() % 1000) / 10,
        });
    }
    return candles;
}

int main() {
    std::srand(924);

    const TParams params = TParams{
        {"opener", TParams{
            {"fast", TParams{
                {"period", FAST}
            }},
            {"slow", TParams{
                {"period", SLOW}
            }}
        }},
        {"closer", TParams{
            {"fast", TParams{
                {"period", FAST}
            }},
            {"slow", TParams{
                {"period", SLOW}
            }}
        }}
    };

    std::vector<TCandle> candles = GenerateCandles();

    {
        uint64_t t = Duration(candles, TNaiveStrat(params));
        std::cout << "Naive: " << t << "ms" << std::endl;
    }
    {
        uint64_t t = Duration(candles, TSmartStrat(params));
        std::cout << "Smart: " << t << "ms" << std::endl;
    }
}