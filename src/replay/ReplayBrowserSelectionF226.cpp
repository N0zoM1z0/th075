#include "engine/SceneTransition.hpp"
#include "replay/ReplayMode.hpp"
#include "replay/ReplayBrowserScene.hpp"
#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "audio/AudioControl.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#include <string.h>
#define PLAY(sound) g_SoundBank->Play(sound)
#define TRANSITION() { \
  strcpy(g_ReplayRecords.filePath, filenames[selectedFile]); \
  AudioControl407CA0::ScheduleFade(-10000,-60,1,0); \
}
unsigned short ReplayBrowserScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if (choosingRecord == 0) {
        if (verticalInput < 0) {
            PLAY(0x27);
            --selectedFile;
            if (selectedFile < 0)
                selectedFile = 0;
        }
        if (verticalInput > 0) {
            PLAY(0x27);
            ++selectedFile;
            if (selectedFile >= static_cast<int>(filenames.size()))
                selectedFile = filenames.size() - 1;
        }
        if (pageInput < 0) {
            PLAY(0x27);
            selectedFile = selectedFile - 10;
            if (selectedFile < 0)
                selectedFile = 0;
        }
        if (pageInput > 0) {
            PLAY(0x27);
            selectedFile = selectedFile + 10;
            if (selectedFile >= static_cast<int>(filenames.size()))
                selectedFile = filenames.size() - 1;
        }
    } else {
        if (verticalInput < 0) {
            PLAY(0x27);
            --selectedRecord;
            if (selectedRecord < 0)
                selectedRecord = headers[selectedFile].recordCount - 1;
        }
        if (verticalInput > 0) {
            PLAY(0x27);
            ++selectedRecord;
            if (selectedRecord >= static_cast<int>(headers[selectedFile].recordCount))
                selectedRecord = 0;
        }
    }
    if (displayAlpha < 255)
        displayAlpha = displayAlpha + 25;
    if (confirmInput == 1 && filenames.size() > 0) {
        if (static_cast<signed char>(headers[selectedFile].mode) > 0) {
            PLAY(0x2d);
            if (choosingRecord == 0) {
                if (headers[selectedFile].recordCount > 1) {
                    choosingRecord = 1;
                    selectedRecord = 0;
                } else {
                    g_RecordSequenceAt006714A4 = 1;
                    g_ReplayModeAt0066C238 = ReplayMode::Playback;
                    TRANSITION();
                    return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
                }
            } else {
                g_RecordSequenceAt006714A4 = selectedRecord + 1;
                g_ReplayModeAt0066C238 = ReplayMode::Playback;
                TRANSITION();
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
            }
        } else {
            PLAY(0x2d);
            g_ReplayModeAt0066C238 = ReplayMode::Playback;
            TRANSITION();
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
        }
    }
    if (cancelInput == 1) {
        if (choosingRecord == 1) {
            PLAY(0x28);
            choosingRecord = 0;
        } else {
            PLAY(0x28);
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
        }
    }
    return 5;
}
#undef TRANSITION
#undef PLAY
