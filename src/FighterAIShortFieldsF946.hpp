#pragma once
#include <stddef.h>

// Original Japanese TH075 independently stores these three consecutive
// SIGNED 16-bit fighter AI state words at actual receiver offsets
// +0x512 / +0x514 / +0x516. Different real AI policies use the
// third word only when handling card/timer behavior. This is only
// a 6-byte borrowed tail view, NOT an allocatable fighter/AI class.
// The previously accepted command byte at +0x511 is an independent
// directly observed adjacent byte (F940); don't fake padding across
// that unaligned one-byte / signed-short physical boundary.
struct FighterAIShortFieldsF946 {
    short countdownAt512;
    short modeAt514;
    short cardTimerAt516;
};
typedef char FighterAIShortFieldsF946Size[
    sizeof(FighterAIShortFieldsF946)==6 ? 1 : -1];
typedef char FighterAIShortFieldsF946OffsetMode[
    offsetof(FighterAIShortFieldsF946,modeAt514)==2 ? 1 : -1];
typedef char FighterAIShortFieldsF946OffsetTimer[
    offsetof(FighterAIShortFieldsF946,cardTimerAt516)==4 ? 1 : -1];

#define F946_AI_FIELDS_AT512(receiver) (*reinterpret_cast<FighterAIShortFieldsF946*>(reinterpret_cast<unsigned char*>(receiver)+0x512))
