// F891 original native action2C3 full 69B/20x86/4 typed PE calls.
// Real Reset/getter, value4E0 selects native action0 or1, then giant return.
// Whole 46755B original fighter NONEXACT; this is not an independent callable leaf.
case 0x2C3: {
    ClearMotionFields();
    if (AdvanceNestedFrame()==(field070)) {
        if (inputY==0)
            SetNativeActionAt40FAC0(0);
        else
            SetNativeActionAt40FAC0(1);
    }
    return;
}
