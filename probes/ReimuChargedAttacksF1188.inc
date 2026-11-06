// Native Reimu 1F4..1FB charge/warp/repeat and projectile-leap policies.

#define R1188_ACTION 0x1f4
#define R1188_FADE_STAGE 1
#define R1188_RETURN_STAGE 3
#define R1188_LAND_STAGE 7
#define R1188_HAS_GRAVITY_MIN 0
#include "ReimuChargeWarpAttackF1188.inc"
#undef R1188_ACTION
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
#undef R1188_LAND_STAGE
#undef R1188_HAS_GRAVITY_MIN


#define R1188_ACTION 0x1f5
#define R1188_FADE_STAGE 1
#define R1188_RETURN_STAGE 3
#define R1188_LAND_STAGE 6
#include "ReimuChargeRepeatAttackF1188.inc"
#undef R1188_ACTION
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
#undef R1188_LAND_STAGE


#define R1188_ACTION 0x1f6
#define R1188_FADE_STAGE 1
#define R1188_RETURN_STAGE 3
#define R1188_LAND_STAGE 7
#define R1188_HAS_GRAVITY_MIN 0
#include "ReimuChargeWarpAttackF1188.inc"
#undef R1188_ACTION
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
#undef R1188_LAND_STAGE
#undef R1188_HAS_GRAVITY_MIN


#define R1188_ACTION 0x1f7
#define R1188_FADE_STAGE 2
#define R1188_RETURN_STAGE 4
#define R1188_LAND_STAGE 8
#define R1188_HAS_GRAVITY_MIN 1
#include "ReimuChargeWarpAttackF1188.inc"
#undef R1188_ACTION
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
#undef R1188_LAND_STAGE
#undef R1188_HAS_GRAVITY_MIN


#define R1188_ACTION 0x1f8
#define R1188_FADE_STAGE 2
#define R1188_RETURN_STAGE 4
#define R1188_LAND_STAGE 7
#include "ReimuChargeRepeatAttackF1188.inc"
#undef R1188_ACTION
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
#undef R1188_LAND_STAGE


#define R1188_ACTION 0x1fa
#define R1188_LEAP_X 7.5f
#define R1188_LEAP_Y 8.5f
#include "ReimuProjectileLeapF1188.inc"
#undef R1188_ACTION
#undef R1188_LEAP_X
#undef R1188_LEAP_Y


#define R1188_ACTION 0x1fb
#define R1188_LEAP_X 9.5f
#define R1188_LEAP_Y 12.5f
#include "ReimuProjectileLeapF1188.inc"
#undef R1188_ACTION
#undef R1188_LEAP_X
#undef R1188_LEAP_Y

