// F655: seven complete native function identities, source-origin UNKNOWN.
// These are compiler-grammar probes, not assertions of historical names,
// class membership, game authorship or complete owner layout.
// No ABI fabrication, inline ASM, padding, or machine-byte grafting.
class EmptyReceiverA_F655 {public: void NoOp();};
class EmptyReceiverB_F655 {public: void NoOp();};
void EmptyReceiverA_F655::NoOp() {}
void EmptyReceiverB_F655::NoOp() {}

// Full original CDECL pointer arithmetic: the two functions are distinct
// original extents with identical genuine native x86 CODE.
extern "C" char* AfterHeaderA_F655(char* p) { return p+8; }
extern "C" char* AfterHeaderB_F655(char* p) { return p+8; }

extern "C" void EmptyFreeA_F655() {}
extern "C" void EmptyFreeB_F655() {}

// An original native thiscall forwards to one original real callee;
// the historical declaration and source provenance are not known.
class DelegateMember_F655 {public: void Forward(); void Finish();};
void DelegateMember_F655::Forward() { Finish(); }
