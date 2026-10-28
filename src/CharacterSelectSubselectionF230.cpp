// Borrowed scene and existing progress-card receiver; no invented owner type.
class ChoiceSoundF230 {public: void Play(int id);};
extern ChoiceSoundF230* g_ChoiceSoundAt00671618;
class ProgressCardViewF230 {public: signed char GetSelectedValue();};
extern ProgressCardViewF230 g_SelectedCardAt006718F8;
extern unsigned char g_SelectedFighterAt006714C8;
extern unsigned char g_PlayerPadAt00671620;
extern unsigned char g_SelectStageAt00671621;
extern unsigned char g_ChosenModeAt006714AC;
namespace ChoiceInputF230 {int __cdecl TestAction(int input);}
class CharacterSelectSubselectionF230 {public: void ProcessSubselection();};
#define RAW reinterpret_cast<unsigned char*>(this)
#define I(off) (*reinterpret_cast<int*>(RAW+(off)))
#define B(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define SC(off) (*reinterpret_cast<signed char*>(RAW+(off)))
void CharacterSelectSubselectionF230::ProcessSubselection()
{
    if (ChoiceInputF230::TestAction(I(0x10))==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        SC(0xec)=(SC(0xec)+I(0x10)+g_SelectedCardAt006718F8.GetSelectedValue())%g_SelectedCardAt006718F8.GetSelectedValue();
    }
    if (I(0x14)==1) {
        g_ChoiceSoundAt00671618->Play(0x2d);
        g_SelectedFighterAt006714C8=B(0xe0);
        g_PlayerPadAt00671620=SC(0xec)+1;
        g_SelectStageAt00671621=1;
        g_ChosenModeAt006714AC=0;
        B(0x96)=1;
        I(0xc0)=0;
        B(0xea)=0;
    }
    if (I(0x24)==1 || I(0x18)==1) {
        g_PlayerPadAt00671620=1;
        g_ChoiceSoundAt00671618->Play(0x28);
        B(0xea)=0;
        B(0xec)=0;
    }
}
#undef SC
#undef B
#undef I
#undef RAW
