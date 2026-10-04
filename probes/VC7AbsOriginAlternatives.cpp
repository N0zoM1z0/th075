// Ordinary expression controls: matching bytes do not identify source ownership.
extern "C" int AbsIntExpressionControl(int value) {
    return value < 0 ? -value : value;
}

extern "C" long AbsLongExpressionControl(long value) {
    return value < 0 ? -value : value;
}
