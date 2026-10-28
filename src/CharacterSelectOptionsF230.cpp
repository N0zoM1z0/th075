// Physically observed signed per-player selectors, 28-byte input stride and
// original game flags. This is a borrowed scene receiver, not a full owner.
class ChoiceSoundF230 {public: void Play(int id);};
extern ChoiceSoundF230* g_ChoiceSoundAt00671618;
extern signed char g_SelectOptionAt00671434[2];
extern unsigned char g_SelectOptionFlagAt00671438[2];
namespace ChoiceInputF230 {int __cdecl TestAction(int input);}
class CharacterSelectOptionsF230 {
public:
    void ProcessPlayerOptions(signed char player);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define I(off) (*reinterpret_cast<int*>(RAW+(off)+player*28))
#define SC(off) (*reinterpret_cast<signed char*>(RAW+(off)+player))
void CharacterSelectOptionsF230::ProcessPlayerOptions(signed char player)
{
    if (ChoiceInputF230::TestAction(I(0x10))==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        SC(0xec)=1-SC(0xec);
    }
    if (SC(0xec)==0) {
        if (I(0x14)==1 || ChoiceInputF230::TestAction(I(0xc))==1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionFlagAt00671438[player]=(static_cast<int>(g_SelectOptionFlagAt00671438[player])?0:1);
        }
    } else {
        if (I(0x14)==1 || I(0xc)==1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionAt00671434[player]=(g_SelectOptionAt00671434[player]+1)%5;
        }
        if (I(0xc)==-1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionAt00671434[player]=(g_SelectOptionAt00671434[player]+4)%5;
        }
    }
    if (I(0x24)==1) {
        g_ChoiceSoundAt00671618->Play(0x28);
        SC(0xea)=!SC(0xea);
    }
}
#undef SC
#undef I
#undef RAW
