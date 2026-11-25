#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/CharacterObject.hpp"
#include "characters/PatchouliFighter.hpp"
#include "battle/EffectServices.hpp"
#include "battle/FighterAnimationPhaseBorrowedF1024.hpp"
// Natural-C++ reconstruction of PatchouliObject::Advance at 0050A580.
// Replays 81,539 code bytes plus 567 bytes of switch data with VC7.1 build 3077.
// Compiler profile and relocation bindings are in config/match-units.toml.
// The state cases belong to PatchouliObject; helper call contracts remain native.
// Shared sound, camera and effect spawning now use the real Fighter API,
// with float coordinates passed directly to the native float parameter slots.
// The native 0046D000 gauge timer is shared by Fighter owners, so case
// 0x35D now invokes Fighter::UpdateGaugeTimer directly.
extern float g_F1055_FadeScaleAt006598A4;
extern float g_F1059_ScaleFadeAt006598A8;
extern float g_F1075_StepAt006598A0;
extern const float g_F1126_RightAt00659884;


void PatchouliObject::Advance() {
    if (owner->opponent->field3BA != 0)
        return;
    if (owner->field3BA != 0 && field08A == 0)
        return;
    if (field082 != 0) {
        --field082;
        return;
    }
    switch (action) {
#include "CharacterObjectBoss320NativeF1045.inc"
#include "CharacterObjectBoss321F1051.inc"
#include "CharacterObjectBoss322F1046.inc"
#include "CharacterObjectBoss323F1070.inc"
#include "CharacterObjectBoss324F1071.inc"
#include "CharacterObjectBoss325F1052.inc"
#include "CharacterObjectBoss328F1073.inc"
#define F1074_CASE 0x329
#define F1074_X_SPEED 20.0f
#include "CharacterObjectBoss32932AF1074.inc"
#undef F1074_X_SPEED
#undef F1074_CASE
#define F1074_CASE 0x32A
#define F1074_X_SPEED 10.0f
#include "CharacterObjectBoss32932AF1074.inc"
#undef F1074_X_SPEED
#undef F1074_CASE
#include "CharacterObjectBoss32BF1047.inc"
#include "CharacterObjectBoss32CF1050.inc"
#include "CharacterObjectBoss32DF1047.inc"
#include "CharacterObjectBoss32EF1050.inc"
#include "CharacterObjectBoss32FF1052.inc"
#include "CharacterObjectBoss330F1068.inc"
#include "CharacterObjectBoss331F1069.inc"
#include "CharacterObjectBoss332F1047.inc"
#define F1065_ACTION 0x333
#define F1066_INITIAL_ANGLE 30.0f
#include "CharacterObjectBoss333334F1065.inc"
#undef F1066_INITIAL_ANGLE
#undef F1065_ACTION
#define F1065_ACTION 0x334
#define F1066_INITIAL_ANGLE 0.0f
#include "CharacterObjectBoss333334F1065.inc"
#undef F1066_INITIAL_ANGLE
#undef F1065_ACTION
#include "CharacterObjectBoss335F1064.inc"
#define F1065_ACTION 0x336
#define F1066_INITIAL_ANGLE -30.0f
#include "CharacterObjectBoss333334F1065.inc"
#undef F1066_INITIAL_ANGLE
#undef F1065_ACTION
#include "CharacterObjectBoss337F1054.inc"
#include "CharacterObjectBoss338F1062.inc"
#include "CharacterObjectBoss339F1061.inc"
#include "CharacterObjectBoss33AF1059.inc"
#define F1057_CASE 0x33B
#define F1057_NEXT_CASE 0x33C
#include "CharacterObjectBossLongF1057.inc"
#undef F1057_NEXT_CASE
#undef F1057_CASE
#define F1055_CASE 0x33C
#include "CharacterObjectBossFadeF1055.inc"
#undef F1055_CASE
#define F1057_CASE 0x33D
#define F1057_NEXT_CASE 0x33E
#include "CharacterObjectBossLongF1057.inc"
#undef F1057_NEXT_CASE
#undef F1057_CASE
#define F1055_CASE 0x33E
#include "CharacterObjectBossFadeF1055.inc"
#undef F1055_CASE
#define F1057_CASE 0x33F
#define F1057_NEXT_CASE 0x340
#include "CharacterObjectBossLongF1057.inc"
#undef F1057_NEXT_CASE
#undef F1057_CASE
#define F1055_CASE 0x340
#include "CharacterObjectBossFadeF1055.inc"
#undef F1055_CASE
#define F1057_CASE 0x341
#define F1057_NEXT_CASE 0x342
#include "CharacterObjectBossLongF1057.inc"
#undef F1057_NEXT_CASE
#undef F1057_CASE
#define F1055_CASE 0x342
#include "CharacterObjectBossFadeF1055.inc"
#undef F1055_CASE
#define F1057_CASE 0x343
#define F1057_NEXT_CASE 0x344
#include "CharacterObjectBossLongF1057.inc"
#undef F1057_NEXT_CASE
#undef F1057_CASE
#define F1055_CASE 0x344
#include "CharacterObjectBossFadeF1055.inc"
#undef F1055_CASE
#include "CharacterObjectBoss345F1054.inc"
#include "CharacterObjectBoss346F1076.inc"
#include "CharacterObjectBoss347F1075.inc"
#include "CharacterObjectBoss348F1080.inc"
#include "CharacterObjectBoss349F1081.inc"
#include "CharacterObjectBoss34AF1082.inc"
#include "CharacterObjectBoss34BF1083.inc"
#include "CharacterObjectBoss34CF1085.inc"
#include "CharacterObjectBoss34DF1086.inc"
#include "CharacterObjectBoss34EF1087.inc"
#include "CharacterObjectBoss34FF1088.inc"
#include "CharacterObjectBoss350F1089.inc"
#include "CharacterObjectBoss351F1090.inc"
#include "CharacterObjectBoss352F1091.inc"
#include "CharacterObjectBoss353F1092.inc"
#include "CharacterObjectBoss354F1093.inc"
#include "CharacterObjectBoss355F1095.inc"
#include "CharacterObjectBoss356F1097.inc"
#include "CharacterObjectBoss357F1098.inc"
#include "CharacterObjectBoss358F1101.inc"
#include "CharacterObjectBoss359F1099.inc"
#include "CharacterObjectBoss35AF1100.inc"
#include "CharacterObjectBoss35BF1102.inc"
#include "CharacterObjectBoss35CF1103.inc"
#include "CharacterObjectBoss35DF1104.inc"
#include "CharacterObjectBoss35EF1107.inc"
#include "CharacterObjectBoss35FF1105.inc"
#define F1108_CASE 0x360
#define F1108_NEXT_ID 0x365
#include "CharacterObjectBoss360361F1108.inc"
#undef F1108_NEXT_ID
#undef F1108_CASE
#define F1108_CASE 0x361
#define F1108_NEXT_ID 0x366
#include "CharacterObjectBoss360361F1108.inc"
#undef F1108_NEXT_ID
#undef F1108_CASE
#define F1108_CASE 0x362
#define F1108_NEXT_ID 0x367
#include "CharacterObjectBoss360361F1108.inc"
#undef F1108_NEXT_ID
#undef F1108_CASE
#define F1108_CASE 0x363
#define F1108_NEXT_ID 0x368
#include "CharacterObjectBoss360361F1108.inc"
#undef F1108_NEXT_ID
#undef F1108_CASE
#define F1108_CASE 0x364
#define F1108_NEXT_ID 0x369
#include "CharacterObjectBoss360361F1108.inc"
#undef F1108_NEXT_ID
#undef F1108_CASE
#include "CharacterObjectBoss365F1110.inc"
#define F1111_CASE 0x366
#define F1111_NEXT_ACTION 0x33E
#include "CharacterObjectBoss366369F1111.inc"
#undef F1111_NEXT_ACTION
#undef F1111_CASE
#define F1111_CASE 0x367
#define F1111_NEXT_ACTION 0x340
#include "CharacterObjectBoss366369F1111.inc"
#undef F1111_NEXT_ACTION
#undef F1111_CASE
#define F1111_CASE 0x368
#define F1111_NEXT_ACTION 0x342
#include "CharacterObjectBoss366369F1111.inc"
#undef F1111_NEXT_ACTION
#undef F1111_CASE
#define F1111_CASE 0x369
#define F1111_NEXT_ACTION 0x344
#include "CharacterObjectBoss366369F1111.inc"
#undef F1111_NEXT_ACTION
#undef F1111_CASE
#include "CharacterObjectBoss384F1113.inc"
#include "CharacterObjectBoss385F1114.inc"
#include "CharacterObjectBoss386F1115.inc"
#include "CharacterObjectBoss387F1116.inc"
#include "CharacterObjectBoss388F1117.inc"
#include "CharacterObjectBoss389F1118.inc"
#include "CharacterObjectBoss38AF1119.inc"
#include "CharacterObjectBoss38BF1120.inc"
#include "CharacterObjectBoss38CF1121.inc"
#include "CharacterObjectBoss38EF1122.inc"
#include "CharacterObjectBoss38FF1123.inc"
#include "CharacterObjectBoss390F1125.inc"
#include "CharacterObjectBoss391F1126.inc"
#include "CharacterObjectBoss392F1127.inc"
#include "CharacterObjectBoss393F1128.inc"
#include "CharacterObjectBoss3E3F1131.inc"
#include "CharacterObjectBoss3E4F1132.inc"
#include "CharacterObjectBoss3E5F1130.inc"
#include "CharacterObjectBoss3E6F1129.inc"
        default: AdvanceNestedFrame();
    }
}
