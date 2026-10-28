// Borrowed physical scene and input views; the complete nominal scene and
// the input-provider element layout have not been reconstructed.
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
class CharacterSelectAdvanceF229 {
public:
    virtual void VirtualZero();
    virtual void VirtualOne();
    virtual void DrawCurrent();
    unsigned short Advance();
    void PollInput();
    void ProcessPlayerOptions(signed char player);
    void ProcessSubselection();
    void UpdateSelect(signed char player);
    void UpdatePlayerChoice(signed char player);
    void UpdatePlayerConfirmation(signed char player);
    void UpdateChoiceAnimation(signed char player);
    void UpdateCancelAnimation(signed char player);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define F(off) (*reinterpret_cast<float*>(RAW + (off)))
#define B(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define S(off) (*reinterpret_cast<signed char*>(RAW+(off)))
#define D(off) (*reinterpret_cast<int*>(RAW+(off)))
#define PWORD(off,index) (*reinterpret_cast<int*>(RAW+(off)+(index)*0x1c))
#define PLAY(id) g_ChoiceSoundAt00671618->Play(id)
unsigned short CharacterSelectAdvanceF229::Advance()
{
    PollInput();
    DrawCurrent();
    SelectionGlobalF229::ResetInput();
    if (g_ChoiceHalfStepAt00657874 < F(0xd8))
        F(0xd8) = F(0xd8) * g_ChoiceFadeAt00658260;
    F(0xdc) = F(0xdc) + g_ChoiceClockStepAt0065825C;
    if (S(0x96) >= 4 && S(0x97) >= 4) {
        if (B(0xc8) < 255)
            B(0xc8) = B(0xc8) + 5;
        if (F(0x98) < g_ChoiceRiseLimitAt0065788C)
            F(0x98) = F(0x98) + g_ChoiceHalfStepAt00657874;
        if (F(0x9c) < g_ChoiceRiseLimitAt0065788C)
            F(0x9c) = F(0x9c) + g_ChoiceHalfStepAt00657874;
    } else {
        if (B(0xc8) > 5)
            B(0xc8) = B(0xc8) - 5;
        if (g_ChoiceZeroAt0065782C < F(0x98))
            F(0x98) -= g_ChoiceHalfStepAt00657874;
        if (g_ChoiceZeroAt0065782C < F(0x9c))
            F(0x9c) -= g_ChoiceHalfStepAt00657874;
    }
    if (g_ChoiceGameModeAt006714B4==1 || g_ChoiceGameModeAt006714B4==5) {
        if (g_SelectInputCancelAt00671670[g_ChoiceFocusAt006714B8].cancellation==1 || D(0x4c)==1) {
            PLAY(0x28);
            if (S(0xea+g_ChoiceFocusAt006714B8)!=0) {
                B(0xea+g_ChoiceFocusAt006714B8)=0;
            } else if ((S(0x96)==0 && S(0x97)==0) || D(0x4c)==1) {
                return 0x2202;
            }
        }
        if (PWORD(0x18,1-g_ChoiceFocusAt006714B8)==1) {
            PLAY(0x28);
            if (reinterpret_cast<signed char*>(RAW+0xea)[1-g_ChoiceFocusAt006714B8] != 0) {
                reinterpret_cast<unsigned char*>(RAW+0xea)[1-g_ChoiceFocusAt006714B8] = 0;
            } else if (reinterpret_cast<signed char*>(RAW+0x96)[1-g_ChoiceFocusAt006714B8] == 0) {
                PWORD(0x18,g_ChoiceFocusAt006714B8)=1;
            }
        }
    } else if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
        if ((g_SelectInputCancelAt00671670[0].cancellation==1 && S(0x96)==0) || D(0x4c)==1) {
            PLAY(0x28);
            if (S(0xea)!=0)
                B(0xea)=0;
            else
                return 0x2202;
        }
        B(0x97)=8;
    } else if (g_SelectInputCancelAt00671670[0].cancellation==1 && S(0xea)!=0) {
        PLAY(0x28);
        B(0xea)=0;
    } else if (g_SelectInputCancelAt00671670[1].cancellation==1 && S(0xeb)!=0) {
        PLAY(0x28);
        B(0xeb)=0;
    } else if ((g_SelectInputCancelAt00671670[0].cancellation==1 || g_SelectInputCancelAt00671670[1].cancellation==1 || D(0x4c)==1)
               && ((S(0x96)==0 && S(0x97)==0) || D(0x4c)==1)) {
        PLAY(0x28);
        return 0x2202;
    }
    for (int i=0;i<2;++i) {
        if (S(0xea+i)!=0) {
            if (i==0 && g_ChoiceGameModeAt006714B4==3)
                ProcessSubselection();
            else
                ProcessPlayerOptions(static_cast<signed char>(i));
        } else {
            switch (S(0x96+i)) {
            case 0: UpdateSelect(static_cast<signed char>(i)); break;
            case 1: UpdatePlayerChoice(static_cast<signed char>(i)); break;
            case 2: UpdatePlayerConfirmation(static_cast<signed char>(i)); break;
            case 4: UpdateChoiceAnimation(static_cast<signed char>(i)); break;
            case 8: UpdateCancelAnimation(static_cast<signed char>(i)); break;
            }
        }
    }
    if (S(0x96)==8 && S(0x97)==8) {
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
        F(0xd4) = F(0xd4) + g_ChoiceReturnStepAt0065747C;
        if (g_ChoiceLoopLimitAt00658258 < F(0xd4))
            F(0xd4) -= g_ChoiceLoopLimitAt00658258;
        return 3;
    }
}
#undef PLAY
#undef PWORD
#undef D
#undef S
#undef B
#undef F
#undef RAW
