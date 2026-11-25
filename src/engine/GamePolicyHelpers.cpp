#include "battle/FighterFrameFlags.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/TextOverlay.hpp"
#include "graphics/FontSurface.hpp"
#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/BackgroundStageBaseF479.hpp"

void NativeBackgroundBaseF479::CopyParameters(BackgroundStageFloatFieldsF933* destination)
{
    *destination = parameters.floating;
}

void SpriteScene::DispatchGlobalDraw(SpriteQuad40CA80* destination, DWORD* color, SpriteQuad40CA80* source)
{
    g_CurrentBattleStageAt00671424->ApplyTransform(destination, color, source);
}

u8 FontSurface::DecodeHexDigit(char digit)
{
    if (static_cast<unsigned char>(digit) >= 'a' && static_cast<unsigned char>(digit) <= 'f')
        return static_cast<unsigned char>(digit) - 'a' + 10;
    if (static_cast<unsigned char>(digit) >= 'A' && static_cast<unsigned char>(digit) <= 'F')
        return static_cast<unsigned char>(digit) - 'A' + 10;
    if (static_cast<unsigned char>(digit) >= '0' && static_cast<unsigned char>(digit) <= '9')
        return static_cast<unsigned char>(digit) - '0';
    return 0;
}

void BattleScene::DrawSelectedNotice()
{
    fighters[matchWinnerSide]->DrawFacingSprite(fighters[matchWinnerSide]->noticeBadge, victoryBadgeX, 0.0f, 0xffffffffUL);
    g_TextRenderer->DrawBox();
}

bool Fighter::IsGroundedStateWindow()
{
    return y > FloatConstants::Zero
        && flashGauge == 0
        && IsState50To149()
        && (frameInfo->flags & FrameFlags::DisablesAirRecovery) == 0;
}

void Fighter::ConfigureNoticeText(u8 enabled)
{
    if (enabled) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, g_StageAt0067161E < 8);
        noticeEnabled = 1;
    } else {
        noticeEnabled = 0;
    }
}

void Fighter::BeginNoticeTransition(u8 notice, u8 direction)
{
    noticeState = 2 - direction;
    SetNoticeFields(notice, 1, direction * 0x7F + 0x80);
    noticeAxis = 0x10;
}

void Fighter::InitializeNotice(short value)
{
    scriptId = value;
    scriptIndex = 0;
    scriptBitMask = 0;
    scriptStep = 5;
    ConfigureNoticeText(1);
}
