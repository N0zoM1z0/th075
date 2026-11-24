// Native ReimuFighter::Advance special actions from 0045DD70.

#define R1189_ACTION 0x252
#define R1189_HAS_BONUS 1
#include "ReimuResourcePreparationF1189.inc"
#undef R1189_ACTION
#undef R1189_HAS_BONUS

#define R1189_ACTION 0x253
#define R1189_HAS_BONUS 1
#include "ReimuResourcePreparationF1189.inc"
#undef R1189_ACTION
#undef R1189_HAS_BONUS

#define R1189_ACTION 0x254
#define R1189_HAS_BONUS 0
#include "ReimuResourcePreparationF1189.inc"
#undef R1189_ACTION
#undef R1189_HAS_BONUS

#include "ReimuFourShot258F1189.inc"
#include "ReimuFourShot259F1189.inc"
#include "ReimuFourShot25AF1189.inc"
#include "ReimuFourShot25BF1189.inc"
#include "ReimuFan25CF1189.inc"
#include "ReimuCircle25DF1189.inc"
#include "ReimuFan25EF1189.inc"
#include "ReimuFan25FF1189.inc"

#define R1189_ACTION 0x260
#define R1189_AIR 0
#define R1189_FIRE_STAGE 6
#define R1189_ANGLE 0.0f
#define R1189_SPEED 8.0f
#define R1189_X_OFFSET 30
#define R1189_Y_OFFSET g_ReimuSpecialYAt0065908C
#define R1189_EFFECT 0x32C
#define R1189_HAS_PREPARATION 0
#include "ReimuSingleSpecialAttackF1189.inc"
#undef R1189_ACTION
#undef R1189_AIR
#undef R1189_FIRE_STAGE
#undef R1189_ANGLE
#undef R1189_SPEED
#undef R1189_X_OFFSET
#undef R1189_Y_OFFSET
#undef R1189_EFFECT
#undef R1189_HAS_PREPARATION

#define R1189_ACTION 0x261
#define R1189_AIR 0
#define R1189_FIRE_STAGE 6
#define R1189_ANGLE -45.0f
#define R1189_SPEED 8.0f
#define R1189_X_OFFSET 37
#define R1189_Y_OFFSET g_ReimuAirVolleyYAt00659098
#define R1189_EFFECT 0x32C
#define R1189_HAS_PREPARATION 1
#include "ReimuSingleSpecialAttackF1189.inc"
#undef R1189_ACTION
#undef R1189_AIR
#undef R1189_FIRE_STAGE
#undef R1189_ANGLE
#undef R1189_SPEED
#undef R1189_X_OFFSET
#undef R1189_Y_OFFSET
#undef R1189_EFFECT
#undef R1189_HAS_PREPARATION

#define R1189_ACTION 0x262
#define R1189_AIR 1
#define R1189_FIRE_STAGE 3
#define R1189_ANGLE 0.0f
#define R1189_SPEED 8.0f
#define R1189_X_OFFSET 12
#define R1189_Y_OFFSET GeometryConstants::HundredTwenty
#define R1189_EFFECT 0x32C
#define R1189_HAS_PREPARATION 1
#include "ReimuSingleSpecialAttackF1189.inc"
#undef R1189_ACTION
#undef R1189_AIR
#undef R1189_FIRE_STAGE
#undef R1189_ANGLE
#undef R1189_SPEED
#undef R1189_X_OFFSET
#undef R1189_Y_OFFSET
#undef R1189_EFFECT
#undef R1189_HAS_PREPARATION

#define R1189_ACTION 0x263
#define R1189_AIR 1
#define R1189_FIRE_STAGE 3
#define R1189_ANGLE 45.0f
#define R1189_SPEED 8.0f
#define R1189_X_OFFSET 12
#define R1189_Y_OFFSET GeometryConstants::HundredTwenty
#define R1189_EFFECT 0x32C
#define R1189_HAS_PREPARATION 1
#include "ReimuSingleSpecialAttackF1189.inc"
#undef R1189_ACTION
#undef R1189_AIR
#undef R1189_FIRE_STAGE
#undef R1189_ANGLE
#undef R1189_SPEED
#undef R1189_X_OFFSET
#undef R1189_Y_OFFSET
#undef R1189_EFFECT
#undef R1189_HAS_PREPARATION
