#pragma once
#include <stddef.h>

// Independently native-observed notice fields in multiple complete
// fighter/UI game functions. These are BORROWED *partial windows*,
// never instantiated/embedded as complete original fighter classes.
// Observe physical signedness at the particular native access site.
struct FighterNoticeBadgeF960 {
    signed char noticeAt6E7;
    unsigned char firstAt6E8;
    unsigned char colorAt6E9;
};
struct FighterNoticeMotionF960 {
    signed short axisAt6EA;
    signed short extentAt6EC;
};
struct FighterNoticeCountersF960 {
    signed short stateAt6F0;
    signed short priorAt6F2;
    signed short nextAt6F4;
    signed short durationAt6F6;
};
struct FighterNoticeSingleByteF960 {unsigned char byteValue;};
typedef char FighterNoticeBadgeSizeF960[(sizeof(FighterNoticeBadgeF960)==3)?1:-1];
typedef char FighterNoticeMotionSizeF960[(sizeof(FighterNoticeMotionF960)==4)?1:-1];
typedef char FighterNoticeCountersSizeF960[(sizeof(FighterNoticeCountersF960)==8)?1:-1];
typedef char FighterNoticeBadgeOffsetsF960[
    (offsetof(FighterNoticeBadgeF960,firstAt6E8)==1 &&
     offsetof(FighterNoticeBadgeF960,colorAt6E9)==2)?1:-1];
typedef char FighterNoticeMotionOffsetsF960[
    (offsetof(FighterNoticeMotionF960,extentAt6EC)==2)?1:-1];
typedef char FighterNoticeCounterOffsetsF960[
    (offsetof(FighterNoticeCountersF960,priorAt6F2)==2 &&
     offsetof(FighterNoticeCountersF960,nextAt6F4)==4 &&
     offsetof(FighterNoticeCountersF960,durationAt6F6)==6)?1:-1];

// +0x6F6 is naturally a 16-bit duration/state field at write time
// (0045CDF0), but the renderer 0045D5EA reads only the low BYTE.
// Do not misrepresent the rendering read as a 16-bit load.
#define F960_BADGE(receiver) (*reinterpret_cast<FighterNoticeBadgeF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6E7))
#define F960_MOTION(receiver) (*reinterpret_cast<FighterNoticeMotionF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6EA))
#define F960_COUNTERS(receiver) (*reinterpret_cast<FighterNoticeCountersF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6F0))
#define F960_ENABLED_BYTE(receiver) (reinterpret_cast<FighterNoticeSingleByteF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6EE)->byteValue)
#define F960_STEP_LOW_BYTE(receiver) (reinterpret_cast<FighterNoticeSingleByteF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6F6)->byteValue)
#define F960_TRANSITION_BYTE(receiver) (reinterpret_cast<FighterNoticeSingleByteF960*>(reinterpret_cast<unsigned char*>(receiver)+0x6E6)->byteValue)
