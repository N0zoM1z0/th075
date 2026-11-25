#ifndef TH075_CHARACTER_SELECT_SCENE_HPP
#define TH075_CHARACTER_SELECT_SCENE_HPP

#include "engine/SceneBase.hpp"
class TextureManagerF198;

// One 28-byte snapshot for each player's directional and button repeat counters.
// The stride and all seven DWORD slots are observed in the select input code.
struct SelectInputFrame {
    int horizontal;
    int vertical;
    int confirm;
    int cancel;
    int special;
    int toggle;
    int alternative;
};

// Character select scene, vtable 0065824C. WinMain allocates 0xF4 bytes.
// The observed fields run through offset +F3.
class CharacterSelectScene : public SceneBase {
public:
    CharacterSelectScene();                // 00432EA0
    virtual ~CharacterSelectScene();       // slot 0
    virtual unsigned short Update();      // slot 1, 00433470
    virtual void Render();            // slot 2
    void ResetSelection();                 // 00433230
    void PollInput();                      // 004388D0
    void ProcessPlayerOptions(signed char player);
    void ProcessSubselection();
    void UpdateSelect(signed char player);
    void UpdatePlayerChoice(signed char player);
    void UpdatePlayerConfirmation(signed char player);
    void UpdateChoiceAnimation(signed char player);
    void UpdateCancelAnimation(signed char player);
    void RenderCards();                  // 00437380
    void RenderOptions();                // 00438240
    void RenderSinglePlayerOptions();    // 00438670

    TextureManagerF198* menuTextures;                    // +008
    SelectInputFrame input[2];             // +00C, +028 (0x1C per player)
    TextureManagerF198* characterTextures;               // +044
    TextureManagerF198* backgroundTextures;              // +048
    int cancellationRequested;              // +04C
    unsigned char leftCharacterAvailable[20];  // +050
    unsigned char rightCharacterAvailable[20]; // +064
    unsigned char stageAvailable[30];      // +078
    signed char playerState[2];            // +096
    float portraitFade[2];                 // +098
    float portraitEnterX[2];               // +0A0
    float portraitEnterY[2];               // +0A8
    float portraitExitX[2];                // +0B0
    float portraitExitY[2];                // +0B8
    float choiceStop[2];                   // +0C0
    unsigned char transitionAlpha;         // +0C8
    unsigned char unknown0C9[3];
    float portraitReturn[2];               // +0CC
    float animationPhase;                 // +0D4
    float choiceOscillation;               // +0D8
    float choiceRotation;                  // +0DC
    signed char chosenCharacter[2];      // +0E0
    signed char alternateCharacter[2];   // +0E2
    unsigned char choiceRandom[2];         // +0E4
    unsigned char chosenPalette[2];        // +0E6
    unsigned char playerReady[2];          // +0E8
    signed char optionsOpen[2];            // +0EA
    signed char optionsCursor[2];          // +0EC
    unsigned char alternatePalette[2];     // +0EE
    signed char stagePage[2];              // +0F0
    signed char stageCountdown[2];         // +0F2
};
#endif
