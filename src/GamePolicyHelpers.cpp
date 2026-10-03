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
        *(reinterpret_cast<signed char *>(
            *reinterpret_cast<FighterState **>(
                reinterpret_cast<u8 *>(this) + 0x44 +
                *(reinterpret_cast<signed char *>(this) + 0x5D) * 4)) + 0x6E7),
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
        *(reinterpret_cast<u8 *>(this) + 0x6EE) = 1;
    } else {
        *(reinterpret_cast<u8 *>(this) + 0x6EE) = 0;
    }
}

void FighterState::BeginNoticeTransition(u8 notice, u8 direction)
{
    *(reinterpret_cast<u8 *>(this) + 0x6E6) = 2 - direction;
    SetNoticeFields(notice, 1, direction * 0x7F + 0x80);
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x6EA) = 0x10;
}

void FighterState::InitializeNotice(short value)
{
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x6F0) = value;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x6F4) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x6F2) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x6F6) = 5;
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
