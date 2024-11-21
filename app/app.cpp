#include <random>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <future>
#include <cstdlib>

#include <markets/backtest/market.h>
#include <markets/recorders.h>
#include <runners/dummy/runner.h>
#include <strategy/closers/cross/closer.h>
#include <strategy/closers/dummy/closer.h>
#include <strategy/features/sma/feature.h>
#include <strategy/openers/cross/opener.h>
#include <strategy/openers/dummy/opener.h>
#include <strategy/params/params.h>
#include <strategy/strategy.h>


using TStrat = TStrategy<TCrossOpener<TSmaFeature<2>>, TCrossCloser<TSmaFeature<2>>>;

int main() {
    TBacktestMarket market;
    TDummyRunner<
        TStrat,
        TBacktestInstrument<TTelegramRecorder>
    > runner(
        TStrat({
            {"opener", TParams{
                {"fast", TParams{
                    {"period", 12}
                }},
                {"slow", TParams{
                    {"period", 100}
                }},
            }},
            {"closer", TParams{
                {"fast", TParams{{
                    "period", 12}
                }},
                {"slow", TParams{{
                    "period", 100}
                }},
            }},
        }),
        market.GetInstrument<TTelegramRecorder>(
            TTelegramRecorder(std::getenv("TELEGRAM_TOKEN"), std::getenv("TELEGRAM_CHATID"), 300),
            42, // seed
            10000, // size
            300, // offset
            1000, // currency
            0.0004 // fee
        )
    );
    runner.Run();

    return 0;
}
