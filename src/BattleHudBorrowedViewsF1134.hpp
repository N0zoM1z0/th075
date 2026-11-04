#pragma once
#include <stddef.h>

// Narrow borrowed physical TH075 original HUD owner float at +0x8C.
// This is the original signed vertical HUD scroll/slide displacement,
// not a claim about the complete HUD class layout or allocation.
struct BattleHudSlideFieldF1134 {
    float verticalSlideAt8C;
};
typedef char F1134SlideSize[sizeof(BattleHudSlideFieldF1134)==4?1:-1];
#define F1134_HUD_SLIDE(hud) (*reinterpret_cast<BattleHudSlideFieldF1134*>(reinterpret_cast<unsigned char*>(hud)+0x8C))

// Original fighter's selected HUD variant is a signed char at +0x39D.
struct FighterHudSelectionF1134 { signed char styleAt39D; };
typedef char F1134SelectorSize[sizeof(FighterHudSelectionF1134)==1?1:-1];
#define F1134_FIGHTER_SELECTION(fighter) (*reinterpret_cast<FighterHudSelectionF1134*>(reinterpret_cast<unsigned char*>(fighter)+0x39D))

// Original +0x33E has 3 physically adjacent signed 16-bit native
// health-max denominators, indexed by the actual signed HUD selector.
// Borrowed only: no full fighter owner, vector allocation or padding.
struct FighterHudHealthLimitsF1134 { signed short byStyle[3]; };
typedef char F1134HealthLimitsBytes[sizeof(FighterHudHealthLimitsF1134)==6?1:-1];
typedef char F1134HealthLimitsOffset[offsetof(FighterHudHealthLimitsF1134,byStyle)==0?1:-1];
#define F1134_FIGHTER_HEALTH_LIMIT(fighter,style) (*reinterpret_cast<FighterHudHealthLimitsF1134*>(reinterpret_cast<unsigned char*>(fighter)+0x33E)).byStyle[(style)]

// Three signed bytes at +0x32A are original HUD display-variant
// selection values, selected using actor+0x39D signed style index.
struct FighterHudVariantBytesF1134 { signed char byStyle[3]; };
typedef char F1134VariantBytes[sizeof(FighterHudVariantBytesF1134)==3?1:-1];
#define F1134_FIGHTER_VARIANT(fighter,style) (*reinterpret_cast<FighterHudVariantBytesF1134*>(reinterpret_cast<unsigned char*>(fighter)+0x32A)).byStyle[(style)]

// The original HUD draws a real per-fighter float field at +0x36C,
// converting its physically observed range 0..900 into sprite slices.
// No full actor, gauge array or historic owner allocation is inferred.
struct FighterHudChargeFieldF1134 { float chargeAt36C; };
typedef char F1134ChargeFieldBytes[sizeof(FighterHudChargeFieldF1134)==4?1:-1];
#define F1134_FIGHTER_CHARGE(fighter) (*reinterpret_cast<FighterHudChargeFieldF1134*>(reinterpret_cast<unsigned char*>(fighter)+0x36C))

// Two actually adjacent unsigned byte alpha/shade values in the original
// native HUD owner at +0x98/+0x99, selected on left and right drawing.
struct BattleHudShadeBytePairF1134 {
    unsigned char leftShadeAt98;
    unsigned char rightShadeAt99;
};
typedef char F1134ShadeBytes[sizeof(BattleHudShadeBytePairF1134)==2?1:-1];
typedef char F1134ShadeRightOffset[offsetof(BattleHudShadeBytePairF1134,rightShadeAt99)==1?1:-1];
#define F1134_HUD_SHADES(hud) (*reinterpret_cast<BattleHudShadeBytePairF1134*>(reinterpret_cast<unsigned char*>(hud)+0x98))
