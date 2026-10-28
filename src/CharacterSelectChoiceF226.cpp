#include <stdlib.h>
// Borrowed scene-state view only. Field offsets and signed player index come
// from complete native instruction decoding, not from a nominal class layout.
class ChoiceSoundBankF226 { public: void Play(int id); };
extern ChoiceSoundBankF226* g_ChoiceSoundAt00671618;
extern unsigned char g_ChoiceRandomModeAt00671610[];
extern unsigned char g_ChoiceStageAt00671621;
extern const float g_ChoiceMinimumAt0065782C;
extern const float g_ChoiceBackStepAt00657874;
extern const float g_ChoiceRiseBoundAt00658268;
extern const float g_ChoiceRiseStepAt00657D14;
extern const float g_ChoiceDropBoundAt00657858;
extern const float g_ChoiceDropStepAt00657480;
extern const float g_ChoiceZeroAt00657CBC;
extern const float g_ChoiceReturnStepAt0065747C;
namespace ChoiceInputF226 { int __cdecl TestAction(int key); }
class CharacterSelectChoiceF226 {
public:
    void UpdatePlayerChoice(signed char player);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define F(off) (reinterpret_cast<float*>(RAW+(off))[player])
#define B(off) (RAW[(off)+player])
#define I(off) (*reinterpret_cast<int*>(RAW+(off)+player*0x1c))
void CharacterSelectChoiceF226::UpdatePlayerChoice(signed char player)
{
    if (g_ChoiceMinimumAt0065782C < F(0xcc))
        F(0xcc) -= g_ChoiceBackStepAt00657874;
    if (F(0xa0) < g_ChoiceRiseBoundAt00658268)
        F(0xa0) = F(0xa0) + g_ChoiceRiseStepAt00657D14;
    if (F(0xa8) < g_ChoiceDropBoundAt00657858)
        F(0xa8) = F(0xa8) + g_ChoiceDropStepAt00657480;
    if (F(0xb0) < g_ChoiceRiseBoundAt00658268)
        F(0xb0) = F(0xb0) + g_ChoiceRiseStepAt00657D14;
    if (F(0xb8) < g_ChoiceDropBoundAt00657858)
        F(0xb8) = F(0xb8) + g_ChoiceDropStepAt00657480;
    if (F(0xc0) < g_ChoiceZeroAt00657CBC)
        F(0xc0) = F(0xc0) + g_ChoiceReturnStepAt0065747C;
    else if (g_ChoiceZeroAt00657CBC < F(0xc0)) {
        F(0xc0) -= g_ChoiceDropStepAt00657480;
        if (F(0xc0) < g_ChoiceZeroAt00657CBC)
            F(0xc0)=0.0f;
    }
    if (I(0x10)==-1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=0;
    } else if (ChoiceInputF226::TestAction(I(0x0c))==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=1;
    } else if (I(0x10)==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=2;
    }
    if (I(0x14)==1) {
        g_ChoiceRandomModeAt00671610[player]=B(0xe6);
        B(0x96)=2;
        g_ChoiceSoundAt00671618->Play(0x2d);
    }
    if (I(0x18)==1) {
        g_ChoiceSoundAt00671618->Play(0x28);
        g_ChoiceStageAt00671621=0;
        RAW[0xec]=0;
        B(0x96)=0;
        F(0xa0)=80.0f;
        F(0xa8)=40.0f;
        F(0xb0)=80.0f;
        F(0xb8)=40.0f;
        B(0xe8)=1;
    }
    if (I(0x20)==1) B(0xe4) = static_cast<unsigned int>(!B(0xe4));
    if (I(0x1c)==1) {
        g_ChoiceRandomModeAt00671610[player]=static_cast<unsigned char>(rand()%3);
        B(0x96)=2;
        g_ChoiceSoundAt00671618->Play(0x2d);
    }
    if (I(0x24)==1) B(0xee) = static_cast<unsigned int>(!B(0xee));
}
#undef F
#undef B
#undef I
#undef RAW
