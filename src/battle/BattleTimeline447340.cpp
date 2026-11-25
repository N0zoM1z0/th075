#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/BattleTimeline447340.hpp"

#define QUAD reinterpret_cast<SpriteTransform*>(&packet)

void BattleScene::RenderOverlayTimeline() {
    RenderQuadPacket5E68C0 packet;
    textureManager->SetDepthMode(0);
    textureManager->SetBlendMode(0);
    switch (noticeKind) {
        RECT rect;
    case 0:
        SetRect(&rect, elapsedBattleFrames * 5, 0, elapsedBattleFrames * 5 + 640, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f - noticeHorizontalEdgeOffset, 640.0f, 272.0f - noticeHorizontalEdgeOffset);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - elapsedBattleFrames * 5, 0, 640 - elapsedBattleFrames * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f + noticeHorizontalEdgeOffset, 640.0f, 272.0f + noticeHorizontalEdgeOffset);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, elapsedBattleFrames * 5, 0, elapsedBattleFrames * 5 + 480, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f - noticeVerticalEdgeOffset, 560.0f, 272.0f - noticeVerticalEdgeOffset);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - elapsedBattleFrames * 5, 0, 480 - elapsedBattleFrames * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f + noticeVerticalEdgeOffset, 560.0f, 272.0f + noticeVerticalEdgeOffset);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        if (noticeTitleMotion >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            if (noticeTitleMotion > 0.0f) {
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, noticeTitleMotion);
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    noticeTitleMotion / 20.0f + 1.2f, noticeTitleMotion / 20.0f + 1.2f, 1.0f);
            } else {
                if (noticeFrames > 70)
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        noticeTitleMotion / 200.0f + 1.2f, noticeTitleMotion / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        -noticeTitleMotion / 200.0f + 1.2f, noticeTitleMotion / 200.0f + 1.2f, 1.0f);
            }
            textureManager->DrawQuad(4, packet, &rect, 0xFFFFFFFF);
        }
        if (noticeFrames < 140 && noticeFlashScale * 40.0f < 255.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, noticeFlashScale + 1.2f, noticeFlashScale + 1.2f, 1.0f);
            textureManager->SetBlendMode(2);
            textureManager->DrawQuad(6, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(noticeFlashScale * 40.0f), 255, 255, 255));
            textureManager->SetBlendMode(0);
        }
        if (noticeFrames <= 75 && noticeSubtitleMotion > -300.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (noticeFrames <= 10)
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, noticeSubtitleMotion / 5.0f);
            if (noticeFrames > 65)
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    -noticeSubtitleMotion / 15.0f + 1.0f, -noticeSubtitleMotion / 15.0f + 1.0f, 1.0f);
            else
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    noticeSubtitleMotion / 100.0f + 1.0f, noticeSubtitleMotion / 100.0f + 1.0f, 1.0f);
            textureManager->DrawQuad(5, packet, &rect, 0xFFFFFFFF);
        }
        if (noticeFrames < 70 && noticePulseScale * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, noticePulseScale, noticePulseScale, 1.0f);
            textureManager->SetBlendMode(2);
            textureManager->DrawQuad(2, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(noticePulseScale * 60.0f), 255, 255, 255));
            textureManager->SetBlendMode(0);
        }
        break;
    case 1:
        SetRect(&rect, elapsedBattleFrames * 5, 0, elapsedBattleFrames * 5 + 640, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f - noticeHorizontalEdgeOffset, 640.0f, 272.0f - noticeHorizontalEdgeOffset);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - elapsedBattleFrames * 5, 0, 640 - elapsedBattleFrames * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f + noticeHorizontalEdgeOffset, 640.0f, 272.0f + noticeHorizontalEdgeOffset);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, elapsedBattleFrames * 5, 0, elapsedBattleFrames * 5 + 480, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f - noticeVerticalEdgeOffset, 560.0f, 272.0f - noticeVerticalEdgeOffset);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - elapsedBattleFrames * 5, 0, 480 - elapsedBattleFrames * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f + noticeVerticalEdgeOffset, 560.0f, 272.0f + noticeVerticalEdgeOffset);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        textureManager->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        if (noticeTitleMotion >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (noticeTitleMotion > 0.0f) {
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, noticeTitleMotion);
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    noticeTitleMotion / 20.0f + 1.2f, noticeTitleMotion / 20.0f + 1.2f, 1.0f);
            } else {
                if (noticeFrames > 70)
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        noticeTitleMotion / 200.0f + 1.2f, noticeTitleMotion / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        -noticeTitleMotion / 200.0f + 1.2f, noticeTitleMotion / 200.0f + 1.2f, 1.0f);
            }
            textureManager->DrawQuad(7, packet, &rect, 0xFFFFFFFF);
        }
        if (noticeFrames < 170 && noticePulseScale * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, noticePulseScale, noticePulseScale, 1.0f);
            textureManager->SetBlendMode(2);
            textureManager->DrawQuad(2, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(noticePulseScale * 60.0f), 255, 255, 255));
            textureManager->SetBlendMode(0);
        }
    }
}

#undef QUAD
