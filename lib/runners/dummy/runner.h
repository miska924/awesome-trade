#pragma once

#include <runners/runner.h>
#include <strategy/strategy.h>
#include <markets/market.h>


template <Strategy TStrategy, Instrument TInstrument>
struct TDummyRunner : IRunner {
    TDummyRunner(TStrategy strategy, TInstrument instrument)
        : strategy(strategy), instrument(instrument) {}

    void Run() override;

    TStrategy strategy;
    TInstrument instrument;
};

template <Strategy TStrategy, Instrument TInstrument>
void TDummyRunner<TStrategy, TInstrument>::Run() {
    while (!instrument.Finished()) {
        while (!instrument.Update()) {}
        ESignal signal = strategy.Signal(instrument.GetCandles());
        if (signal == ESignal::OPEN_BUY) { // если просят встать в лонг
            // смотрим сколько надо купить, чтобы нейтрализовать текущую позицию и встать в лонг
            int lots = -instrument.GetLots() + 1;
            if (lots > 0) { // если надо докупать вообще, то докупаем
                instrument.Order(TOrder{
                    .type = EOrderType::BUY,
                    .lots = static_cast<size_t>(lots)
                });
            }
        } else if (signal == ESignal::OPEN_SELL) { // если просят встать в шорт
            // смотрим сколько надо продать, чтобы нейтрализовать текущую позицию и встать в шорт
            int lots = instrument.GetLots() + 1;
            if (lots > 0) { // если надо допродать, то допродаем
                instrument.Order(TOrder{
                    .type = EOrderType::SELL,
                    .lots = static_cast<size_t>(lots)
                });
            }
        } else if (signal == ESignal::CLOSE && instrument.GetLots() != 0) {
            // если просят закрыть все позиции и я реально в позиции, то закрываю
            instrument.Order(TOrder{
                .type = instrument.GetLots() < 0 ? EOrderType::BUY : EOrderType::SELL,
                .lots = static_cast<size_t>(abs(instrument.GetLots()))
            });
        }
    }
}
