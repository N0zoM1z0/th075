#pragma once
#include <stddef.h>

// Borrowed one-byte command slot observed by the original Japanese
// TH075 PE at this+0x511 in distinct native Input and AI systems.
// This is NOT a complete fighter/input object or an instantiable
// 0x512-byte class. Its sole observed byte is accessed relative to
// the real receiver. Its exact 8-bit signedness-neutral storage is
// checked by independently accepted native whole functions.
struct FighterCommandByteF940 {
    unsigned char commandCode;
};
typedef char FighterCommandByteF940Size[
    sizeof(FighterCommandByteF940)==1 ? 1 : -1];
typedef char FighterCommandByteF940Offset[
    offsetof(FighterCommandByteF940, commandCode)==0 ? 1 : -1];

#define F940_COMMAND_AT511(receiver) (reinterpret_cast<FighterCommandByteF940*>(reinterpret_cast<unsigned char*>(receiver)+0x511)->commandCode)
