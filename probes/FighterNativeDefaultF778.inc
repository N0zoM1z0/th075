// F778 native original 00551598: real shared default-handler policy.
// The PE's seven case tables map 239 distinct action IDs to this native
// handler. The original non-optimizing compiler compares its actual
// AdvanceNestedFrame() result with the observed signed +0x70 state,
// and invokes real SetNativeActionAt40FAC0(0) only on equality.
// This is one *interior* of still-NONEXACT 00543210, not callable CODE.
default:
    if (AdvanceNestedFrame()==(field070))
        SetNativeActionAt40FAC0(0);
    break;
