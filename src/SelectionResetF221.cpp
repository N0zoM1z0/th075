#include "CharacterSelectScene.hpp"
// Restore the initial two-player character-select state.
extern signed char g_PlayerSelectionAt006714C8;
extern unsigned char g_SecondPlayerAt006714C9;
extern unsigned char g_OptionModeAt006714D0;
extern signed char g_StageSelectionAt0067161D;
class ProgressSelectionF221 {
public:
    void RegisterSelection(unsigned char player, unsigned char mode);
};
extern ProgressSelectionF221 g_ProgressSelectionAt006718F8;
void CharacterSelectScene::ResetSelection()
{
    (choiceRandom[1])=1;
    (choiceRandom[0])=1;
    (chosenPalette[1])=0;
    (chosenPalette[0])=0;
    (portraitReturn[1])=100.0f;
    (portraitReturn[0])=100.0f;
    (portraitFade[1])=100.0f;
    (portraitFade[0])=100.0f;
    (portraitEnterX[1])=80.0f;
    (portraitEnterX[0])=80.0f;
    (portraitEnterY[1])=40.0f;
    (portraitEnterY[0])=40.0f;
    (portraitExitX[1])=80.0f;
    (portraitExitX[0])=80.0f;
    (portraitExitY[1])=40.0f;
    (portraitExitY[0])=40.0f;
    (choiceStop[1])=0;
    (choiceStop[0])=0;
    (transitionAlpha)=0;
    (animationPhase)=0;
    (playerState[1])=0;
    (playerState[0])=0;
    (optionsOpen[1])=0;
    (optionsOpen[0])=0;
    (alternatePalette[1])=0;
    (alternatePalette[0])=0;
    (optionsCursor[1])=0;
    (optionsCursor[0])=0;
    (choiceOscillation)=80.0f;
    // Native field +0xDC stores IEEE-754 0x4096CBE2; 4.712388f is the
    // meaningful rounded float literal, unlike 4.712389f (0x4096CBE4).
    (choiceRotation)=4.712388f;
    (chosenCharacter[0])=g_PlayerSelectionAt006714C8;
    (chosenCharacter[1])=g_SecondPlayerAt006714C9;
    (alternateCharacter[0])=(g_PlayerSelectionAt006714C8+1)%10;
    (alternateCharacter[1])=(g_PlayerSelectionAt006714C8+1)%10;
    (playerReady[1])=1;
    (playerReady[0])=1;
    if (g_StageSelectionAt0067161D==20) {
        (stagePage[1])=8;
        (stagePage[0])=1;
    } else {
        (stagePage[1])=g_StageSelectionAt0067161D%10;
        (stagePage[0])=g_StageSelectionAt0067161D>=10;
    }
    g_ProgressSelectionAt006718F8.RegisterSelection(
        g_PlayerSelectionAt006714C8,g_OptionModeAt006714D0);
}
