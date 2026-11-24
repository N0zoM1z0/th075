#include "BattleResultState.hpp"
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "Graphics.hpp"
#include "TextureManagerF198.hpp"
#include "CharacterSelectScene.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Ignored-result call-only view, matching the established drawing contracts.
class BackgroundDrawingF179 {
public:
};
// Reference-only observed byte views. No original names or ownership claimed.

// All used animation and overlay fields share the scene layout.
#define QUAD reinterpret_cast<SpriteTransform*>(&spriteQuad)
#define INVERSE_ALPHA(offset, range, shade) D3DCOLOR_ARGB(255 - BYTE((offset) * 255.0f / (range)), shade, shade, shade)
#define FORWARD_ALPHA(offset, range, shade) D3DCOLOR_ARGB(BYTE((offset) * 255.0f / (range)), shade, shade, shade)

void CharacterSelectScene::Render()
{
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 spriteQuad;
        BYTE tint[2];
        tint[0] = 255 - (optionsOpen[0]) * 128;
        tint[1] = 255 - (optionsOpen[1]) * 128;
        RECT clipRect;
        menuTextures->SetDepthMode(0);
        menuTextures->SetBlendMode(0);
        SetRect(&clipRect, 0, 0, 640, 480);
        QUAD->BuildQuadFromRect(&clipRect);
        menuTextures->DrawQuad(0, spriteQuad, &clipRect, 0xFFFFFFFF);

        SetRect(&clipRect, 0, 0, 512, 512);
        QUAD->BuildQuad(-96.0f - portraitFade[0], 0.0f,
                        416.0f - portraitFade[0], 512.0f);
        characterTextures->DrawQuad((chosenCharacter[0]) << 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(portraitReturn[0], 100.0f, tint[0]));
        if ((static_cast<signed char>(playerReady[0])) == 0 && (playerState[0]) == 0) {
            SetRect(&clipRect, 0, 0, 512, 512);
            QUAD->BuildQuad(-96.0f - (100.0f - portraitFade[0]), 0.0f,
                            416.0f - (100.0f - portraitFade[0]), 512.0f);
            characterTextures->DrawQuad((alternateCharacter[0]) << 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(portraitReturn[0], 100.0f, tint[0]));
        }
        if (g_CombatMode != 3) {
            SetRect(&clipRect, 0, 0, 512, 512);
            QUAD->BuildQuad(-96.0f - portraitFade[1], 0.0f,
                            416.0f - portraitFade[1], 512.0f);
            QUAD->RotateQuad(320.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[1]) << 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitReturn[1], 100.0f, tint[1]));
            SetRect(&clipRect, 0, 192, 256, 448);
            QUAD->BuildQuad(20.0f + portraitEnterX[1], 244.0f,
                            276.0f + portraitEnterX[1], 500.0f);
            QUAD->ScaleQuad(160.0f, 372.0f, 0.0f,
                -portraitEnterX[1] / 80.0f + 1.0f,
                -portraitEnterX[1] / 80.0f + 1.0f,
                -portraitEnterX[1] / 80.0f + 1.0f);
            QUAD->RotateQuad(160.0f, 372.0f, 0.0f, 0.0f, 0.0f, -portraitEnterX[1] * 2.0f);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitEnterX[1], 80.0f, tint[1]));
            SetRect(&clipRect, 0, 128, 256, 192);
            QUAD->BuildQuad(20.0f, 303.0f - portraitEnterY[1],
                            276.0f, 367.0f - portraitEnterY[1]);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitEnterY[1], 40.0f, tint[1]));
            SetRect(&clipRect, 0, 0, 256, 64);
            QUAD->BuildQuad(20.0f - portraitExitX[1], 333.0f,
                            276.0f - portraitExitX[1], 397.0f);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitExitX[1], 80.0f, tint[1]));
            SetRect(&clipRect, 0, 64, 256, 128);
            QUAD->BuildQuad(20.0f, 358.0f + portraitExitY[1],
                            276.0f, 422.0f + portraitExitY[1]);
            QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitExitY[1], 40.0f, tint[1]));
            if ((static_cast<signed char>(playerReady[1])) == 0 && (playerState[1]) == 0) {
                SetRect(&clipRect, 0, 0, 512, 512);
                QUAD->BuildQuad(-96.0f - (100.0f - portraitFade[1]), 0.0f,
                                416.0f - (100.0f - portraitFade[1]), 512.0f);
                QUAD->RotateQuad(320.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
                characterTextures->DrawQuad((alternateCharacter[1]) << 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(portraitReturn[1], 100.0f, tint[1]));
                SetRect(&clipRect, 0, 128, 256, 192);
                QUAD->BuildQuad(20.0f, 303.0f - (40.0f - portraitEnterY[1]),
                                276.0f, 367.0f - (40.0f - portraitExitX[1]));
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                characterTextures->DrawQuad((alternateCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(portraitEnterY[1], 40.0f, tint[1]));
                SetRect(&clipRect, 0, 0, 256, 64);
                QUAD->BuildQuad((80.0f - portraitExitX[1]) + 20.0f, 333.0f,
                                (80.0f - portraitExitX[1]) + 276.0f, 397.0f);
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                characterTextures->DrawQuad((alternateCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(portraitExitX[1], 80.0f, tint[1]));
                SetRect(&clipRect, 0, 64, 256, 128);
                QUAD->BuildQuad(20.0f, (40.0f - portraitExitY[1]) + 358.0f,
                                276.0f, (40.0f - portraitExitY[1]) + 422.0f);
                QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                characterTextures->DrawQuad((alternateCharacter[1]) * 2 + 1, spriteQuad, &clipRect,
                                     FORWARD_ALPHA(portraitExitY[1], 40.0f, tint[1]));
            }
        }
        SetRect(&clipRect, 0, 192, 256, 448);
        QUAD->BuildQuad(20.0f, 244.0f, 276.0f, 500.0f);
        QUAD->ScaleQuad(160.0f, 372.0f, 0.0f,
            -portraitEnterX[0] / 80.0f + 1.0f,
            -portraitEnterX[0] / 80.0f + 1.0f,
            -portraitEnterX[0] / 80.0f + 1.0f);
        QUAD->RotateQuad(160.0f, 372.0f, 0.0f, 0.0f, 0.0f, -portraitEnterX[0] * 2.0f);
        characterTextures->DrawQuad((chosenCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(portraitEnterX[0], 80.0f, tint[0]));
        SetRect(&clipRect, 0, 128, 256, 192);
        QUAD->BuildQuad(20.0f, 303.0f - portraitEnterY[0],
                        276.0f, 367.0f - portraitEnterY[0]);
        characterTextures->DrawQuad((chosenCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(portraitEnterY[0], 40.0f, tint[0]));
        SetRect(&clipRect, 0, 0, 256, 64);
        QUAD->BuildQuad(20.0f + portraitExitX[0], 333.0f,
                        276.0f + portraitExitX[0], 397.0f);
        characterTextures->DrawQuad((chosenCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(portraitExitX[0], 80.0f, tint[0]));
        SetRect(&clipRect, 0, 64, 256, 128);
        QUAD->BuildQuad(20.0f, 358.0f + portraitExitY[0],
                        276.0f, 422.0f + portraitExitY[0]);
        characterTextures->DrawQuad((chosenCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                             INVERSE_ALPHA(portraitExitY[0], 40.0f, tint[0]));
        if ((static_cast<signed char>(playerReady[0])) == 0 && (playerState[0]) == 0) {
            SetRect(&clipRect, 0, 128, 256, 192);
            QUAD->BuildQuad(20.0f, 303.0f - (40.0f - portraitEnterY[0]),
                            276.0f, 367.0f - (40.0f - portraitExitX[0]));
            characterTextures->DrawQuad((alternateCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(portraitEnterY[0], 40.0f, tint[0]));
            SetRect(&clipRect, 0, 0, 256, 64);
            QUAD->BuildQuad(20.0f - (80.0f - portraitExitX[0]), 333.0f,
                            276.0f - (80.0f - portraitExitX[0]), 397.0f);
            characterTextures->DrawQuad((alternateCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(portraitExitX[0], 80.0f, tint[0]));
            SetRect(&clipRect, 0, 64, 256, 128);
            QUAD->BuildQuad(20.0f, (40.0f - portraitExitY[0]) + 358.0f,
                            276.0f, (40.0f - portraitExitY[0]) + 422.0f);
            characterTextures->DrawQuad((alternateCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                                 FORWARD_ALPHA(portraitExitY[0], 40.0f, tint[0]));
        }
        RenderCards();
        signed char index;
        if ((stagePage[1]) == 8 && (stagePage[0]) == 1)
            index = 16;
        else
            index = (stagePage[1]) + (stagePage[0]) * 10 * ((stagePage[1]) < 6);
        SetRect(&clipRect, 0, 0, 256, 480);
        QUAD->BuildQuadFromRect(&clipRect);
        QUAD->TranslateQuad(192.0f, 0.0f, 0.0f);
        backgroundTextures->DrawQuad(index, spriteQuad, &clipRect, D3DCOLOR_ARGB((transitionAlpha), 255, 255, 255));
        SetRect(&clipRect, 0, index * 57, 512, index * 57 + 57);
        QUAD->BuildQuad(64.0f, 300.0f, 576.0f, 357.0f);
        menuTextures->DrawQuad(2, spriteQuad, &clipRect, D3DCOLOR_ARGB((transitionAlpha), 255, 255, 255));
        SetRect(&clipRect, 0, 0, 512, 64);
        QUAD->BuildQuad(64.0f, CameraSineAt0040D940(choiceRotation) * choiceOscillation + 10.0f,
                        576.0f, CameraSineAt0040D940(choiceRotation) * choiceOscillation + 74.0f);
        menuTextures->DrawQuad(3, spriteQuad, &clipRect, D3DCOLOR_ARGB((transitionAlpha), 255, 255, 255));
        menuTextures->DrawQuad(1, spriteQuad, &clipRect, D3DCOLOR_ARGB(255 - (transitionAlpha), 255, 255, 255));
        SetRect(&clipRect, int(animationPhase), 0, int(640.0f + animationPhase), 16);
        QUAD->BuildQuad(0.0f, 448.0f, 640.0f, 464.0f);
        if (g_CombatMode == 3)
            menuTextures->DrawQuad(7, spriteQuad, &clipRect, 0xFFFFFFFF);
        else
            menuTextures->DrawQuad(4, spriteQuad, &clipRect, 0xFFFFFFFF);
        if ((g_CombatMode == 3 && (optionsOpen[0]) == 0) || g_CombatMode == 4) {
            SetRect(&clipRect, 256, 832, 512, 1024);
            QUAD->BuildQuad(0.0f, 0.0f, 256.0f, 192.0f);
            QUAD->TranslateQuad(352.0f, 128.0f, 0.0f);
            characterTextures->DrawQuad((chosenCharacter[0]) * 2 + 1, spriteQuad, &clipRect,
                                 INVERSE_ALPHA(portraitReturn[0], 100.0f, 255));
        }
        if (g_StoryResultAt00671621 != 0) {
            SetRect(&clipRect, 144, g_StoryChoiceAt00671620 * 32 - 32,
                    224, g_StoryChoiceAt00671620 * 32);
            QUAD->BuildQuad(0.0f, 0.0f, 80.0f, 32.0f);
            QUAD->TranslateQuad(530.0f, 400.0f, 0.0f);
            menuTextures->DrawQuad(6, spriteQuad, &clipRect, 0xFFFFFFFF);
        }
        if (g_CombatMode == 3)
            RenderSinglePlayerOptions();
        else
            RenderOptions();
        Graphics::EndFrame();
    }
}

#undef FORWARD_ALPHA
#undef INVERSE_ALPHA
#undef QUAD
