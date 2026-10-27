#include <string.h>

// This is a call-only progress-defaults constructor view. Its physical
// writes are target-observed, not an original complete archive declaration.
// The native body explicitly initializes ten 9-byte local fish names;
// the original source-level purpose of those bytes remains unknown.
// No owner is instantiated or allocated through this small receiver.
class ProgressDefaultsF214 {
public:
    ProgressDefaultsF214();
};
#define BYTE_FIELD(off) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + (off)))
#define DWORD_FIELD(off) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + (off)))
#define RECORD_BYTE(off) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x17f0*i + 0x5fc*j + 16*k + (off)))
#define RECORD_DWORD(off) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x17f0*i + 0x5fc*j + 16*k + (off)))
ProgressDefaultsF214::ProgressDefaultsF214()
{
    memset(this, 0, 0x16710);
    memset(reinterpret_cast<unsigned char*>(this)+0x16a9c, 0, 0x28);
    // These ten locally initialized, NUL-terminated names occur in the
    // target's stack frame even if their source-level later use is unknown.
    char fishNames[10][9] = {
        "iwashi  ", "maguro  ", "hirame  ", "katuo   ",
        "karei   ", "sanma   ", "sake    ", "buri    ",
        "saba    ", "tai     "
    };
    for (int i=0; i<15; ++i) {
        for (int j=0; j<4; ++j) {
            for (int k=0; k<10; ++k) {
                RECORD_DWORD(0x568) = (10-k)*1000;
                RECORD_BYTE(0x55c) = 13;
                RECORD_BYTE(0x55d) = 14;
                RECORD_BYTE(0x55e) = 100;
                RECORD_BYTE(0x55f) = 4;
                RECORD_BYTE(0x560) = 13;
                RECORD_BYTE(0x561) = 19;
                RECORD_BYTE(0x562) = 17;
                RECORD_BYTE(0x563) = 24;
            }
        }
        for (int t=0; t<15; ++t)
            reinterpret_cast<int(*)[15]>(reinterpret_cast<unsigned char*>(this) + 0x16710)[i][t] = 10;
    }
    BYTE_FIELD(0x16a94)=100;
    BYTE_FIELD(0x16a95)=100;
    BYTE_FIELD(0x16a96)=100;
    BYTE_FIELD(0x16a97)=100;
    BYTE_FIELD(0x16a98)=100;
    BYTE_FIELD(0x16a99)=100;
    BYTE_FIELD(0x16a9a)=100;
    BYTE_FIELD(0x16a9b)=100;
}
#undef RECORD_BYTE
#undef RECORD_DWORD
#undef DWORD_FIELD
#undef BYTE_FIELD
