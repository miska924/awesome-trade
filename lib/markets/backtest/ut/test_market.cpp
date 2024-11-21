#include <gtest/gtest.h>

#include <markets/backtest/market.h>


TEST(TBacktestMarket, TBacktestMarket) {
    TBacktestMarket market;
    TBacktestInstrument<TFakeRecorder> instrument = market.GetInstrument<TFakeRecorder>(
        TFakeRecorder(), // recorder
        42, // seed
        1000, // size
        0, // offset
        10000, // currency
        0.005 // fee
    );

    EXPECT_EQ(instrument.GetCurrency(), 10000);
    EXPECT_EQ(instrument.GetLots(), 0);
    EXPECT_EQ(instrument.GetCandles().Size(), 0);

    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_EQ(instrument.Finished(), false);
        EXPECT_EQ(instrument.Update(), true);
        EXPECT_EQ(instrument.GetCandles().Size(), i + 1);

        instrument.Order(TOrder{
            .type = (i % 2) ? EOrderType::SELL : EOrderType::BUY,
            .lots = 1
        });

        EXPECT_EQ(instrument.GetLots(), (i & 1) ? 0 : 1);
    }

    EXPECT_EQ(instrument.Finished(), true);
    EXPECT_EQ(instrument.Update(), false);
    EXPECT_EQ(instrument.GetCandles().Size(), 1000);
}
