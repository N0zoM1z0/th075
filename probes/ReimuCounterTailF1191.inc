// Original Reimu counter volleys, random drift and timed tail policies.
#define R1191_ACTION 0x2D0
#define R1191_AIR 0
#define R1191_FIRST_STAGE 8
#define R1191_ANGLE_EXPR (S16(0xF00)*5)
#define R1191_X_OFFSET 114
#define R1191_Y_OFFSET g_ReimuLowVolleyYAt006590A0
#include "ReimuCounterVolleyF1191.inc"
#undef R1191_ACTION
#undef R1191_AIR
#undef R1191_FIRST_STAGE
#undef R1191_ANGLE_EXPR
#undef R1191_X_OFFSET
#undef R1191_Y_OFFSET
#define R1191_ACTION 0x2D1
#define R1191_AIR 0
#define R1191_FIRST_STAGE 8
#define R1191_ANGLE_EXPR (S16(0xF00)*5+30)
#define R1191_X_OFFSET 90
#define R1191_Y_OFFSET g_ReimuHighVolleyYAt0065909C
#include "ReimuCounterVolleyF1191.inc"
#undef R1191_ACTION
#undef R1191_AIR
#undef R1191_FIRST_STAGE
#undef R1191_ANGLE_EXPR
#undef R1191_X_OFFSET
#undef R1191_Y_OFFSET
#define R1191_ACTION 0x2D2
#define R1191_AIR 1
#define R1191_FIRST_STAGE 4
#define R1191_ANGLE_EXPR (0-S16(0xF00)*6)
#define R1191_X_OFFSET 83
#define R1191_Y_OFFSET g_ReimuAirVolleyYAt00659098
#include "ReimuCounterVolleyF1191.inc"
#undef R1191_ACTION
#undef R1191_AIR
#undef R1191_FIRST_STAGE
#undef R1191_ANGLE_EXPR
#undef R1191_X_OFFSET
#undef R1191_Y_OFFSET
#define R1191_ACTION 0x2D3
#define R1191_AIR 1
#define R1191_FIRST_STAGE 4
#define R1191_ANGLE_EXPR (-30-S16(0xF00)*9)
#define R1191_X_OFFSET 67
#define R1191_Y_OFFSET g_ReimuDownVolleyYAt0065826C
#include "ReimuCounterVolleyF1191.inc"
#undef R1191_ACTION
#undef R1191_AIR
#undef R1191_FIRST_STAGE
#undef R1191_ANGLE_EXPR
#undef R1191_X_OFFSET
#undef R1191_Y_OFFSET
