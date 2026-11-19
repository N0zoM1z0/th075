#include "CharacterSelectScene.hpp"
// Main character-select update and transition loop.
class SceneSelectionSoundF229 {public: void Play(int sound);};
extern SceneSelectionSoundF229* g_ChoiceSoundAt00671618;
extern signed char g_ChoiceGameModeAt006714B4;
extern signed char g_ChoiceFocusAt006714B8;
// The native input controller repeats a physically observed 0x48-byte record.
// This borrowed indexed view is not instantiated or used to infer its fields.
struct InputCancelRecordF229 {int cancellation; unsigned char otherNativeBytes[68];};
typedef char InputCancelStride72F229[(sizeof(InputCancelRecordF229)==72)?1:-1];
extern InputCancelRecordF229 g_SelectInputCancelAt00671670[2];
extern signed char g_SelectedFightersAt006714C8[2];
extern unsigned char g_SequenceIdleAt0067161E;
extern signed char g_SequencePhaseAt0067161D;
extern unsigned char g_ModeLeftAt006714AC;
extern unsigned char g_ModeRightAt006714AD;
extern const float g_ChoiceZeroAt0065782C;
extern const float g_ChoiceHalfStepAt00657874;
extern const float g_ChoiceFadeAt00658260;
extern const float g_ChoiceClockStepAt0065825C;
extern const float g_ChoiceRiseLimitAt0065788C;
extern const float g_ChoiceLoopLimitAt00658258;
extern const float g_ChoiceReturnStepAt0065747C;
namespace SelectionGlobalF229 {
    void ResetInput();
    void ChangeScene(int x, int y, int one, int zero);
}
class SelectionReplayF229 {public: void BeginCapture();};
extern SelectionReplayF229 g_ReplayCaptureAt00671750;
#define PLAY(id) g_ChoiceSoundAt00671618->Play(id)
unsigned short CharacterSelectScene::Advance()
{
    PollInput();
    DrawCurrent();
    SelectionGlobalF229::ResetInput();
    if (g_ChoiceHalfStepAt00657874 < (choiceOscillation))
        (choiceOscillation) = (choiceOscillation) * g_ChoiceFadeAt00658260;
    (choiceRotation) = (choiceRotation) + g_ChoiceClockStepAt0065825C;
    if ((playerState[0]) >= 4 && (playerState[1]) >= 4) {
        if ((transitionAlpha) < 255)
            (transitionAlpha) = (transitionAlpha) + 5;
        if ((portraitFade[0]) < g_ChoiceRiseLimitAt0065788C)
            (portraitFade[0]) = (portraitFade[0]) + g_ChoiceHalfStepAt00657874;
        if ((portraitFade[1]) < g_ChoiceRiseLimitAt0065788C)
            (portraitFade[1]) = (portraitFade[1]) + g_ChoiceHalfStepAt00657874;
    } else {
        if ((transitionAlpha) > 5)
            (transitionAlpha) = (transitionAlpha) - 5;
        if (g_ChoiceZeroAt0065782C < (portraitFade[0]))
            (portraitFade[0]) -= g_ChoiceHalfStepAt00657874;
        if (g_ChoiceZeroAt0065782C < (portraitFade[1]))
            (portraitFade[1]) -= g_ChoiceHalfStepAt00657874;
    }
    if (g_ChoiceGameModeAt006714B4==1 || g_ChoiceGameModeAt006714B4==5) {
        if (g_SelectInputCancelAt00671670[g_ChoiceFocusAt006714B8].cancellation==1 || (cancellationRequested)==1) {
            PLAY(0x28);
            if ((optionsOpen[g_ChoiceFocusAt006714B8])!=0) {
                (optionsOpen[g_ChoiceFocusAt006714B8])=0;
            } else if (((playerState[0])==0 && (playerState[1])==0) || (cancellationRequested)==1) {
                return 0x2202;
            }
        }
        if ((input[1-g_ChoiceFocusAt006714B8].cancel)==1) {
            PLAY(0x28);
            if ((optionsOpen[1-g_ChoiceFocusAt006714B8]) != 0) {
                (optionsOpen[1-g_ChoiceFocusAt006714B8]) = 0;
            } else if ((playerState[1-g_ChoiceFocusAt006714B8]) == 0) {
                (input[g_ChoiceFocusAt006714B8].cancel)=1;
            }
        }
    } else if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
        if ((g_SelectInputCancelAt00671670[0].cancellation==1 && (playerState[0])==0) || (cancellationRequested)==1) {
            PLAY(0x28);
            if ((optionsOpen[0])!=0)
                (optionsOpen[0])=0;
            else
                return 0x2202;
        }
        (playerState[1])=8;
    } else if (g_SelectInputCancelAt00671670[0].cancellation==1 && (optionsOpen[0])!=0) {
        PLAY(0x28);
        (optionsOpen[0])=0;
    } else if (g_SelectInputCancelAt00671670[1].cancellation==1 && (optionsOpen[1])!=0) {
        PLAY(0x28);
        (optionsOpen[1])=0;
    } else if ((g_SelectInputCancelAt00671670[0].cancellation==1 || g_SelectInputCancelAt00671670[1].cancellation==1 || (cancellationRequested)==1)
               && (((playerState[0])==0 && (playerState[1])==0) || (cancellationRequested)==1)) {
        PLAY(0x28);
        return 0x2202;
    }
    for (int i=0;i<2;++i) {
        if ((optionsOpen[i])!=0) {
            if (i==0 && g_ChoiceGameModeAt006714B4==3)
                ProcessSubselection();
            else
                ProcessPlayerOptions(static_cast<signed char>(i));
        } else {
            switch ((playerState[i])) {
            case 0: UpdateSelect(static_cast<signed char>(i)); break;
            case 1: UpdatePlayerChoice(static_cast<signed char>(i)); break;
            case 2: UpdatePlayerConfirmation(static_cast<signed char>(i)); break;
            case 4: UpdateChoiceAnimation(static_cast<signed char>(i)); break;
            case 8: UpdateCancelAnimation(static_cast<signed char>(i)); break;
            }
        }
    }
    if ((playerState[0])==8 && (playerState[1])==8) {
        g_SequenceIdleAt0067161E=0;
        if ((g_SelectedFightersAt006714C8[0]==6 || g_SelectedFightersAt006714C8[1]==6) && g_SequencePhaseAt0067161D <6)
            g_SequencePhaseAt0067161D += 10;
        if (g_ChoiceGameModeAt006714B4==3) {
            g_ModeLeftAt006714AC=0;
            g_ModeRightAt006714AD=0;
        }
        SelectionGlobalF229::ChangeScene(-10000,-60,1,0);
        g_ReplayCaptureAt00671750.BeginCapture();
        return 0x2201;
    } else {
        (animationPhase) = (animationPhase) + g_ChoiceReturnStepAt0065747C;
        if (g_ChoiceLoopLimitAt00658258 < (animationPhase))
            (animationPhase) -= g_ChoiceLoopLimitAt00658258;
        return 3;
    }
}
#undef PLAY
