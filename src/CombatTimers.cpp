#include "FighterActionTimerPairF1027.hpp"
#include "FighterVitalBorrowedF999.hpp"
#include "FighterFadeBorrowedF986.hpp"
#include "FighterGaugeBorrowedF980.hpp"
#include "CombatTimers.hpp"
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define SELF(type, offset) FIELD(type, this, offset)
#define OPPONENT(type, offset) FIELD(type, SELF(void *, 0x2E8), offset)
void FrameActor::UpdateCounters()
{
    // Opponent freeze suspends counters but not view bounds and the frame count.
    if (OPPONENT(short, 0x3BA) > 0) goto updateViewBounds;
    {
        if (F1027_TIMERS(this).timerAt82 > 0) --F1027_TIMERS(this).timerAt82;
        else if (SELF(short, 0x3CC) > 0) --SELF(short, 0x3CC);
        SELF(float, 0x490) = 0.0f;
        OPPONENT(float, 0x490) = 0.0f;
        if (SELF(short, 0x84) > 0) --SELF(short, 0x84);
        if (SELF(short, 0x86) > 0) --SELF(short, 0x86);
        if (FIELD(unsigned long, SELF(void *, 0x74), 0x3C) & 0x1000) SELF(short, 0x86) = 6;
        if (SELF(short, 0x88) > 0) --SELF(short, 0x88);
        if (SELF(short, 0x3BC) > 0) --SELF(short, 0x3BC);
        if (SELF(short, 0x3A0) > 0) {
            if (SELF(signed char, 0x2CD) == 0 || g_CombatMode != 3) {
                SELF(short, 0x3A0) -= 2;
                if (SELF(short, 0x3A0) <= 0) {
                    SELF(short, 0x3A0) = 0;
                    SELF(unsigned char, 0x39C) = 1;
                    SELF(float, 0x36C) = 0.0f;
                }
            } else {
                SELF(int, 0x3A4) -= reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x430)[SELF(signed char, 0x39D)];
                if (SELF(int, 0x3A4) < 0) SELF(int, 0x3A4) = 0;
                --SELF(int, 0x3A8);
                if (SELF(int, 0x3A8) < 0) SELF(int, 0x3A8) = 0;
            }
        }
        if (SELF(float, 0x368) > 0.0f && SELF(unsigned char, 0x39C) == 0) {
            if (SELF(short, 0x3A0) != 0) {
                SELF(float, 0x368) -= 0.4f;
                SELF(float, 0x36C) += 0.02f;
            } else {
                SELF(float, 0x368) -= 4.0f;
                SELF(float, 0x36C) += 0.2f;
            }
        }
        if (SELF(float, 0x36C) < 0.0f) SELF(float, 0x36C) = 0.0f;
        if (SELF(float, 0x36C) > 900.0f) SELF(float, 0x36C) = 900.0f;
        if (SELF(float, 0x368) < 0.0f) SELF(float, 0x368) = 0.0f;
        if (SELF(float, 0x368) > 1000.0f) SELF(float, 0x368) = 1000.0f;
        if (g_CombatMode == 3 && SELF(signed char, 0x2CD) != 0) SELF(float, 0x36C) = 900.0f;
        if (g_CombatMode != 3 || SELF(signed char, 0x2CD) == 0) {
            if (SELF(short, 0x3A0) > 0 && F999_VITAL(this).recoverableAt326 > F999_VITAL(this).currentAt324) F999_VITAL(this).currentAt324 += 100;
            if (F999_VITAL(this).recoverableAt326 < F999_VITAL(this).currentAt324) F999_VITAL(this).currentAt324 = F999_VITAL(this).recoverableAt326;
        }
        if (F980_GAUGE(this).cooldownAt3B6 > 0) {
            F980_GAUGE(this).cooldownAt3B6 -= 2;
            F980_GAUGE(this).meterAt3B0 = 0;
            if (F980_GAUGE(this).cooldownAt3B6 <= 0) {
                reinterpret_cast<CombatTimerActor *>(this)->PlaySharedSound(47);
                F980_GAUGE(this).meterAt3B0 = 1000;
            }
        } else if (F980_GAUGE(this).meterAt3B0 < F980_GAUGE(this).previousAt3B2) {
            F980_GAUGE(this).waitAt3B4 = 60;
        } else if (F980_GAUGE(this).waitAt3B4 > 0) {
            --F980_GAUGE(this).waitAt3B4;
        } else {
            if ((!reinterpret_cast<CombatTimerActor *>(this)->IsState150To199() ||
                (SELF(short, 0x60) != 209 && SELF(short, 0x60) != 210)) && F980_GAUGE(this).waitAt3B4 == 0)
                F980_GAUGE(this).meterAt3B0 += 3;
            if (F980_GAUGE(this).meterAt3B0 > 1000) F980_GAUGE(this).meterAt3B0 = 1000;
        }
        F980_GAUGE(this).previousAt3B2 = F980_GAUGE(this).meterAt3B0;
    }
updateViewBounds:
    if (F999_VITAL(this).currentAt324 < 0) F999_VITAL(this).currentAt324 = 0;
    if (F999_VITAL(this).recoverableAt326 < 0) F999_VITAL(this).recoverableAt326 = 0;
    if (SELF(int, 0x47C) > 0) --SELF(int, 0x47C);
    if (SELF(signed char, 0x484) > 0) --SELF(signed char, 0x484);
    if (F986_FADE(this).fadeAlphaAt538 > 0) F986_FADE(this).fadeAlphaAt538 -= 3;
    SELF(float, 0x2D8) = (-g_CombatViewOffsetX - 320.0f + 640.0f) - (320.0f - g_CombatViewSpan) * 0.5f;
    SELF(float, 0x2DC) = (-g_CombatViewOffsetX + 320.0f + 640.0f) + (320.0f - g_CombatViewSpan) * 0.5f;
    SELF(float, 0x2E0) = (g_CombatViewOffsetY - 300.0f + 420.0f) + (320.0f - g_CombatViewSpan) * 210.0f / 320.0f;
    SELF(float, 0x2E4) = (g_CombatViewOffsetY - 300.0f - 60.0f) - (320.0f - g_CombatViewSpan) * 30.0f / 320.0f;
    ++SELF(short, 0xEF8);
}
