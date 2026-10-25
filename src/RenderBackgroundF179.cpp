#include "RenderBackgroundF179.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "CharacterSelectCards437380.hpp"
#include "CharacterSelectOptions438240.hpp"
#include "SinglePlayerOptions438670.hpp"

// Ignored-result call-only view, matching the established drawing contracts.
class BackgroundDrawingF179 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
};
// Reference-only observed byte views. No original names or ownership claimed.
extern signed char g_BackgroundPadFrameAt00671620;
extern unsigned char g_BackgroundPadNoticeAt00671621;

// Borrowed observed float windows; no complete scene layout is asserted.
struct BackgroundLayerMotionF179 {
    float leftBackdrop;
    float rightBackdrop;
    float leftPortrait;
    float rightPortrait;
    float leftName;
    float rightName;
    float leftTitle;
    float rightTitle;
    float leftDetail;
    float rightDetail;
};
struct BackgroundOverlayMotionF179 {
    float leftFade;
    float rightFade;
    float barOffset;
    float waveHeight;
    float wavePhase;
};
#define LAYERS (*reinterpret_cast<BackgroundLayerMotionF179*>(reinterpret_cast<unsigned char*>(this) + 0x98))
#define OVERLAY (*reinterpret_cast<BackgroundOverlayMotionF179*>(reinterpret_cast<unsigned char*>(this) + 0xCC))

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define DRAW(offset) FIELD(BackgroundDrawingF179*, offset)
#define QUAD reinterpret_cast<SpriteTransform*>(&spriteQuad)
#define INVERSE_ALPHA(offset, range, shade) D3DCOLOR_ARGB(255 - BYTE((offset) * 255.0f / (range)), shade, shade, shade)
#define FORWARD_ALPHA(offset, range, shade) D3DCOLOR_ARGB(BYTE((offset) * 255.0f / (range)), shade, shade, shade)

void RenderBackgroundF179::RenderBackground()
{
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 spriteQuad;
        BYTE tint[2];
        tint[0] = 255 - FIELD(signed char, 0xEA) * 128;
        tint[1] = 255 - FIELD(signed char, 0xEB) * 128;
        RECT clipRect;
        DRAW(8)->SetDepthMode(0);
        DRAW(8)->SetBlendMode(0);
        SetRect(&clipRect, 0, 0, 640, 480);
        QUAD->BuildQuadFromRect(&clipRect);
        DRAW(8)->DrawQuad(0, spriteQuad, &clipRect, 0xFFFFFFFF);

        SetRect(&clipRect, 0, 0, 512, 512);
        QUAD->BuildQuad(-96.0f - LAYERS.leftBackdrop, 0.0f,
                        416.0f - LAYERS.leftBackdrop, 512.0f);
        DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) << 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(OVERLAY.leftFade, 100.0f, tint[0]));
        if (FIELD(signed char, 0xE8) == 0 && FIELD(signed char, 0x96) == 0) {
            SetRect(&clipRect, 0, 0, 512, 512);
            QUAD->BuildQuad(-96.0f - (100.0f - LAYERS.leftBackdrop), 0.0f,
                            416.0f - (100.0f - LAYERS.leftBackdrop), 512.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE2) << 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(OVERLAY.leftFade, 100.0f, tint[0]));
        }
        if (g_CombatMode != 3) {
            SetRect(&clipRect, 0, 0, 512, 512);
            QUAD->BuildQuad(-96.0f - LAYERS.rightBackdrop, 0.0f,
                            416.0f - LAYERS.rightBackdrop, 512.0f);
            QUAD->RotateQuad(320.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE1) << 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(OVERLAY.rightFade, 100.0f, tint[1]));
            SetRect(&clipRect, 0, 192, 256, 448);
            QUAD->BuildQuad(20.0f + LAYERS.rightPortrait, 244.0f,
                            276.0f + LAYERS.rightPortrait, 500.0f);
            QUAD->ScaleQuad(160.0f, 372.0f, 0.0f,
                -LAYERS.rightPortrait / 80.0f + 1.0f,
                -LAYERS.rightPortrait / 80.0f + 1.0f,
                -LAYERS.rightPortrait / 80.0f + 1.0f);
            QUAD->RotateQuad(160.0f, 372.0f, 0.0f, 0.0f, 0.0f, -LAYERS.rightPortrait * 2.0f);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE1) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(LAYERS.rightPortrait, 80.0f, tint[1]));
            SetRect(&clipRect, 0, 128, 256, 192);
            QUAD->BuildQuad(20.0f, 303.0f - LAYERS.rightName,
                            276.0f, 367.0f - LAYERS.rightName);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE1) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(LAYERS.rightName, 40.0f, tint[1]));
            SetRect(&clipRect, 0, 0, 256, 64);
            QUAD->BuildQuad(20.0f - LAYERS.rightTitle, 333.0f,
                            276.0f - LAYERS.rightTitle, 397.0f);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE1) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(LAYERS.rightTitle, 80.0f, tint[1]));
            SetRect(&clipRect, 0, 64, 256, 128);
            QUAD->BuildQuad(20.0f, 358.0f + LAYERS.rightDetail,
                            276.0f, 422.0f + LAYERS.rightDetail);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE1) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(LAYERS.rightDetail, 40.0f, tint[1]));
            if (FIELD(signed char, 0xE9) == 0 && FIELD(signed char, 0x97) == 0) {
                SetRect(&clipRect, 0, 0, 512, 512);
                QUAD->BuildQuad(-96.0f - (100.0f - LAYERS.rightBackdrop), 0.0f,
                                416.0f - (100.0f - LAYERS.rightBackdrop), 512.0f);
                QUAD->RotateQuad(320.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
                DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE3) << 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(OVERLAY.rightFade, 100.0f, tint[1]));
                SetRect(&clipRect, 0, 128, 256, 192);
                QUAD->BuildQuad(20.0f, 303.0f - (40.0f - LAYERS.rightName),
                                276.0f, 367.0f - (40.0f - LAYERS.rightTitle));
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE3) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(LAYERS.rightName, 40.0f, tint[1]));
                SetRect(&clipRect, 0, 0, 256, 64);
                QUAD->BuildQuad((80.0f - LAYERS.rightTitle) + 20.0f, 333.0f,
                                (80.0f - LAYERS.rightTitle) + 276.0f, 397.0f);
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE3) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(LAYERS.rightTitle, 80.0f, tint[1]));
                SetRect(&clipRect, 0, 64, 256, 128);
                QUAD->BuildQuad(20.0f, (40.0f - LAYERS.rightDetail) + 358.0f,
                                276.0f, (40.0f - LAYERS.rightDetail) + 422.0f);
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE3) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(LAYERS.rightDetail, 40.0f, tint[1]));
            }
        }
        SetRect(&clipRect, 0, 192, 256, 448);
        QUAD->BuildQuad(20.0f, 244.0f, 276.0f, 500.0f);
        QUAD->ScaleQuad(160.0f, 372.0f, 0.0f,
            -LAYERS.leftPortrait / 80.0f + 1.0f,
            -LAYERS.leftPortrait / 80.0f + 1.0f,
            -LAYERS.leftPortrait / 80.0f + 1.0f);
        QUAD->RotateQuad(160.0f, 372.0f, 0.0f, 0.0f, 0.0f, -LAYERS.leftPortrait * 2.0f);
        DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(LAYERS.leftPortrait, 80.0f, tint[0]));
        SetRect(&clipRect, 0, 128, 256, 192);
        QUAD->BuildQuad(20.0f, 303.0f - LAYERS.leftName,
                        276.0f, 367.0f - LAYERS.leftName);
        DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(LAYERS.leftName, 40.0f, tint[0]));
        SetRect(&clipRect, 0, 0, 256, 64);
        QUAD->BuildQuad(20.0f + LAYERS.leftTitle, 333.0f,
                        276.0f + LAYERS.leftTitle, 397.0f);
        DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(LAYERS.leftTitle, 80.0f, tint[0]));
        SetRect(&clipRect, 0, 64, 256, 128);
        QUAD->BuildQuad(20.0f, 358.0f + LAYERS.leftDetail,
                        276.0f, 422.0f + LAYERS.leftDetail);
        DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(LAYERS.leftDetail, 40.0f, tint[0]));
        if (FIELD(signed char, 0xE8) == 0 && FIELD(signed char, 0x96) == 0) {
            SetRect(&clipRect, 0, 128, 256, 192);
            QUAD->BuildQuad(20.0f, 303.0f - (40.0f - LAYERS.leftName),
                            276.0f, 367.0f - (40.0f - LAYERS.leftTitle));
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE2) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(LAYERS.leftName, 40.0f, tint[0]));
            SetRect(&clipRect, 0, 0, 256, 64);
            QUAD->BuildQuad(20.0f - (80.0f - LAYERS.leftTitle), 333.0f,
                            276.0f - (80.0f - LAYERS.leftTitle), 397.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE2) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(LAYERS.leftTitle, 80.0f, tint[0]));
            SetRect(&clipRect, 0, 64, 256, 128);
            QUAD->BuildQuad(20.0f, (40.0f - LAYERS.leftDetail) + 358.0f,
                            276.0f, (40.0f - LAYERS.leftDetail) + 422.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE2) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(LAYERS.leftDetail, 40.0f, tint[0]));
        }
        reinterpret_cast<CharacterSelectCards437380*>(this)->RenderCards();
        signed char index;
        if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
            index = 16;
        else
            index = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10 * (FIELD(signed char, 0xF1) < 6);
        SetRect(&clipRect, 0, 0, 256, 480);
        QUAD->BuildQuadFromRect(&clipRect);
        QUAD->TranslateQuad(192.0f, 0.0f, 0.0f);
        DRAW(0x48)->DrawQuad(index, spriteQuad, &clipRect, D3DCOLOR_ARGB(FIELD(BYTE, 0xC8), 255, 255, 255));
        SetRect(&clipRect, 0, index * 57, 512, index * 57 + 57);
        QUAD->BuildQuad(64.0f, 300.0f, 576.0f, 357.0f);
        DRAW(8)->DrawQuad(2, spriteQuad, &clipRect, D3DCOLOR_ARGB(FIELD(BYTE, 0xC8), 255, 255, 255));
        SetRect(&clipRect, 0, 0, 512, 64);
        QUAD->BuildQuad(64.0f, CameraSineAt0040D940(OVERLAY.wavePhase) * OVERLAY.waveHeight + 10.0f,
                        576.0f, CameraSineAt0040D940(OVERLAY.wavePhase) * OVERLAY.waveHeight + 74.0f);
        DRAW(8)->DrawQuad(3, spriteQuad, &clipRect, D3DCOLOR_ARGB(FIELD(BYTE, 0xC8), 255, 255, 255));
        DRAW(8)->DrawQuad(1, spriteQuad, &clipRect, D3DCOLOR_ARGB(255 - FIELD(BYTE, 0xC8), 255, 255, 255));
        SetRect(&clipRect, int(OVERLAY.barOffset), 0, int(640.0f + OVERLAY.barOffset), 16);
        QUAD->BuildQuad(0.0f, 448.0f, 640.0f, 464.0f);
        if (g_CombatMode == 3)
            DRAW(8)->DrawQuad(7, spriteQuad, &clipRect, 0xFFFFFFFF);
        else
            DRAW(8)->DrawQuad(4, spriteQuad, &clipRect, 0xFFFFFFFF);
        if ((g_CombatMode == 3 && FIELD(signed char, 0xEA) == 0) || g_CombatMode == 4) {
            SetRect(&clipRect, 256, 832, 512, 1024);
            QUAD->BuildQuad(0.0f, 0.0f, 256.0f, 192.0f);
            QUAD->TranslateQuad(352.0f, 128.0f, 0.0f);
            DRAW(0x44)->DrawQuad(FIELD(signed char, 0xE0) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(OVERLAY.leftFade, 100.0f, 255));
        }
        if (g_BackgroundPadNoticeAt00671621 != 0) {
            SetRect(&clipRect, 144, g_BackgroundPadFrameAt00671620 * 32 - 32,
                    224, g_BackgroundPadFrameAt00671620 * 32);
            QUAD->BuildQuad(0.0f, 0.0f, 80.0f, 32.0f);
            QUAD->TranslateQuad(530.0f, 400.0f, 0.0f);
            DRAW(8)->DrawQuad(6, spriteQuad, &clipRect, 0xFFFFFFFF);
        }
        if (g_CombatMode == 3)
            reinterpret_cast<SinglePlayerOptions438670*>(this)->RenderOptions();
        else
            reinterpret_cast<CharacterSelectOptions438240*>(this)->RenderOptions();
        Graphics::EndFrame();
    }
}

#undef FORWARD_ALPHA
#undef INVERSE_ALPHA
#undef QUAD
#undef DRAW
#undef FIELD

#undef OVERLAY
#undef LAYERS
