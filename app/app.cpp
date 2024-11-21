#include <random>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <future>

#include <markets/dummy/market.h>
#include <strategy/closers/cross/closer.h>
#include <strategy/features/sma/feature.h>
#include <strategy/features/cached_feature.h>
#include <strategy/openers/cross/opener.h>
#include <strategy/params/params.h>
#include <strategy/strategy.h>


using TSmartStrat = TStrategy<TCrossOpener<TSmaFeature<2>>, TCrossCloser<TSmaFeature<2>>>;


constexpr size_t ITERATIONS = 100000;
constexpr size_t CANDLES = 100000;

constexpr int FAST = 10;
constexpr int SLOW = 300;

template<Strategy TStrat>
uint64_t Run(const std::vector<TCandle>& candlesVector, TParams params, size_t startIter, size_t endIter, bool log) {
    uint64_t result = 0;
    size_t iterations = endIter - startIter;
    for (size_t i = startIter; i < endIter; ++i) {
        if (log && iterations % std::max(1ul, iterations / 100) == 0) {
            std::cerr << "\r\r\r\r" << (i - startIter) / std::max(1ul, iterations / 100) << "%" << std::flush;
        }
        TStrat strategy(params);
        for (size_t j = SLOW + 1; j < candlesVector.size(); ++j) {
            TVectorView<TCandle> candles(candlesVector, 0, j);
            result += strategy.Signal(candles) == ESignal::NONE ? 0 : 1;
        }
    }
    return result;
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

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads > 2) {
        numThreads -= 2;
    }
    if (numThreads == 0) {
        numThreads = 1; // Fallback to single thread if hardware_concurrency is not implemented
    }

    std::vector<std::future<uint64_t>> futures;
    size_t iterationsPerThread = ITERATIONS / numThreads;

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t startIter = i * iterationsPerThread;
        size_t endIter = (i == numThreads - 1) ? ITERATIONS : startIter + iterationsPerThread;
        futures.push_back(std::async(std::launch::async, Run<TSmartStrat>, std::cref(candles), params, startIter, endIter, i == 0 ? true: false));
    }

    uint64_t totalResult = 0;
    for (auto& future : futures) {
        totalResult += future.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    uint64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cerr << "\r\r\r\r100%" << " -> " << totalResult << std::endl;
    std::cout << "Smart: " << duration << "ms" << std::endl;

    return 0;
}
