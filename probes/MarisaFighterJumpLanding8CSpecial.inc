// Original Marisa 0x8C pre-switch landing branch.
// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
if (actionSnapshot == F628_CASE) goto action8CSpecial;
