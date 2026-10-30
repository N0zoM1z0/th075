// F745: complete original R212-authored GameProgress::ClearUnlockBit.
// Match native signed short 0..320 and authentic game-owned bit DWORDs
// at receiver+0x16A9C. No guessed full private GameProgress layout.
class GameProgressClearF745 {
public: void ClearUnlockBit(short selected);
};
#define BITS (reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this)+0x16A9C))
void GameProgressClearF745::ClearUnlockBit(short selected) {
    if (selected>320 || selected<0) {} else
        BITS[selected/32] &= (0xffffffffu - (1u << (selected%32)));
}
#undef BITS
