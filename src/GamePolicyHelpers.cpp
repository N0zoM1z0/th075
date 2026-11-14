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
    return y > g_ZeroFloat
        && flashGauge == 0
        && IsState50To149()
        && (frameInfo->flags & 0x100000) == 0;
}

void FighterState::ConfigureNoticeText(u8 enabled)
{
    if (enabled) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, g_NoticeSelection < 8);
        noticeEnabled = 1;
    } else {
        noticeEnabled = 0;
    }
}

void FighterState::BeginNoticeTransition(u8 notice, u8 direction)
{
    reinterpret_cast<unsigned char&>(noticeState) = 2 - direction;
    SetNoticeFields(notice, 1, direction * 0x7F + 0x80);
    noticeAxis = 0x10;
}

void FighterState::InitializeNotice(short value)
{
    scriptId = value;
    scriptIndex = 0;
    scriptBitMask = 0;
    scriptStep = 5;
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
