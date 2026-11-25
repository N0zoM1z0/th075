#include "replay/ReplayBrowserScene.hpp"
#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "audio/AudioControl.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#include <string.h>
#define PLAY(sound) g_SoundBank->Play(sound)
#define TRANSITION() { \
  strcpy(g_ReplayRecords.filePath, filenames[field048]); \
  AudioControl407CA0::ScheduleFade(-10000,-60,1,0); \
}
unsigned short ReplayBrowserScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if (field051 == 0) {
        if (field04E < 0) {
            PLAY(0x27);
            --field048;
            if (field048 < 0)
                field048 = 0;
        }
        if (field04E > 0) {
            PLAY(0x27);
            ++field048;
            if (field048 >= static_cast<int>(filenames.size()))
                field048 = filenames.size() - 1;
        }
        if (field04D < 0) {
            PLAY(0x27);
            field048 = field048 - 10;
            if (field048 < 0)
                field048 = 0;
        }
        if (field04D > 0) {
            PLAY(0x27);
            field048 = field048 + 10;
            if (field048 >= static_cast<int>(filenames.size()))
                field048 = filenames.size() - 1;
        }
    } else {
        if (field04E < 0) {
            PLAY(0x27);
            --field04A;
            if (field04A < 0)
                field04A = headers[field048].recordCount - 1;
        }
        if (field04E > 0) {
            PLAY(0x27);
            ++field04A;
            if (field04A >= static_cast<int>(headers[field048].recordCount))
                field04A = 0;
        }
    }
    if (field04C < 255)
        field04C = field04C + 25;
    if (field04F == 1 && filenames.size() > 0) {
        if (static_cast<signed char>(headers[field048].mode) > 0) {
            PLAY(0x2d);
            if (field051 == 0) {
                if (headers[field048].recordCount > 1) {
                    field051 = 1;
                    field04A = 0;
                } else {
                    g_RecordSequenceAt006714A4 = 1;
                    g_ReplayModeAt0066C238 = 2;
                    TRANSITION();
                    return 0x2201;
                }
            } else {
                g_RecordSequenceAt006714A4 = field04A + 1;
                g_ReplayModeAt0066C238 = 2;
                TRANSITION();
                return 0x2201;
            }
        } else {
            PLAY(0x2d);
            g_ReplayModeAt0066C238 = 2;
            TRANSITION();
            return 0x2201;
        }
    }
    if (field050 == 1) {
        if (field051 == 1) {
            PLAY(0x28);
            field051 = 0;
        } else {
            PLAY(0x28);
            return 0x2202;
        }
    }
    return 5;
}
#undef TRANSITION
#undef PLAY
