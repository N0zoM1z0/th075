#include "FrameActorMotionPairsF1037.hpp"
#include "FighterAnimationPhaseBorrowedF1024.hpp"
#include "FighterGaugeBorrowedF980.hpp"
#include "FighterRenderTransformWindowF1094.hpp"
// Native original-shaped TH075 CharacterObject whole switch C++ candidate.
// Original source/owner layout and the entire 81KB machine function remain NONEXACT;
// all genuine case/default gameplay is sourced from independent original PE evidence.
class FighterSwitchF569_Boss0050A580 { public: void Advance(); void NativeParentExpiredAt0045B830(); void NativeHitAt0045B860(int); void SetNativeMotionAt0040FBB0(float,float,float); short GetNativeActionAt0040FA30(); void SetAuxActionAt0040FB40(short); void SetNativeActionAt0040FAC0(int); void SetNativeTwoFloatsAt0040FB70(float,float); void SetNativeAngleBitsAt0040FB70(unsigned int,float); int RandomBoundaryAt00455580(int,int); };
class F1051Grandparent { public: void NativePrepareAt00453D40(int); void SpawnObjectAt00453A70(int,unsigned int,unsigned int,signed char,int); void SpawnObjectAt00453A70(int,float,float,signed char,int); void SpawnProjectileAt00453C80(int,unsigned int,unsigned int,signed char,int); void InitTrajectoryAt00453E60(float); void SpawnSevenAt00453B50(int,unsigned int,unsigned int,char,int,int,int); void StartAnimationAt0046D000(int); };
extern float g_F1044_GravityAt0065747C;
extern float g_F1044_GroundAt0065782C;
extern float g_F1051_ScaleStepAt00658348;
extern float g_F1051_ScaleCeilingAt0065747C;
extern float g_F1051_TrajectoryUpperAt006590C4;
extern float g_F1051_TrajectoryLowerAt00658290;
extern float g_F1055_FadeScaleAt006598A4;
extern float g_F1057_RightBoundAt0065925C;
extern float g_F1057_LeftBoundAt00659258;
extern float g_F1057_UpperBoundAt006583B4;
extern float g_F1057_LowerBoundAt00658374;
extern float g_F1057_YOffsetAt00657888;
extern float g_F1057_AngleDivAt00657828;
extern float g_F1057_SpeedScaleAt006590B4;
extern float g_F1057_SpeedBaseAt00657CBC;
extern double g_F1057_RandomDoubleAt00658A20;
extern double g_F1057_RandomBaseAt00657D00;
extern float g_F1057_NudgeAt00657480;
extern float g_F1059_ScaleBaseAt006590B4;
extern float g_F1059_ScaleRatioAt00657478;
extern float g_F1059_ScaleFadeAt006598A8;
extern float g_F1059_UpperBoundAt00657884;
extern float g_F1059_LowerBoundAt0065924C;
extern float g_F1061_CeilingAt006583FC;
extern float g_F1061_StepAt0065972C;
extern float g_F1061_OffsetAt00658354;
extern float g_F1075_StepAt006598A0;
extern float g_F1075_CeilingAt00658058;
extern float g_F1076_AngleNudgeAt00658294;
extern float g_F1076_ScaleMulAt00659450;
extern float g_F1076_RightAt00659424;
extern float g_F1076_LeftAt006595EC;
extern float g_F1076_TargetYOffsetAt00658398;
extern float g_F1080_ParentScaleAt006590A8;
extern float g_F1080_AngleIncreaseAt00657850;
extern float g_F1081_ParentYOffsetAt00658268;
extern float g_F1081_AngleStepAt00657874;
extern float g_F1083_YBoundAt00658E80;
extern float g_F1085_ParentMultiplierAt0065989C;
extern float g_F1085_ParentYMultiplierAt00657F74;
extern float g_F1085_YOffsetAt0065835C;
extern float g_F1085_LastYAt006592A4;
extern float g_F1062_ScaleStepAt006583F8;
extern float g_F1068_ActionSpeedAt00657878;
extern float g_F1069_ParentYFirstAt00659138;
extern float g_F1069_ParentYSecondAt00658264;
extern float g_F1070_InitSpeedAt00657858;
extern float g_F1070_AnimSpeedAt006592A4;
extern float g_F1070_FadeScaleAt00659454;
extern float g_F1093_XStepAt00658048;
extern float g_F1095_ScaleCeilingAt00659898;
extern float g_F1095_LowerYAt00659894;
extern float g_F1095_UpperYAt00659890;
extern float g_F1101_RightAt00659424;
extern float g_F1101_LeftAt0065924C;
extern float g_F1110_NativeSpeedAt006578C0;
extern float g_F1110_NativeBaseAt00657CF8;
extern signed char g_F1113_DifficultyAt006714D0;
extern float g_F1113_DivisorAt0065988C;
extern float g_F1057_SpeedBaseAt006590BC;
extern float g_F1120_XBrakingAt00659090;
extern float g_F1125_YUpperAt00657884;
extern float g_F1126_XDistanceAt00657850;
extern float g_F1126_RightAt00659884;
extern float g_F1126_LeftAt006595E4;
extern float g_F1131_LeftHitAt00659230;
extern float g_F1131_TopHitAt006590A8;
extern float g_F1131_BottomHitAt00658268;
extern double g_F1132_DoubleAt00659228;
extern float g_F1114_RandomOffsetAt00659094;
extern float g_F1114_FadeAt00659240;
extern double g_F1115_RandomDoubleAt006583B8;
extern float g_F1115_DistanceAt0065786C;
extern float g_F1116_YOffsetAt00659888;
extern float g_F1116_AngleOffsetAt0065786C;
extern float __cdecl F1115_AbsFloatAt00412D90(float);

extern float __cdecl F1057_FloatAtan2At00483300(float,float);

#define RAW reinterpret_cast<char*>(this)
#define I16(off) *reinterpret_cast<signed short*>(RAW+(off))
#define OWNER (*reinterpret_cast<char**>(RAW+0x2E8))
#define PARENT (*reinterpret_cast<char**>(RAW+0xE4))
#define PARENT_FIELD(type,off) (*reinterpret_cast<type*>(PARENT+(off)))
#define PARENT_GRANDPARENT (*reinterpret_cast<char**>(PARENT+0x2E8))
#define PARENT_GRANDPARENT_FIELD(type,off) (*reinterpret_cast<type*>(PARENT_GRANDPARENT+(off)))
#define SELF_FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
void FighterSwitchF569_Boss0050A580::Advance() {
    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(
                *reinterpret_cast<char**>(RAW+0xE4)+0x2E8)+0x3BA) != 0)
        return;
    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(RAW+0xE4)+0x3BA) != 0 &&
            I16(0x8A) == 0)
        return;
    if (I16(0x82) != 0) {
        --I16(0x82);
        return;
    }
    switch (I16(0x60)) {
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
        default: GetNativeActionAt0040FA30();
    }
}
#undef SELF_FIELD
#undef PARENT_GRANDPARENT_FIELD
#undef PARENT_GRANDPARENT
#undef PARENT_FIELD
#undef PARENT
#undef OWNER
#undef I16
#undef RAW
