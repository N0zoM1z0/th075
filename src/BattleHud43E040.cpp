#include "SpriteTransform.hpp"
#include "TextureManagerF198.hpp"
#include "BattleScene.hpp"
#include "BattleHud43E040.hpp"

#define LEFT_DRAWING reinterpret_cast<TextureManagerF198*>(fighters[0]->drawing)
#define RIGHT_DRAWING reinterpret_cast<TextureManagerF198*>(fighters[1]->drawing)
#define DRAWING reinterpret_cast<TextureManagerF198*>(textures)
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)

void BattleScene::RenderHud() {
    float nameSlide;
    int iconIndex;
    short tex;
    RenderQuadPacket5E68C0 packet;
    {
        // Quad submission pass; counter widgets are rendered after this scope.
        D3DCOLOR color;
        int gaugeIndex;
        RECT region;
        int gaugeHeight;
        int leftStateRow;
        int rightBand;

        reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
        color = D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 255, 255, 255);
        SetRect(&region, 0, 0, 128, 128);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuadFromRect(&region);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, field08C, 0.0f);
        tex = reinterpret_cast<HudDirectory43E040*>(&fighters[0]->sequenceSlots)->At(41)->At(0)[3];
        LEFT_DRAWING->DrawQuad(tex, packet, &region, color);
        tex = reinterpret_cast<HudDirectory43E040*>(&fighters[1]->sequenceSlots)->At(41)->At(0)[3];
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        RIGHT_DRAWING->DrawQuad(tex, packet, &region, color);

        SetRect(&region, 0, 0, 640, 123);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 640.0f, 123.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, field08C, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);

        if (fighters[0]->field39D == 2) {
            SetRect(&region, 641, 10, 866, 21);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(31.0f, 27.0f, 256.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 128, 128, 128));
            SetRect(&region, 866 - fighters[0]->recoverableHealth * 225 / 10000, 21, 866, 32);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(256 - fighters[0]->recoverableHealth * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            SetRect(&region, 865 - fighters[0]->health * 225 / 10000, 236, 865, 247);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(256 - fighters[0]->health * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        } else {
            SetRect(&region, 866 - fighters[0]->recoverableHealth * 225 / 10000, 21, 866, 32);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(256 - fighters[0]->recoverableHealth * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            SetRect(&region, 866 - fighters[0]->health * 225 / 10000, 10, 866, 21);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(256 - fighters[0]->health * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239,
                field098, field098, field098));
        }

        if (g_CombatMode == 3) {
            switch (fighters[1]->field32A[fighters[1]->field39D]) {
            case 0:
                if (field018 == 9 || field018 == 10) {
                    SetRect(&region, 866 - fighters[1]->recoverableHealth * 225 / fighters[1]->healthLimits[fighters[1]->field39D], 10, 866, 21);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->recoverableHealth * 56 / fighters[1]->healthLimits[fighters[1]->field39D] + 384), 27.0f, 384.0f, 38.0f);
                } else {
                    SetRect(&region, 641, 10, 866, 21);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(440.0f, 27.0f, 384.0f, 38.0f);
                }
                if (field08C != 0.0f)
                    QUAD->Translate(0.0f, field08C, 0.0f);
                DRAWING->DrawQuad(0, packet, &region, color);
                SetRect(&region, 865 - fighters[1]->health * 225 / fighters[1]->healthLimits[fighters[1]->field39D], 236, 865, 247);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->health * 169 / fighters[1]->healthLimits[fighters[1]->field39D] + 440), 27.0f, 440.0f, 38.0f);
                if (field08C != 0.0f)
                    QUAD->Translate(0.0f, field08C, 0.0f);
                DRAWING->DrawQuad(0, packet, &region, color);
                break;
            case 1:
                SetRect(&region, 866 - fighters[1]->health * 225 / fighters[1]->healthLimits[fighters[1]->field39D], 10, 866, 21);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->health * 56 / fighters[1]->healthLimits[fighters[1]->field39D] + 384), 27.0f, 384.0f, 38.0f);
                if (field08C != 0.0f)
                    QUAD->Translate(0.0f, field08C, 0.0f);
                DRAWING->DrawQuad(0, packet, &region, color);
                break;
            case 2:
                SetRect(&region, 866 - fighters[1]->health * 225 / fighters[1]->healthLimits[fighters[1]->field39D], 10, 866, 21);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->health * 225 / fighters[1]->healthLimits[fighters[1]->field39D] + 384), 27.0f, 384.0f, 38.0f);
                if (field08C != 0.0f)
                    QUAD->Translate(0.0f, field08C, 0.0f);
                DRAWING->DrawQuad(0, packet, &region, color);
                break;
            }
        } else if (fighters[1]->field39D == 2) {
            SetRect(&region, 641, 10, 866, 21);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(609.0f, 27.0f, 384.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 128, 128, 128));
            SetRect(&region, 866 - fighters[1]->recoverableHealth * 225 / 10000, 21, 866, 32);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->recoverableHealth * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            SetRect(&region, 865 - fighters[1]->health * 225 / 10000, 236, 865, 247);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->health * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        } else {
            SetRect(&region, 866 - fighters[1]->recoverableHealth * 225 / 10000, 21, 866, 32);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->recoverableHealth * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            SetRect(&region, 866 - fighters[1]->health * 225 / 10000, 10, 866, 21);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->health * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239,
                field099, field099, field099));
        }

        tex = reinterpret_cast<HudDirectory43E040*>(&fighters[0]->sequenceSlots)->At(40)->At(0)[3];
        nameSlide = float(reinterpret_cast<HudDirectory43E040*>(&fighters[0]->sequenceSlots)->At(40)->At(0)[0]);
        SetRect(&region, 0, 0, 128, 16);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f - nameSlide, 72.0f, 128.0f - nameSlide, 88.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, field08C, 0.0f);
        LEFT_DRAWING->DrawQuad(tex, packet, &region, color);
        tex = reinterpret_cast<HudDirectory43E040*>(&fighters[1]->sequenceSlots)->At(40)->At(0)[3];
        nameSlide = float(reinterpret_cast<HudDirectory43E040*>(&fighters[1]->sequenceSlots)->At(40)->At(1)[0]);
        SetRect(&region, 0, 0, 128, 16);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f - nameSlide, 72.0f, 128.0f - nameSlide, 88.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, field08C, 0.0f);
        RIGHT_DRAWING->DrawQuad(tex, packet, &region, color);

        if (g_CombatMode == 3) {
            SetRect(&region, 756, 39, 797, 53);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(115.0f, 5.0f, 156.0f, 19.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            DrawAtlasNumberAt00446B90(280.0f, 5.0f + field08C, color, fighters[0]->score, 12, 10);
            SetRect(&region, 803, 39, 858, 53);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(376.0f, 5.0f, 431.0f, 19.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            DrawAtlasNumberAt00446B90(555.0f, 5.0f + field08C, color, int(g_MaxCombatScore), 12, 10);
            SetRect(&region, 866, 41, 923, 54);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(1.0f, 5.0f, 58.0f, 18.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            DrawAtlasNumberDefaultAt00446B60(70.0f, 5.0f + field08C, color, int(static_cast<signed char>(g_SequenceCounterAt00671622)), 11);
        } else {
            SetRect(&region, 756, 39, 797, 53);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(115.0f, 5.0f, 156.0f, 19.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            DrawAtlasNumberAt00446B90(280.0f, 5.0f + field08C, color, fighters[0]->score, 12, 10);
            SetRect(&region, 756, 39, 797, 53);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(370.0f, 5.0f, 411.0f, 19.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            DrawAtlasNumberAt00446B90(535.0f, 5.0f + field08C, color, fighters[1]->score, 12, 10);
        }

        color = D3DCOLOR_ARGB(g_SequenceByteAt0066C23A, 255, 255, 255);
        if (fighters[0]->field36C < 900.0f) {
            gaugeIndex = int(fighters[0]->field36C / 100.0f);
            gaugeHeight = ((int(fighters[0]->field36C * 10.0f) % 1000 + 1) * 58) / 1000;
        } else {
            gaugeIndex = 8;
            gaugeHeight = 58;
        }
        SetRect(&region, (gaugeIndex % 3) * 64, gaugeIndex / 3 * 58 + 136 - gaugeHeight,
            gaugeIndex % 3 * 64 + 64, gaugeIndex / 3 * 58 + 136);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, float(58 - gaugeHeight), 64.0f, 58.0f);
        QUAD->Translate(1.0f, 416.0f - field08C, 0.0f);
        DRAWING->DrawQuad(8, packet, &region, color);
        if (fighters[1]->field36C < 900.0f) {
            gaugeIndex = int(fighters[1]->field36C / 100.0f);
            gaugeHeight = ((int(fighters[1]->field36C * 10.0f) % 1000 + 1) * 58) / 1000;
        } else {
            gaugeIndex = 8;
            gaugeHeight = 58;
        }
        SetRect(&region, gaugeIndex % 3 * 64, gaugeIndex / 3 * 58 + 136 - gaugeHeight,
            gaugeIndex % 3 * 64 + 64, gaugeIndex / 3 * 58 + 136);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, float(58 - gaugeHeight), 64.0f, 58.0f);
        QUAD->Translate(1.0f, 416.0f - field08C, 0.0f);
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        DRAWING->DrawQuad(8, packet, &region, color);

        SetRect(&region, 0, 188, 301, 256);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 412.0f, 301.0f, 480.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, -field08C, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        DRAWING->DrawQuad(0, packet, &region, color);

        if (fighters[0]->spiritCooldown > 0) {
            SetRect(&region, 640, 227, 844, 236);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[0]->spiritCooldown * 204 / 1000 + 75), 462.0f, 279.0f, 471.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        } else {
            leftStateRow = 0;
            if (fighters[0]->spirit <= 250.0)
                leftStateRow = (fighters[0]->fieldEF8 % 20 < 10) * 9 + 18;
            else if (fighters[0]->spirit <= 500.0)
                leftStateRow = 18;
            else if (fighters[0]->spirit <= 750.0)
                leftStateRow = 9;
            SetRect(&region, 640, leftStateRow + 200, 844, leftStateRow + 209);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(273 - fighters[0]->spirit * 198 / 1000), 462.0f, 279.0f, 471.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        }
        if (fighters[1]->spiritCooldown > 0) {
            SetRect(&region, 640, 227, 844, 236);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(565 - fighters[1]->spiritCooldown * 204 / 1000), 462.0f, 361.0f, 471.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        } else {
            rightBand = 0;
            if (fighters[1]->spirit <= 250.0)
                rightBand = (fighters[1]->fieldEF8 % 20 < 10) * 9 + 18;
            else if (fighters[1]->spirit <= 500.0)
                rightBand = 18;
            else if (fighters[1]->spirit <= 750.0)
                rightBand = 9;
            SetRect(&region, 640, rightBand + 200, 844, rightBand + 209);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(fighters[1]->spirit * 204 / 1000 + 361), 462.0f, 361.0f, 471.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        }

        SetRect(&region, 866, 0, 914, 19);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(65.0f, 437.0f, 113.0f, 456.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, -field08C, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);
        if (g_CombatMode != 3) {
            QUAD->Translate(431.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        }
        SetRect(&region, 948, 3, 964, 18);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(115.0f, 440.0f, 131.0f, 455.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, -field08C, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);
        QUAD->Translate(16.0f, 0.0f, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);
        if (g_CombatMode != 3) {
            QUAD->Translate(431.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
            QUAD->Translate(-16.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        }
        SetRect(&region, 916, 3, 932, 18);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(115.0f, 440.0f, 131.0f, 455.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, -field08C, 0.0f);
        for (iconIndex = 0; iconIndex < fighters[0]->field366; iconIndex = iconIndex + 1) {
            DRAWING->DrawQuad(0, packet, &region, color);
            QUAD->Translate(16.0f, 0.0f, 0.0f);
        }
        if (g_CombatMode != 3) {
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(546.0f, 440.0f, 562.0f, 455.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            for (iconIndex = 0; iconIndex < fighters[1]->field366; iconIndex = iconIndex + 1) {
                DRAWING->DrawQuad(0, packet, &region, color);
                QUAD->Translate(16.0f, 0.0f, 0.0f);
            }
        }
        SetRect(&region, (2 - fighters[0]->field39D) * 64 + 832, 64,
            (2 - fighters[0]->field39D) * 64 + 896, 96);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(223.0f, 433.0f, 287.0f, 465.0f);
        if (field08C != 0.0f)
            QUAD->Translate(0.0f, -field08C, 0.0f);
        DRAWING->DrawQuad(0, packet, &region, color);
        if (g_CombatMode != 3) {
            SetRect(&region, (2 - fighters[1]->field39D) * 64 + 832, 64,
                (2 - fighters[1]->field39D) * 64 + 896, 96);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(380.0f, 433.0f, 444.0f, 465.0f);
            if (field08C != 0.0f)
                QUAD->Translate(0.0f, -field08C, 0.0f);
            DRAWING->DrawQuad(0, packet, &region, color);
        }
        DrawAtlasNumberDefaultAt00446B60(33.0f, 439.0f - field08C, color, static_cast<int>(static_cast<short>(fighters[0]->field36C / 100.0f)), 10);
        if (g_CombatMode == 3) {
            // This mode omits the right numeric gauge.
        } else {
            DrawAtlasNumberDefaultAt00446B60(637.0f, 439.0f - field08C, color, static_cast<int>(static_cast<short>(fighters[1]->field36C / 100.0f)), 10);
        }
    }
    comboDisplays[0]->Render();
    comboDisplays[1]->Render();
}

#undef QUAD
#undef STYLE
#undef DRAWING
#undef RIGHT_DRAWING
#undef LEFT_DRAWING
