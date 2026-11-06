#include "ObjectAdvance55AC80F1194.hpp"
#include "GameLeafHelpers.hpp"
#include "AnimationProgress40FA30.hpp"
#include "ObjectMotion40FB70.hpp"
#include "SpriteTransform40FBB0.hpp"
#include "FighterEffectPolicies.hpp"
#include "RecordedRange455580.hpp"
#include "EffectServices.hpp"

// Caller-cleaned two-float/ST0 used-contract hypothesis, shared with the
// independently retained004AC040 draft. Origin and nominal return type remain
// unknown; this declaration supplies no ownership or callee exact credit.
float __cdecl Unknown483300(float first, float second);

// Same observed signed-byte view used by the accepted response policy.
extern signed char g_StateRepeatLevelAt006714D0;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0xE4) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(FIELD(unsigned char*, 0xE4) + (offset))
#define OWNER_OPPONENT(type, offset) (*reinterpret_cast<type*>(OWNER(unsigned char*, 0x2E8) + (offset)))
#define OWNER_OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(OWNER(unsigned char*, 0x2E8) + (offset))
#define SELF_VIEW(type) reinterpret_cast<type*>(this)
#define OWNER_VIEW(type) reinterpret_cast<type*>(FIELD(void*, 0xE4))
#undef PlaySound

// F1194: continued from the preserved complete F167 normal C++ draft.
// All 57 native state bodies/default are present. The complete callable remains
// NONEXACT: 726 GPR positions and six CMP widths differ from the pinned PE.
// Frame 0x19C, every EBP operand, native CFG and reference destinations agree.
void ObjectAdvance55AC80F1194::Advance()
{
    if (OWNER_OPPONENT(short, 0x3BA) != 0) return;
    if (OWNER(short, 0x3BA) != 0 && FIELD(short, 0x8A) == 0) return;
    if (FIELD(short, 0x82) != 0) {
        FIELD(short, 0x82)--;
        return;
    }
    switch (FIELD(short, 0x60)) {

// Native0055AD32..0055B0DA observation chunk; no standalone unit or credit.
case 800:
    if (FIELD(unsigned int, 0x7C) == 6 && FIELD(short, 0x62) == 4) {
        FIELD(unsigned int, 0x7C) = 0;
        FIELD(short, 0x80) = 1;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -120.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    FLOAT(0x30) = FLOAT(0x30) + 5.0f;
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) + FLOAT(0x54);
    if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 5) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(5);
        FLOAT(0x1C) = FLOAT(0x1C) + 0.5f;
        FLOAT(0x20) = FLOAT(0x20) + 0.5f;
        return;
    } else {
        if (FIELD(short, 0x62) == 5) {
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FLOAT(0x1C) = FLOAT(0x1C) * 0.75f;
            FLOAT(0x20) = FLOAT(0x20) * 0.75f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) = FLOAT(0x1C) + 0.05f;
            FLOAT(0x20) = FLOAT(0x20) + 0.05f;
            if (FLOAT(0x1C) > 2.5f) {
                FLOAT(0x1C) = 2.5f;
                FLOAT(0x20) = 2.5f;
            }
            if (OWNER(short, 0x60) == 400 && OWNER(short, 0x62) > 4) {
                SELF_VIEW(AnimationState)->ResetSecondaryCounter(FIELD(short, 0xD8) + 2);
                FIELD(short, 0x80) = FIELD(short, 0xD8) + 1;
                FLOAT(0x50) = FIELD(short, 0xD8) * 4.0f + 12.0f;
                return;
            }
            if (OWNER(short, 0x60) != 400)
                SELF_VIEW(AnimationState)->ResetSecondaryCounter(5);
        }
        if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
            SELF_VIEW(BattleEffect)->ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
            FIELD(short, 0xD8)++;
            if (FIELD(short, 0xD8) > 2) FIELD(short, 0xD8) = 2;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
            FIELD(unsigned int, 0x7C) = 0;
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        }
        if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
            FIELD(unsigned int, 0x7C) = 0;
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(3);
        }
        if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) {
            FIELD(unsigned int, 0x7C) = 0;
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(4);
        }
    }
    return;

// Native0055B0DA..0055B21F observation chunk; no standalone unit or credit.
case 801:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 0;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x2C) = 60.0f;
    }
    FLOAT(0x1C) = FLOAT(0x1C) + 0.3f;
    FLOAT(0x20) = FLOAT(0x20) + 0.3f;
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned char, 0x11) > 15)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 15;
    else
        FIELD(unsigned char, 0x11) = 0;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055B21F..0055B599 observation chunk; no standalone unit or credit.
case 802: {
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i802 = 0; i802 < 2; i802++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
    }
    if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0 && OWNER(short, 0x3B0) > 0) {
        OWNER_VIEW(FighterEffectPoliciesF135)->UpdateGaugeTimer(15);
        OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(0);
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(803, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
    }
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) < 2 &&
        (OWNER(short, 0x60) != 600 || (OWNER(short, 0x60) == 600 && OWNER(short, 0x62) > 9))) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        return;
    } else {
        if (FIELD(short, 0x62) == 2) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 15;
            } else {
                FIELD(unsigned char, 0x11) = 0;
                SELF_VIEW(BattleEffect)->ClearField74();
                return;
            }
        }
        if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
            SELF_VIEW(BattleEffect)->ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && OWNER(short, 0x60) == 600 &&
            FIELD(short, 0xD8) < 3 && OWNER(short, 0x3B0) > 0)
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    }
    return;
}

// Native0055B599..0055B7B7 observation chunk; no standalone unit or credit.
case 803: {
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x80) > 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i803 = 0; i803 < 2; i803++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x50) = 15.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x80) == 0) {
        if (FIELD(unsigned char, 0x11) > 10)
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 10;
        else
            SELF_VIEW(BattleEffect)->ClearField74();
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    return;
}

// Native0055B7B7..0055BAAA observation chunk; no standalone unit or credit.
case 804: {
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i804 = 0; i804 < 2; i804++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            FIELD(short, 0xDA) + 15 - SELF_VIEW(RecordedRange455580)->SelectRange(0, 30),
            SELF_VIEW(RecordedRange455580)->SelectRange(1600, 2400) * 0.01f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    }
    if ((FIELD(unsigned int, 0x7C) == 1 || FIELD(unsigned int, 0x7C) == 2 ||
         FIELD(unsigned int, 0x7C) == 4) && FIELD(short, 0x62) < 2) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        return;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 2)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;
}

// Native0055BAAA..0055BC84 observation chunk; no standalone unit or credit.
case 805:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 0.5f;
        FLOAT(0x20) = 0.5f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 5;
        FLOAT(0x50) = 15.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x50) = FLOAT(0x50) - 0.5f;
    if (FLOAT(0x50) < 8.0f) FLOAT(0x50) = 8.0f;
    if (FIELD(unsigned int, 0x7C) == 4) {
        FIELD(unsigned int, 0x7C) = 0;
        FIELD(short, 0x80)--;
    }
    if (FIELD(unsigned int, 0x7C) == 6) {
        FIELD(unsigned int, 0x7C) = 0;
        FIELD(short, 0x80)++;
    }
    if (FIELD(unsigned int, 0x7C) != 0) FIELD(short, 0x80) = 0;
    if (FIELD(short, 0x62) == 1 && FIELD(short, 0x80) == 0)
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
    if (FIELD(short, 0x62) == 0) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.2f;
        FLOAT(0x20) = FLOAT(0x20) + 0.2f;
    }
    if (FIELD(short, 0x62) == 2) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055BC84..0055BE29 observation chunk; no standalone unit or credit.
case 806:
    if (OWNER(short, 0x60) == 700 && FIELD(short, 0x62) < 19)
        FLOAT(0x44) = OWNER_FLOAT(0x44);
    if (OWNER(short, 0x60) != 700 && FIELD(short, 0x62) < 19) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(19);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0x80) = 12;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = 0;
    }
    if (FIELD(unsigned int, 0x7C) != 0 && ++FIELD(short, 0xDA) > 5) {
        FIELD(short, 0xDA) = 0;
        FIELD(unsigned int, 0x7C) = 0;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 19 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 3) {
        FIELD(short, 0xD8)++;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(9);
    }
    return;

// Native0055BE29..0055BF3E observation chunk; no standalone unit or credit.
case 807:
    if (OWNER(short, 0x60) == 394) {
        FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 151;
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 104.0f;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 3.0f;
        FLOAT(0x20) = 3.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    FLOAT(0x1C) = FLOAT(0x1C) * 0.8f;
    FLOAT(0x20) = FLOAT(0x20) * 0.8f;
    if (FIELD(short, 0x62) > 1 && FIELD(unsigned char, 0x11) > 10)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 10;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055BF3E..0055C03D observation chunk; no standalone unit or credit.
case 808:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 5;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x50) = 45.0f;
        FLOAT(0x54) = 0.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
        FIELD(unsigned int, 0x7C) = 0;
    }
    return;

// Native0055C03D..0055C154 observation chunk; no standalone unit or credit.
case 809:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x28) = FIELD(signed char, 0x66) * -35;
        FLOAT(0x2C) = 70.0f;
        FLOAT(0x30) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 359);
    }
    FLOAT(0x1C) = FLOAT(0x1C) * 1.05f;
    FLOAT(0x20) = FLOAT(0x20) * 1.05f;
    FLOAT(0x30) = FLOAT(0x30) + 6.0f;
    if (FIELD(unsigned char, 0x11) > 10) {
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 10;
    } else {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055C154..0055C2FE observation chunk; no standalone unit or credit.
case 810:
    if (OWNER(short, 0x60) == 705 && FIELD(short, 0x62) < 19)
        FLOAT(0x44) = OWNER_FLOAT(0x44) + 0.0f;
    if (OWNER(short, 0x60) != 705 && FIELD(short, 0x62) < 19) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(19);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0x80) = 20;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.5f;
        FLOAT(0x20) = 1.25f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = 0;
    }
    if (FIELD(unsigned int, 0x7C) != 0 && ++FIELD(short, 0xDA) > 5) {
        FIELD(short, 0xDA) = 0;
        FIELD(unsigned int, 0x7C) = 0;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 19 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 6) {
        FIELD(short, 0xD8)++;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(9);
    }
    return;

// Native0055C2FE..0055C3FD observation chunk; no standalone unit or credit.
case 811:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x50) = 45.0f;
        FLOAT(0x54) = 0.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
        FIELD(unsigned int, 0x7C) = 0;
    }
    return;

// Native0055C3FD..0055C514 observation chunk; no standalone unit or credit.
case 814:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x28) = FIELD(signed char, 0x66) * -30;
        FLOAT(0x2C) = 70.0f;
        FLOAT(0x30) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 359);
    }
    FLOAT(0x1C) = FLOAT(0x1C) * 1.05f;
    FLOAT(0x20) = FLOAT(0x20) * 1.05f;
    FLOAT(0x30) = FLOAT(0x30) + 6.0f;
    if (FIELD(unsigned char, 0x11) > 10) {
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 10;
    } else {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055C514..0055C7D8 observation chunk; no standalone unit or credit.
case 816: {
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i816 = 0; i816 < 3; i816++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            FLOAT(0xC8) + 15.0f - SELF_VIEW(RecordedRange455580)->SelectRange(0, 30), 25.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    }
    if ((FIELD(unsigned int, 0x7C) == 1 || FIELD(unsigned int, 0x7C) == 2 ||
         FIELD(unsigned int, 0x7C) == 4) && FIELD(short, 0x62) < 2) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        return;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 2)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;
}

// Native0055C7D8..0055CCD6 observation chunk; no standalone unit or credit.
case 817: {
    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -240.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i817 = 0; i817 < 5; i817++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = 10;
        FIELD(short, 0xDA) = 0;
        FIELD(short, 0xDE) = 0;
        FIELD(short, 0xDC) = static_cast<short>(FLOAT(0xC8));
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FIELD(short, 0xDC), FIELD(short, 0xD8) * 0.1f + 10.0f);
    }
    if (FIELD(short, 0x62) < 5) {
        FIELD(short, 0xDA) = static_cast<short>(Unknown483300(
            OWNER_OPPONENT_FLOAT(0x48) - FLOAT(0x48) + 100.0f,
            (OWNER_OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / 0.01745328866f);
        if (FIELD(short, 0xDA) > FIELD(short, 0xDC) + 10)
            FIELD(short, 0xDC) = FIELD(short, 0xDC) + 1;
        if (FIELD(short, 0xDA) < FIELD(short, 0xDC) - 10)
            FIELD(short, 0xDC) = FIELD(short, 0xDC) - 1;
        if (FIELD(short, 0xDC) > 90) FIELD(short, 0xDC) = 90;
        if (FIELD(short, 0xDC) < -90) FIELD(short, 0xDC) = -90;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FIELD(short, 0xDC), FIELD(short, 0xD8) * 0.15f + 7.0f);
    }
    FIELD(short, 0xD8) = FIELD(short, 0xD8) + 2;
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned int, 0x7C) != 0 && FIELD(unsigned int, 0x7C) != 6) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(5);
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        FLOAT(0x1C) = 2.0f;
        FLOAT(0x20) = 2.0f;
    }
    if (FIELD(short, 0x62) == 5) {
        FLOAT(0x1C) = FLOAT(0x1C) * 0.85f;
        FLOAT(0x20) = FLOAT(0x20) * 0.85f;
        if (FIELD(unsigned char, 0x11) >= 25) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 25;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0)
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    return;
}

// Native0055CCD6..0055CDFD observation chunk; no standalone unit or credit.
case 819:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x28) = FIELD(signed char, 0x66) * 35;
        FLOAT(0x2C) = 70.0f;
        FLOAT(0x30) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 359);
    }
    FLOAT(0x1C) = FLOAT(0x1C) * 1.05f;
    FLOAT(0x20) = FLOAT(0x20) * 1.05f;
    FLOAT(0x30) = FLOAT(0x30) + 6.0f;
    if (FIELD(unsigned char, 0x11) > 10) {
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 10;
    } else {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055CDFD..0055CEE8 observation chunk; no standalone unit or credit.
case 820:
    if (OWNER(short, 0x60) == 703 || OWNER(short, 0x60) == 708 || OWNER(short, 0x60) == 741) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055CEE8..0055D2B4 observation chunk; no standalone unit or credit.
case 821: {
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i821 = 0; i821 < 10; i821++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        FIELD(short, 0xDC) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 6;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FIELD(short, 0xDA), 25.0f);
    FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    if (FIELD(unsigned int, 0x7C) == 4 && FIELD(short, 0x80) > 0)
        FIELD(unsigned int, 0x7C) = 0;
    // Preserve both independently observed nonzero flag reads.
    if (FIELD(unsigned int, 0x7C) != 0 && FIELD(unsigned int, 0x7C) != 0)
        FIELD(short, 0x80) = 0;
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned int, 0x7C) != 0) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(4);
    if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
        OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(837, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
    }
    if (FIELD(short, 0x62) == 9 && FIELD(short, 0x64) == 0) {
        OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(837, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
    }
    return;
}

// Native0055D2B4..0055D3BF observation chunk; no standalone unit or credit.
case 822:
    if (OWNER(short, 0x60) == 502) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (OWNER(short, 0x60) != 502 || (OWNER(short, 0x60) == 502 && OWNER(short, 0x62) > 15)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055D3BF..0055D4CA observation chunk; no standalone unit or credit.
case 823:
    if (OWNER(short, 0x60) == 503) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (OWNER(short, 0x60) != 503 || (OWNER(short, 0x60) == 503 && OWNER(short, 0x62) > 15)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055D4CA..0055D5EF observation chunk; no standalone unit or credit.
case 824:
    if (OWNER(short, 0x60) == 504) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (OWNER(short, 0x60) != 504 || (OWNER(short, 0x60) == 504 && OWNER(short, 0x62) > 15)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 80.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x30) = -(FLOAT(0xC8) + 15.0f);
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055D5EF..0055D6D4 observation chunk; no standalone unit or credit.
case 825:
    if (OWNER(short, 0x60) == 304) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (OWNER(short, 0x60) != 304) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055D6D4..0055D883 observation chunk; no standalone unit or credit.
case 826:
    if (OWNER(short, 0x60) == 510 || OWNER(short, 0x60) == 511) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if ((OWNER(short, 0x60) != 510 && OWNER(short, 0x60) != 511) ||
        (OWNER(short, 0x60) == 510 && OWNER(short, 0x62) > 7) ||
        (OWNER(short, 0x60) == 511 && OWNER(short, 0x62) > 11)) {
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 30;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        if (OWNER(short, 0x60) == 511) {
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FLOAT(0x30) = 20.0f;
        }
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
    return;

// Native0055D883..0055D9C5 observation chunk; no standalone unit or credit.
case 827:
    if ((OWNER(short, 0x60) == 700 || OWNER(short, 0x60) == 705) && FIELD(short, 0x62) < 19)
        FLOAT(0x44) = OWNER_FLOAT(0x44);
    if ((OWNER(short, 0x60) != 700 && OWNER(short, 0x60) != 705) ||
        (OWNER(short, 0x60) == 700 && OWNER(short, 0x62) > 7)) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055D9C5..0055DAA5 observation chunk; no standalone unit or credit.
case 828:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 45.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1640.0f || FLOAT(0x44) < -360.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DAA5..0055DB85 observation chunk; no standalone unit or credit.
case 829:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 2.0f;
        FLOAT(0x20) = 2.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 45.0f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    if (FLOAT(0x44) > 1640.0f || FLOAT(0x44) < -360.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DB85..0055DC5D observation chunk; no standalone unit or credit.
case 830:
    if (OWNER(short, 0x60) == 310) FLOAT(0x44) = OWNER_FLOAT(0x44);
    if (OWNER(short, 0x60) != 310) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    return;

// Native0055DC5D..0055DD22 observation chunk; no standalone unit or credit.
case 831:
    if (OWNER(short, 0x60) == 309) FLOAT(0x44) = OWNER_FLOAT(0x44);
    if (OWNER(short, 0x60) != 309) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    return;

// Native0055DD22..0055DE5F observation chunk; no standalone unit or credit.
case 832:
    if ((OWNER(short, 0x60) == 700 || OWNER(short, 0x60) == 705) && FIELD(short, 0x62) < 19)
        FLOAT(0x44) = OWNER_FLOAT(0x44);
    if ((OWNER(short, 0x60) != 700 && OWNER(short, 0x60) != 705) ||
        (OWNER(short, 0x60) == 705 && OWNER(short, 0x62) > 7)) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 2.0f;
        FLOAT(0x20) = 2.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DE5F..0055DF37 observation chunk; no standalone unit or credit.
case 833:
    if (OWNER(short, 0x60) == 307) FLOAT(0x44) = OWNER_FLOAT(0x44);
    if (OWNER(short, 0x60) != 307) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    return;

// Native0055DF37..0055E00F observation chunk; no standalone unit or credit.
case 834:
    if (OWNER(short, 0x60) == 307) FLOAT(0x44) = OWNER_FLOAT(0x44);
    if (OWNER(short, 0x60) != 307) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (OWNER(short, 0x82) == 0 && SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    return;

// Native0055E00F..0055E158 observation chunk; no standalone unit or credit.
case 835:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 0;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FLOAT(0x30) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 359);
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (FIELD(unsigned int, 0x7C) == 6) {
        FIELD(unsigned int, 0x7C) = 0;
        FIELD(short, 0x80)++;
    }
    if (FIELD(unsigned int, 0x7C) == 4) FIELD(unsigned int, 0x7C) = 0;
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055E158..0055E250 observation chunk; no standalone unit or credit.
case 836:
    if (OWNER(short, 0x60) == 709 && FIELD(short, 0x62) < 16) {
        FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 55;
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 86.0f;
    } else {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.5f;
        FLOAT(0x20) = 3.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x30) = -120.0f;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055E250..0055E41C observation chunk; no standalone unit or credit.
case 837:
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 0.5f;
        FLOAT(0x20) = 0.5f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x2C) = 60.0f;
        FLOAT(0x28) = -FIELD(signed char, 0x66) * FLOAT(0xC8);
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        FIELD(short, 0xD8) = 10;
        FIELD(unsigned int, 0x7C) = 0;
    }
    FLOAT(0x30) = FLOAT(0x30) + 1.0f;
    FLOAT(0x1C) = FIELD(short, 0xD8) * 0.05f + 0.05f + FLOAT(0x1C);
    FLOAT(0x20) = FIELD(short, 0xD8) * 0.05f + 0.05f + FLOAT(0x20);
    if (FIELD(short, 0xD8) > 0) FIELD(short, 0xD8)--;
    if (FIELD(short, 0x62) == 2) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
            FIELD(unsigned char, 0x14) = FIELD(unsigned char, 0x14) - 20;
            FIELD(unsigned char, 0x13) = FIELD(unsigned char, 0x13) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055E41C..0055E813 observation chunk; no standalone unit or credit.
case 838: {
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i838 = 0; i838 < 10; i838++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        FIELD(short, 0xDC) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 6;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FIELD(short, 0xDA), 3.0f);
    FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    if (FIELD(unsigned int, 0x7C) == 4 && FIELD(short, 0x80) > 0)
        FIELD(unsigned int, 0x7C) = 0;
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x80) == 0) {
        if (FIELD(unsigned char, 0x11) > 20) {
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(4);
    if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
        OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(837, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
        if (FIELD(unsigned int, 0x7C) == 2)
            FIELD(unsigned int, 0x7C) = 0;
        else
            SELF_VIEW(AnimationState)->ResetPrimaryCounters(821);
    }
    if (FIELD(short, 0x62) == 9 && FIELD(short, 0x64) == 0) {
        OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(837, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
        if (FIELD(unsigned int, 0x7C) == 2)
            FIELD(unsigned int, 0x7C) = 0;
        else
            SELF_VIEW(AnimationState)->ResetPrimaryCounters(821);
    }
    return;
}

// Native0055E813..0055EB1A observation chunk; no standalone unit or credit.
case 839: {
    if (FIELD(unsigned int, 0x7C) == 5) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(BattleEffect)->ClearField74();
        if (OWNER(short, 0xEFA) > 25) {
            OWNER(short, 0xEFA) = 0;
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        for (int i839 = 0; i839 < 10; i839++)
            OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 3;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 0;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 18.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0)
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(835, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
    FLOAT(0x50) = FLOAT(0x50) - 0.45f;
    if (FLOAT(0x50) < -18.0f) FLOAT(0x50) = -18.0f;
    if (FIELD(unsigned int, 0x7C) == 4) FIELD(unsigned int, 0x7C) = 0;
    if (FIELD(short, 0x80) == 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        if (FIELD(short, 0xD8) < 7) {
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
            FIELD(unsigned int, 0x7C) = 0;
            FIELD(short, 0xD8)++;
            return;
        } else {
            SELF_VIEW(BattleEffect)->ClearField74();
        }
    }
    return;
}

// Native0055EB1A..0055ED0A observation chunk; no standalone unit or credit.
case 850:
    FIELD(signed char, 0x66) = OWNER(signed char, 0x66);
    if (OWNER(short, 0x60) > 149 && OWNER(short, 0x60) < 154) {
        FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 30;
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 94.0f;
    }
    if (OWNER(short, 0x60) > 153 && OWNER(short, 0x60) < 158) {
        FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 70;
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 60.0f;
    }
    if (OWNER(short, 0x60) == 158) {
        FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
    }
    if ((OWNER(short, 0x60) < 150 || OWNER(short, 0x60) > 158) && FIELD(short, 0x62) == 0)
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055ED0A..0055EF01 observation chunk; no standalone unit or credit.
case 900:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FLOAT(0xC8), 40.0f);
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    OWNER_FLOAT(0x314) = -FLOAT(0xC8);
    OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(901,
        SELF_VIEW(RecordedRange455580)->SelectRange(0, 60) + FLOAT(0x44) - 30.0f,
        FLOAT(0x48) + 30.0f - SELF_VIEW(RecordedRange455580)->SelectRange(0, 60),
        FIELD(signed char, 0x66), 1);
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
        FIELD(unsigned int, 0x7C) = 0;
    }
    return;

// Native0055EF01..0055F14D observation chunk; no standalone unit or credit.
case 901:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 5);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            -FLOAT(0xC8) + 20.0f - SELF_VIEW(RecordedRange455580)->SelectRange(0, 40),
            SELF_VIEW(RecordedRange455580)->SelectRange(5, 10));
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1300.0f || FLOAT(0x44) < -60.0f ||
        FLOAT(0x48) > 960.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0) {
        if (FIELD(short, 0xD8) * 0.1f + 0.5f > FLOAT(0x1C)) {
            FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
            FLOAT(0x20) = FLOAT(0x1C);
        } else {
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
            return;
        }
    }
    if (FIELD(short, 0x62) == 2) {
        FLOAT(0x1C) = FLOAT(0x1C) * 0.9f;
        FLOAT(0x20) = FLOAT(0x1C);
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055F14D..0055F208 observation chunk; no standalone unit or credit.
case 902:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 4.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x30) = -FLOAT(0xC8);
    }
    // The actual multiplier is the complete eight-byte0.85 literal.
    FLOAT(0x20) = FLOAT(0x20) * 0.85;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055F208..0055F43A observation chunk; no standalone unit or credit.
case 903:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 5);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            SELF_VIEW(RecordedRange455580)->SelectRange(0, 359),
            SELF_VIEW(RecordedRange455580)->SelectRange(5, 10));
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1300.0f || FLOAT(0x44) < -60.0f ||
        FLOAT(0x48) > 960.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0) {
        if (FIELD(short, 0xD8) * 0.1f + 0.5f > FLOAT(0x1C)) {
            FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
            FLOAT(0x20) = FLOAT(0x1C);
        } else {
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
            return;
        }
    }
    if (FIELD(short, 0x62) == 2) {
        FLOAT(0x1C) = FLOAT(0x1C) * 0.9f;
        FLOAT(0x20) = FLOAT(0x1C);
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055F43A..0055F631 observation chunk; no standalone unit or credit.
case 904:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(FLOAT(0xC8), 40.0f);
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    OWNER_FLOAT(0x314) = -FLOAT(0xC8);
    OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(901,
        SELF_VIEW(RecordedRange455580)->SelectRange(0, 60) + FLOAT(0x44) - 30.0f,
        FLOAT(0x48) + 30.0f - SELF_VIEW(RecordedRange455580)->SelectRange(0, 60),
        FIELD(signed char, 0x66), 1);
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
        FIELD(unsigned int, 0x7C) = 0;
    }
    return;

// Native0055F631..0055F8F2 observation chunk; no standalone unit or credit.
case 905:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) == 751 && FIELD(short, 0x62) < 2) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 250.0f;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 1) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.05f;
        FLOAT(0x20) = FLOAT(0x20) + 0.05f;
        if (FLOAT(0x1C) > 1.0f) {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
        }
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    FLOAT(0x30) = FLOAT(0x30) + 2.0f;
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f ||
        FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        FIELD(unsigned int, 0x7C) = 0;
        return;
    }
    if (FIELD(short, 0x64) == 0) FIELD(unsigned int, 0x7C) = 0;
    if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
        OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(17);
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(Unknown483300(
            OWNER_OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
            (OWNER_OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / 0.01745328866f, 20.0f);
    }
    return;

// Native0055F8F2..0055FA76 observation chunk; no standalone unit or credit.
case 906:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 1) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
        FLOAT(0x20) = FLOAT(0x20) + 0.1f;
        if (FIELD(short, 0x64) > 15) {
            if (FIELD(unsigned char, 0x11) > 15)
                FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 15;
            else
                FIELD(unsigned char, 0x11) = 0;
        }
    }
    FLOAT(0x30) = FLOAT(0x30) + 2.0f;
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f ||
        FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055FA76..0055FD08 observation chunk; no standalone unit or credit.
case 907:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if ((OWNER(short, 0x60) == 751 || OWNER(short, 0x60) == 753) && FIELD(short, 0x62) < 2) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 250.0f;
    }
    if ((OWNER(short, 0x60) == 751 || OWNER(short, 0x60) == 753) &&
        OWNER(short, 0x62) > 7 && FIELD(short, 0x62) < 2) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 0) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
        FLOAT(0x20) = FLOAT(0x20) + 0.1f;
        if (FLOAT(0x1C) > 1.0f) {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
        }
    }
    if (FIELD(short, 0x62) == 2) {
        FLOAT(0x1C) = FLOAT(0x20) * 0.85f;
        FLOAT(0x20) = FLOAT(0x20) * 0.85f;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        FIELD(unsigned int, 0x7C) = 0;
        return;
    }
    if (FIELD(short, 0x64) == 0) FIELD(unsigned int, 0x7C) = 0;
    if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xDA) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 40);
        FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.8f;
        FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.8f;
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    }
    return;

// Native0055FD08..0055FEFA observation chunk; no standalone unit or credit.
case 908:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) == 752 && FIELD(short, 0x62) < 2) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = 0.0f;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x28) = 75.0f;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 1) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
        FLOAT(0x20) = FLOAT(0x20) + 0.1f;
        if (FLOAT(0x1C) > 1.0f) {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
        }
    }
    if (FIELD(short, 0x62) == 2) {
        if (FIELD(unsigned char, 0x11) > 15)
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 15;
        else
            FIELD(unsigned char, 0x11) = 0;
    }
    FLOAT(0x30) = FLOAT(0x30) + 2.0f;
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f ||
        FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0055FEFA..0056001A observation chunk; no standalone unit or credit.
case 909:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 0) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.5f;
        FLOAT(0x20) = FLOAT(0x20) + 2.0f;
    }
    if (FIELD(short, 0x62) > 0) {
        FLOAT(0x1C) = FLOAT(0x1C) * 0.85f;
        FLOAT(0x20) = FLOAT(0x20) + 0.2f;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0056001A..00560140 observation chunk; no standalone unit or credit.
case 910:
    if (OWNER(short, 0x60) == 741) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48);
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xDA) = 0;
    }
    if (OWNER(short, 0x82) == 0) {
        if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
            SELF_VIEW(BattleEffect)->ClearField74();
        if (FIELD(short, 0x62) == 38 && FIELD(short, 0x64) == 0 &&
            FIELD(short, 0xDA) < (3 - g_StateRepeatLevelAt006714D0) * 2) {
            FIELD(short, 0xDA)++;
            SELF_VIEW(AnimationState)->ResetSecondaryCounter(37);
        }
    }
    break;

// Native00560140..0056030A observation chunk; no standalone unit or credit.
case 911:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (OWNER(short, 0x60) == 752 && FIELD(short, 0x62) < 2) {
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = 0.0f;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FLOAT(0x1C) = 0.0f;
        FLOAT(0x20) = 0.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x28) = 75.0f;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
    }
    if (FIELD(short, 0x62) == 1) {
        FLOAT(0x1C) = FLOAT(0x1C) + 0.1f;
        FLOAT(0x20) = FLOAT(0x20) + 0.1f;
        if (FIELD(short, 0x64) > 15) {
            if (FIELD(unsigned char, 0x11) > 15)
                FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 15;
            else
                FIELD(unsigned char, 0x11) = 0;
        }
    }
    FLOAT(0x30) = FLOAT(0x30) + 2.0f;
    if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f ||
        FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0056030A..0056052B observation chunk; no standalone unit or credit.
case 912:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = -SELF_VIEW(RecordedRange455580)->SelectRange(
            0, g_StateRepeatLevelAt006714D0 * 3 + 40) - 20;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 0.25f;
        FLOAT(0x20) = 0.25f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xD8)), 30.0f);
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        FLOAT(0x48) = 0.0f;
        OWNER_VIEW(FighterShake453E60)->SetCameraShake(3.0f);
        SELF_VIEW(AnimationState)->ResetPrimaryCounters(909);
        FLOAT(0x30) = 0.0f;
        FIELD(unsigned char, 0x11) = 0;
        OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(22);
        return;
    }
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -120.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native0056052B..005606D8 observation chunk; no standalone unit or credit.
case 913:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xDA)), 18.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 2)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native005606D8..005608E6 observation chunk; no standalone unit or credit.
case 914:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            static_cast<float>(FIELD(short, 0xDA) + 10 - SELF_VIEW(RecordedRange455580)->SelectRange(0, 20)),
            static_cast<float>(SELF_VIEW(RecordedRange455580)->SelectRange(0, 9) + 6));
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if ((FIELD(unsigned int, 0x7C) == 1 || FIELD(unsigned int, 0x7C) == 2 ||
         FIELD(unsigned int, 0x7C) == 4) && FIELD(short, 0x62) < 2) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(2);
        return;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 2)
        FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native005608E6..00560F35 observation chunk; no standalone unit or credit.
case 915:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = static_cast<short>(FLOAT(0xC8));
        FIELD(short, 0xDC) = 0;
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xDA)), 7.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    FIELD(short, 0xD8)--;
    if (g_StateRepeatLevelAt006714D0 == 3 && ++FIELD(short, 0xDA) > 180)
        FIELD(short, 0xDA) = FIELD(short, 0xDA) - 360;
    SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xDA)), 7.0f);
    if (FIELD(short, 0xD8) <= 0) {
        OWNER_FLOAT(0x314) = static_cast<float>(FIELD(short, 0xDA));
        OWNER_VIEW(FighterEffectPoliciesF135)->SpawnBattleEffect(
            916, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
        FIELD(short, 0xD8) = 10 - g_StateRepeatLevelAt006714D0;
    }
    if (g_StateRepeatLevelAt006714D0 > 0) {
        if (FLOAT(0x48) > OWNER_FLOAT(0x2E0) && FIELD(short, 0xDC) < 1 && FLOAT(0x54) < 0.0f) {
            OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(11);
            FIELD(short, 0xDA) = -FIELD(short, 0xDA);
            FIELD(short, 0xDC)++;
            FIELD(unsigned int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
            FLOAT(0xCC) = 4.0f;
        }
        if (FLOAT(0x48) < 0.0f && FIELD(short, 0xDC) < 1 && FLOAT(0x54) > 0.0f) {
            OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(11);
            FIELD(short, 0xDA) = -FIELD(short, 0xDA);
            FIELD(short, 0xDC)++;
            FIELD(unsigned int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
            FLOAT(0xCC) = 4.0f;
        }
        if (FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(short, 0xDC) < 1 &&
            ((FIELD(signed char, 0x66) == -1 && FLOAT(0x50) > 0.0f) ||
             (FIELD(signed char, 0x66) == 1 && FLOAT(0x50) < 0.0f))) {
            OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(11);
            if (FIELD(short, 0xDA) > 0)
                FIELD(short, 0xDA) = 180 - FIELD(short, 0xDA);
            if (FIELD(short, 0xDA) < 0)
                FIELD(short, 0xDA) = -180 - FIELD(short, 0xDA);
            FIELD(short, 0xDC)++;
            FIELD(unsigned int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
            FLOAT(0xCC) = 4.0f;
        }
        if (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(short, 0xDC) < 1 &&
            ((FIELD(signed char, 0x66) == -1 && FLOAT(0x50) < 0.0f) ||
             (FIELD(signed char, 0x66) == 1 && FLOAT(0x50) > 0.0f))) {
            OWNER_VIEW(FighterEffectPoliciesF135)->PlaySound(11);
            if (FIELD(short, 0xDA) > 0)
                FIELD(short, 0xDA) = 180 - FIELD(short, 0xDA);
            if (FIELD(short, 0xDA) < 0)
                FIELD(short, 0xDA) = -180 - FIELD(short, 0xDA);
            FIELD(short, 0xDC)++;
            FIELD(unsigned int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
            FLOAT(0xCC) = 4.0f;
        }
    }
    if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f ||
        FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 2) {
        if (FIELD(unsigned char, 0x11) > 20)
            FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 20;
        else {
            SELF_VIEW(BattleEffect)->ClearField74();
            return;
        }
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(BattleEffect)->ClearField74();
    return;

// Native00560F35..00561265 observation chunk; no standalone unit or credit.
case 916:
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(unsigned int, 0x7C) = 0;
        FLOAT(0x1C) = 3.0f;
        FLOAT(0x20) = 3.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = static_cast<short>(
            SELF_VIEW(RecordedRange455580)->SelectRange(0, 40) + FLOAT(0xC8) - 20.0f);
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            static_cast<float>(FIELD(short, 0xDA)), FIELD(short, 0xD8) * 0.05f);
        FLOAT(0x30) = Unknown483300(FLOAT(0x54), FLOAT(0x50)) / 0.01745328866f;
        FIELD(unsigned int, 0x7C) = 0;
        FIELD(short, 0x80) = 1;
    }
    if (FIELD(short, 0x62) == 1) {
        FLOAT(0x1C) = FLOAT(0x1C) - 0.1f;
        FLOAT(0x20) = FLOAT(0x20) - 0.1f;
        if (FLOAT(0x1C) < 1.0f) {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
        }
    }
    if (FIELD(short, 0x62) == 2 && FIELD(unsigned int, 0x7C) != 0) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(3);
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = 0.0f;
        return;
    }
    if (FIELD(short, 0x62) == 3) {
        FLOAT(0x1C) = FLOAT(0x1C) * 0.8f;
        FLOAT(0x20) = FLOAT(0x20) * 0.8f;
    }
    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f ||
        FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    if (FIELD(short, 0x62) == 2) {
        FIELD(short, 0xD8)++;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            static_cast<float>(FIELD(short, 0xDA)), FIELD(short, 0xD8) * 0.05f);
    }
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    break;

// Native00561265..00561591 observation chunk; no standalone unit or credit.
case 995:
    FIELD(signed char, 0x66) = 1;
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = -1.0f;
        FIELD(short, 0xD8) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 360) - 180;
        FIELD(short, 0xDA) = 15;
    }
    if (FIELD(short, 0x62) == 0) {
        FIELD(short, 0xDA)--;
        if (FIELD(short, 0xDA) < 3)
            FIELD(short, 0xDA) = 3;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            static_cast<float>(FIELD(short, 0xD8)), FIELD(short, 0xDA) * 0.8f);
    }
    if (FIELD(short, 0x62) == 1) {
        FIELD(short, 0xD8) = static_cast<short>(Unknown483300(
            OWNER_OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
            OWNER_OPPONENT_FLOAT(0x44) - FLOAT(0x44)) / 0.01745328866f);
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xD8)), 20.0f);
        if (FLOAT(0x44) - OWNER_OPPONENT_FLOAT(0x44) < 20.0f &&
            FLOAT(0x44) - OWNER_OPPONENT_FLOAT(0x44) > -20.0f &&
            FLOAT(0x48) - OWNER_OPPONENT_FLOAT(0x48) < 120.0f &&
            FLOAT(0x48) - OWNER_OPPONENT_FLOAT(0x48) > 80.0f) {
            SELF_VIEW(BattleEffect)->ClearField74();
            if (OWNER_OPPONENT(signed char, 0x366) < 2)
                OWNER_OPPONENT(signed char, 0x366)++;
            else
                OWNER_OPPONENT(int, 0x2D0) = OWNER_OPPONENT(int, 0x2D0) + 20000;
            SELF_VIEW(EffectSound45B860)->PlaySharedSound(46);
            return;
        }
    }
    FLOAT(0x44) = FLOAT(0x44) + FLOAT(0x50);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    break;

// Native00561591..005619F7 observation chunk; no standalone unit or credit.
case 996:
    FIELD(signed char, 0x66) = 1;
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FLOAT(0x50) = 0.0f;
        FLOAT(0x54) = -1.0f;
        FIELD(short, 0xD8) = SELF_VIEW(RecordedRange455580)->SelectRange(0, 360) - 180;
        FIELD(short, 0xDA) = 15;
    }
    if (FIELD(short, 0x62) == 0) {
        FIELD(short, 0xDA)--;
        if (FIELD(short, 0xDA) < 3)
            FIELD(short, 0xDA) = 3;
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(
            static_cast<float>(FIELD(short, 0xD8)), FIELD(short, 0xDA) * 0.8f);
    }
    if (FIELD(short, 0x62) == 1) {
        FIELD(short, 0xD8) = static_cast<short>(Unknown483300(
            OWNER_OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
            OWNER_OPPONENT_FLOAT(0x44) - FLOAT(0x44)) / 0.01745328866f);
        SELF_VIEW(ObjectMotion40FB70)->SetPolarVelocity(static_cast<float>(FIELD(short, 0xD8)), 20.0f);
        if (FLOAT(0x44) - OWNER_OPPONENT_FLOAT(0x44) < 20.0f &&
            FLOAT(0x44) - OWNER_OPPONENT_FLOAT(0x44) > -20.0f &&
            FLOAT(0x48) - OWNER_OPPONENT_FLOAT(0x48) < 120.0f &&
            FLOAT(0x48) - OWNER_OPPONENT_FLOAT(0x48) > 80.0f) {
            OWNER(short, 0xEFA)++;
            SELF_VIEW(EffectSound45B860)->PlaySharedSound(46);
            SELF_VIEW(BattleEffect)->ClearField74();
            if (OWNER_OPPONENT(short, 0x3B6) > 0) {
                if (OWNER_OPPONENT(short, 0x3B6) > 5)
                    OWNER_OPPONENT(short, 0x3B6) = OWNER_OPPONENT(short, 0x3B6) - 5;
                else {
                    OWNER_OPPONENT(short, 0x3B6) = 0;
                    OWNER_OPPONENT(short, 0x3B0) = 1000;
                }
                return;
            } else {
                if (OWNER_OPPONENT(short, 0x3B0) < 990)
                    OWNER_OPPONENT(short, 0x3B0) = OWNER_OPPONENT(short, 0x3B0) + 10;
                else {
                    OWNER_OPPONENT(short, 0x3B0) = 1000;
                    if (OWNER_OPPONENT(unsigned char, 0x39C) == 0) {
                        if (OWNER_OPPONENT_FLOAT(0x36C) < 998.9)
                            OWNER_OPPONENT_FLOAT(0x36C) = OWNER_OPPONENT_FLOAT(0x36C) + 0.5f;
                        else
                            OWNER_OPPONENT_FLOAT(0x36C) = 900.0f;
                    }
                }
            }
            return;
        }
    }
    FLOAT(0x44) = FLOAT(0x44) + FLOAT(0x50);
    FLOAT(0x48) = FLOAT(0x48) - FLOAT(0x54);
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70))
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(1);
    break;

// Native005619F7..00561B83 observation chunk; no standalone unit or credit.
case 997:
    FLOAT(0x44) = OWNER_FLOAT(0x44);
    FLOAT(0x48) = 0.0f;
    FIELD(short, 0x8A) = 1;
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
        SELF_VIEW(SpriteTransform40FBB0)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 3.0f;
        FLOAT(0x20) = 3.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(short, 0x1A) = 1250;
        FLOAT(0x2C) = 0.0f;
        FLOAT(0x30) = 0.0f;
        FLOAT(0x28) = -80.0f;
        FIELD(short, 0xD8) = OWNER(short, 0x3A0);
    }
    if (OWNER(short, 0x3A0) <= 0) {
        SELF_VIEW(BattleEffect)->ClearField74();
        return;
    }
    FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2.0f;
    FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2.0f;
    FLOAT(0x30) = FLOAT(0x30) + 1.0f;
    if (SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        SELF_VIEW(AnimationState)->ResetSecondaryCounter(9);
        return;
    }
    break;

    default:
        SELF_VIEW(AnimationProgress40FA30)->AdvanceNestedFrame();
        break;
    }
}

#undef OWNER_VIEW
#undef SELF_VIEW
#undef OWNER_OPPONENT_FLOAT
#undef OWNER_OPPONENT
#undef OWNER_FLOAT
#undef OWNER
#undef FLOAT
#undef FIELD
