#include "TextOverlay.hpp"
#include "FontSurface.hpp"
#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"

void SpriteScene::CopyVector(Vector3 *destination)
{
    *destination = field00C;
}

void SpriteScene::DispatchGlobalDraw(int first, int second, int third)
{
    g_DrawDispatcher->Draw(first, second, third);
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
    fighters[field05D]->DrawFacingSprite(fighters[field05D]->noticeBadge, field090, 0, -1);
    g_TextRenderer->DrawBox();
}

bool Fighter::IsGroundedStateWindow()
{
    return y > g_ZeroFloat
        && flashGauge == 0
        && IsState50To149()
        && (frameInfo->flags & 0x100000) == 0;
}

void Fighter::ConfigureNoticeText(u8 enabled)
{
    if (enabled) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, g_NoticeSelection < 8);
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
