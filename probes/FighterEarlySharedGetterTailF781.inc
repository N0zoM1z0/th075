// F781: original shared post-case policy at 005515BA, not a placeholder.
// Native 0/2/4/5 action handlers alone enter this common, 8-byte getter
// before epilogue. All other switch breaks return without this call.
// The entry jumps and 2-byte fall-through skip are original PE observations.
    return;
native_shared_getter:
    GetNativeActionAt40FA30();
