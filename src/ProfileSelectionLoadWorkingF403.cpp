#include <string.h>
// R180 independently observed profile-selection 8-byte data restore.
// This is the reverse memory direction of a separately accepted store,
// preserving real signed choice, difficulty and 16-byte record stride.
class ProgressRecordsF403 {public:void LoadWorkingEightBytes(signed char slot);};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(o) (*reinterpret_cast<signed char*>(RAW+(o)))
void ProgressRecordsF403::LoadWorkingEightBytes(signed char slot) {
    memcpy(RAW+0x16a94,
           RAW+FIELD(0x16ac4)*0x17f0+FIELD(0x16ac5)*0x5fc+0x55c+slot*0x10,8);
}
#undef FIELD
#undef RAW
