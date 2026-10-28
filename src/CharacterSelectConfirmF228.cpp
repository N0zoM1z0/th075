#include <stdlib.h>
// Borrowed scene receiver; per-player signed-char indices and each physical
// field are grounded by the full native instruction stream.
class ChoiceSoundBankF228 { public: void Play(int id); };
extern ChoiceSoundBankF228* g_ChoiceSoundAt00671618;
extern unsigned char g_ChoiceSelectedPairAt006714CC[];
extern signed char g_ChoiceGameModeAt006714B4;
extern const float g_ChoiceMinimumAt0065782C;
extern const float g_ChoiceBackStepAt00657874;
extern const float g_ChoiceRiseBoundAt00658268;
extern const float g_ChoiceRiseStepAt00657D14;
extern const float g_ChoiceDropBoundAt00657858;
extern const float g_ChoiceDropStepAt00657480;
extern const float g_ChoiceReadyBoundAt0065826C;
namespace ChoiceInputF228 { int __cdecl TestAction(int key); }
class CharacterSelectConfirmF228 {
public:
    void UpdatePlayerConfirmation(signed char player);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define F(off) (reinterpret_cast<float*>(RAW+(off))[player])
#define B(off) (RAW[(off)+player])
#define I(off) (*reinterpret_cast<int*>(RAW+(off)+player*0x1c))
void CharacterSelectConfirmF228::UpdatePlayerConfirmation(signed char player)
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
    if (F(0xc0)<g_ChoiceReadyBoundAt0065826C &&
       (F(0xc0)=F(0xc0)+g_ChoiceDropStepAt00657480,
        g_ChoiceReadyBoundAt0065826C<F(0xc0)))
        F(0xc0)=75.0f;
    if (I(0x10)==-1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=0;
    } else if (ChoiceInputF228::TestAction(I(0x0c))==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=1;
    } else if (I(0x10)==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        B(0xe6)=2;
    }
    if (I(0x14)==1) {
        if (F(0xc0)<g_ChoiceReadyBoundAt0065826C)
            F(0xc0)=75.0f;
        g_ChoiceSelectedPairAt006714CC[player]=B(0xe6);
        B(0x96)=4;
        if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
            RAW[0x96]=8;
            RAW[0x97]=8;
        }
        g_ChoiceSoundAt00671618->Play(0x2d);
    }
    if (I(0x18)==1) {
        g_ChoiceSoundAt00671618->Play(0x28);
        B(0x96)=1;
    }
    if (I(0x20)==1) B(0xe4)=static_cast<unsigned int>(!B(0xe4));
    if (I(0x1c)==1) {
        g_ChoiceSelectedPairAt006714CC[player]=static_cast<unsigned char>(rand()%3);
        B(0x96)=4;
        if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
            RAW[0x96]=8;
            RAW[0x97]=8;
        }
        g_ChoiceSoundAt00671618->Play(0x2d);
    }
    if (I(0x24)==1) B(0xee)=static_cast<unsigned int>(!B(0xee));
}
#undef F
#undef B
#undef I
#undef RAW
