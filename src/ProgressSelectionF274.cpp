#include <string.h>

// Borrowed game-profile owner method ABI only. The complete original score
// matrix and profile metadata layout are not inferred from these accesses.
class ProgressRecordsF274 {
public:
    void SetSelection(signed char fighter, signed char difficulty);
    void* GetSelectedRecordAddress();
    void StoreWorkingEightBytes(signed char slot);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(off) (*reinterpret_cast<signed char*>(RAW+(off)))
void ProgressRecordsF274::SetSelection(signed char fighter, signed char difficulty)
{
    FIELD(0x16ac4)=fighter;
    FIELD(0x16ac5)=difficulty;
}
void* ProgressRecordsF274::GetSelectedRecordAddress()
{
    return RAW+FIELD(0x16ac4)*0x17f0+FIELD(0x16ac5)*0x5fc;
}
void ProgressRecordsF274::StoreWorkingEightBytes(signed char slot)
{
    memcpy(RAW+FIELD(0x16ac4)*0x17f0+FIELD(0x16ac5)*0x5fc+0x55c+slot*0x10,
           RAW+0x16a94,8);
}
#undef FIELD
#undef RAW
