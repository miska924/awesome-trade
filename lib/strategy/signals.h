#pragma once

enum class ESignal {
    NONE,
    OPEN_BUY,
    OPEN_SELL,
    CLOSE,
};

enum class EOpenSignal {
    NONE,
    BUY,
    SELL,
};

enum class ECloseSignal {
    NONE,
    CLOSE,
};

ESignal ESignalFrom(EOpenSignal signal);
ESignal ESignalFrom(ECloseSignal signal);
