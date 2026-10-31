#include "FighterNoticeBorrowedF960.hpp"
#include "GameLeafHelpers.hpp"

void SpriteScene::CopyVector(Vector3 *destination)
{
    *destination = *reinterpret_cast<Vector3 *>(
        reinterpret_cast<u8 *>(this) + 0x0C);
}

void SpriteScene::DispatchGlobalDraw(int first, int second, int third)
{
    g_DrawDispatcher->Draw(first, second, third);
}

u8 TextRasterizer::DecodeHexDigit(u8 value)
{
    if (value >= 'a' && value <= 'f')
        return value - 'a' + 10;
    if (value >= 'A' && value <= 'F')
        return value - 'A' + 10;
    if (value >= '0' && value <= '9')
        return value - '0';
    return 0;
}

void BattleHud::DrawSelectedNotice()
{
    (*reinterpret_cast<FighterState **>(
        reinterpret_cast<u8 *>(this) + 0x44 +
        *(reinterpret_cast<signed char *>(this) + 0x5D) * 4))->DrawFacingSprite(
        F960_BADGE(*reinterpret_cast<FighterState **>(
                reinterpret_cast<u8 *>(this) + 0x44 +
                *(reinterpret_cast<signed char *>(this) + 0x5D) * 4)).noticeAt6E7,
        *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + 0x90),
        0,
        -1);
    g_TextRenderer->DrawBox();
}

bool FighterState::IsGroundedStateWindow()
{
    return *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + 0x48) > g_ZeroFloat
        && *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x3C8) == 0
        && IsState50To149()
        && (*reinterpret_cast<u32 *>(
            reinterpret_cast<u8 *>(
                *reinterpret_cast<FighterState **>(
                    reinterpret_cast<u8 *>(this) + 0x74)) + 0x3C) & 0x100000) == 0;
}

void FighterState::ConfigureNoticeText(u8 enabled)
{
    if (enabled) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, g_NoticeSelection < 8);
        F960_ENABLED_BYTE(this) = 1;
    } else {
        F960_ENABLED_BYTE(this) = 0;
    }
}

void FighterState::BeginNoticeTransition(u8 notice, u8 direction)
{
    F960_TRANSITION_BYTE(this) = 2 - direction;
    SetNoticeFields(notice, 1, direction * 0x7F + 0x80);
    F960_MOTION(this).axisAt6EA = 0x10;
}

void FighterState::InitializeNotice(short value)
{
    F960_COUNTERS(this).stateAt6F0 = value;
    F960_COUNTERS(this).nextAt6F4 = 0;
    F960_COUNTERS(this).priorAt6F2 = 0;
    F960_COUNTERS(this).durationAt6F6 = 5;
    ConfigureNoticeText(1);
}

void BattleState::StartHitSequence(AnimationState *state, short value)
{
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(state) + 0x3B0) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(state) + 0x3B6) = 1000;
    state->ResetPrimaryCounters(value);
    state->ClearByte40();
    SpawnMidpointEffect(0x35, *(reinterpret_cast<u8 *>(state) + 0x66));
    g_SoundBank->Play(0x26);
}
