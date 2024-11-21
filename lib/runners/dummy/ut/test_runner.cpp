#include <gtest/gtest.h>

#include <markets/backtest/market.h>
#include <markets/recorders.h>
#include <runners/dummy/runner.h>
#include <strategy/closers/dummy/closer.h>
#include <strategy/openers/dummy/opener.h>
#include <strategy/strategy.h>


TEST(DummyRunner, Test) {
    TBacktestMarket market;
    TDummyRunner<TStrategy<TDummyOpener, TDummyCloser>, TBacktestInstrument<TFileRecorder>> runner(
        TStrategy<TDummyOpener, TDummyCloser>({
            {"opener", TParams()},
            {"closer", TParams()},
        }),
        market.GetInstrument<TFileRecorder>(
            TFileRecorder("record.json"), // record
            42, // seed
            1000, // size
            0, // offset
            10000, // currency
            0.005 // fee
        )
    );
    runner.Run();
    EXPECT_NE(runner.instrument.GetCurrency(), 10000);
}
