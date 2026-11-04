#include "FrameActorMotionPairsF1037.hpp"
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class FighterSwitchF569_Boss0050A580 { public: void Advance(); void NativeParentExpiredAt0045B830(); void SetNativeMotionAt0040FBB0(int,float,int); short GetNativeActionAt0040FA30(); void SetAuxActionAt0040FB40(int); void SetNativeActionAt0040FAC0(int); void SetNativeTwoFloatsAt0040FB70(float,float); int RandomBoundaryAt00455580(int,int); };
class F1051Grandparent { public: void NativePrepareAt00453D40(int); void SpawnObjectAt00453A70(int,unsigned int,unsigned int,signed char,int); void SpawnProjectileAt00453C80(int,unsigned int,unsigned int,signed char,int); void InitTrajectoryAt00453E60(float); };
extern unsigned int g_FighterProbeMarker;
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
extern float g_F1062_ScaleStepAt006583F8;
extern float g_F1068_ActionSpeedAt00657878;
extern float g_F1069_ParentYFirstAt00659138;
extern float g_F1069_ParentYSecondAt00658264;

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
        case 0x323: g_FighterProbeMarker = 804; break;
        case 0x324: g_FighterProbeMarker = 805; break;
#include "CharacterObjectBoss325F1052.inc"
        case 0x328: g_FighterProbeMarker = 809; break;
        case 0x329: g_FighterProbeMarker = 810; break;
        case 0x32A: g_FighterProbeMarker = 811; break;
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
        case 0x346: g_FighterProbeMarker = 839; break;
        case 0x347: g_FighterProbeMarker = 840; break;
        case 0x348: g_FighterProbeMarker = 841; break;
        case 0x349: g_FighterProbeMarker = 842; break;
        case 0x34A: g_FighterProbeMarker = 843; break;
        case 0x34B: g_FighterProbeMarker = 844; break;
        case 0x34C: g_FighterProbeMarker = 845; break;
        case 0x34D: g_FighterProbeMarker = 846; break;
        case 0x34E: g_FighterProbeMarker = 847; break;
        case 0x34F: g_FighterProbeMarker = 848; break;
        case 0x350: g_FighterProbeMarker = 849; break;
        case 0x351: g_FighterProbeMarker = 850; break;
        case 0x352: g_FighterProbeMarker = 851; break;
        case 0x353: g_FighterProbeMarker = 852; break;
        case 0x354: g_FighterProbeMarker = 853; break;
        case 0x355: g_FighterProbeMarker = 854; break;
        case 0x356: g_FighterProbeMarker = 855; break;
        case 0x357: g_FighterProbeMarker = 856; break;
        case 0x358: g_FighterProbeMarker = 857; break;
        case 0x359: g_FighterProbeMarker = 858; break;
        case 0x35A: g_FighterProbeMarker = 859; break;
        case 0x35B: g_FighterProbeMarker = 860; break;
        case 0x35C: g_FighterProbeMarker = 861; break;
        case 0x35D: g_FighterProbeMarker = 862; break;
        case 0x35E: g_FighterProbeMarker = 863; break;
        case 0x35F: g_FighterProbeMarker = 864; break;
        case 0x360: g_FighterProbeMarker = 865; break;
        case 0x361: g_FighterProbeMarker = 866; break;
        case 0x362: g_FighterProbeMarker = 867; break;
        case 0x363: g_FighterProbeMarker = 868; break;
        case 0x364: g_FighterProbeMarker = 869; break;
        case 0x365: g_FighterProbeMarker = 870; break;
        case 0x366: g_FighterProbeMarker = 871; break;
        case 0x367: g_FighterProbeMarker = 872; break;
        case 0x368: g_FighterProbeMarker = 873; break;
        case 0x369: g_FighterProbeMarker = 874; break;
        case 0x384: g_FighterProbeMarker = 901; break;
        case 0x385: g_FighterProbeMarker = 902; break;
        case 0x386: g_FighterProbeMarker = 903; break;
        case 0x387: g_FighterProbeMarker = 904; break;
        case 0x388: g_FighterProbeMarker = 905; break;
        case 0x389: g_FighterProbeMarker = 906; break;
        case 0x38A: g_FighterProbeMarker = 907; break;
        case 0x38B: g_FighterProbeMarker = 908; break;
        case 0x38C: g_FighterProbeMarker = 909; break;
        case 0x38E: g_FighterProbeMarker = 911; break;
        case 0x38F: g_FighterProbeMarker = 912; break;
        case 0x390: g_FighterProbeMarker = 913; break;
        case 0x391: g_FighterProbeMarker = 914; break;
        case 0x392: g_FighterProbeMarker = 915; break;
        case 0x393: g_FighterProbeMarker = 916; break;
        case 0x3E3: g_FighterProbeMarker = 996; break;
        case 0x3E4: g_FighterProbeMarker = 997; break;
        case 0x3E5: g_FighterProbeMarker = 998; break;
        case 0x3E6: g_FighterProbeMarker = 999; break;
        default: g_FighterProbeMarker = 0;
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
