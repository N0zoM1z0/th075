#include "CombatTimers.hpp"
#define FIELD_AT(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define SELF(type, offset) FIELD_AT(type, this, offset)
void Fighter::UpdateCounters()
{
    // Opponent freeze suspends counters but not view bounds and the frame count.
    if (opponent->field3BA > 0) goto updateViewBounds;
    {
        if (field082 > 0) --field082;
        else if (field3CC > 0) --field3CC;
        field490 = 0.0f;
        opponent->field490 = 0.0f;
        if (field084 > 0) --field084;
        if (field086 > 0) --field086;
        if (FIELD_AT(unsigned long, frameInfo, 0x3C) & 0x1000) field086 = 6;
        if (field088 > 0) --field088;
        if (field3BC > 0) --field3BC;
        if (field3A0 > 0) {
            if (field2CD == 0 || g_CombatMode != 3) {
                field3A0 -= 2;
                if (field3A0 <= 0) {
                    field3A0 = 0;
                    field39C = 1;
                    field36C = 0.0f;
                }
            } else {
                reinterpret_cast<int&>(field3A4) -= reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x430)[field39D];
                if (reinterpret_cast<int&>(field3A4) < 0) reinterpret_cast<int&>(field3A4) = 0;
                --reinterpret_cast<int&>(field3A8);
                if (reinterpret_cast<int&>(field3A8) < 0) reinterpret_cast<int&>(field3A8) = 0;
            }
        }
        if (field368 > 0.0f && field39C == 0) {
            if (field3A0 != 0) {
                field368 -= 0.4f;
                field36C += 0.02f;
            } else {
                field368 -= 4.0f;
                field36C += 0.2f;
            }
        }
        if (field36C < 0.0f) field36C = 0.0f;
        if (field36C > 900.0f) field36C = 900.0f;
        if (field368 < 0.0f) field368 = 0.0f;
        if (field368 > 1000.0f) field368 = 1000.0f;
        if (g_CombatMode == 3 && field2CD != 0) field36C = 900.0f;
        if (g_CombatMode != 3 || field2CD == 0) {
            if (field3A0 > 0 && recoverableHealth > health) health += 100;
            if (recoverableHealth < health) health = recoverableHealth;
        }
        if (meterCooldown > 0) {
            meterCooldown -= 2;
            meter = 0;
            if (meterCooldown <= 0) {
                reinterpret_cast<CombatTimerActor *>(this)->PlaySharedSound(47);
                meter = 1000;
            }
        } else if (meter < meterPrevious) {
            meterWait = 60;
        } else if (meterWait > 0) {
            --meterWait;
        } else {
            if ((!reinterpret_cast<CombatTimerActor *>(this)->IsState150To199() ||
                (action != 209 && action != 210)) && meterWait == 0)
                meter += 3;
            if (meter > 1000) meter = 1000;
        }
        meterPrevious = meter;
    }
updateViewBounds:
    if (health < 0) health = 0;
    if (recoverableHealth < 0) recoverableHealth = 0;
    if (field47C > 0) --field47C;
    if (field484 > 0) --field484;
    if (fadeAlpha > 0) fadeAlpha -= 3;
    field2D8 = (-g_CombatViewOffsetX - 320.0f + 640.0f) - (320.0f - g_CombatViewSpan) * 0.5f;
    field2DC = (-g_CombatViewOffsetX + 320.0f + 640.0f) + (320.0f - g_CombatViewSpan) * 0.5f;
    field2E0 = (g_CombatViewOffsetY - 300.0f + 420.0f) + (320.0f - g_CombatViewSpan) * 210.0f / 320.0f;
    field2E4 = (g_CombatViewOffsetY - 300.0f - 60.0f) - (320.0f - g_CombatViewSpan) * 30.0f / 320.0f;
    ++fieldEF8;
}
