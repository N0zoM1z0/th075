// F604: two separately observed complete original TH075 game-like
// leaf source shapes; actual original owner/types still UNKNOWN.
// No original complete class layout or shared owner is assumed.
// Normal VC7.1 C++ emits the actual original 24B counter-clear and
// 31B unsigned comparison (rather than shorter !=0) machine code.
class GameCounterOwnerF604 {
public:
    void ClearCounter();
};
class GameStatusFlagOwnerF604 {
public:
    int HasFlagBit();
};

void GameCounterOwnerF604::ClearCounter() {
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x47C) = 0;
}

int GameStatusFlagOwnerF604::HasFlagBit() {
    // True original is an unsigned comparison to zero, NOT != 0.
    // Keep the actual nested field read as one source expression; a
    // named pointer local makes VC7.1 allocate a non-native EBP slot.
    return (*reinterpret_cast<unsigned int*>(
        *reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x74) + 0x3C)
        & 0x20) > 0;
}
