// The scene fields and native signed player selector have been observed
// independently. No full original class or input owner layout is asserted.
// F346: STOP_FLOAT deliberately lacks the outer rvalue parentheses used by
// FLOAT. A literal C++ expression macro of this form reproduces the native
// x87 FLD [global] then FLD [indexed field] order at the *final* equality,
// without altering the four earlier inequalities. No instruction bytes are
// patched, inserted or suppressed.
class SceneSelectionSoundF270 {public: void Play(int sound);};
extern SceneSelectionSoundF270* g_ChoiceSoundAt00671618;
extern const float g_ChoiceCancelHorizontalLimitAt00658268;
extern const float g_ChoiceCancelHorizontalStepAt00657D14;
extern const float g_ChoiceCancelVerticalLimitAt00657858;
extern const float g_ChoiceCancelVerticalStepAt00657480;
extern const float g_ChoiceZeroAt0065782C;
extern const float g_ChoiceCancelReturnStepAt0065747C;
extern const float g_ChoiceCancelStopAt00658264;
class CharacterSelectCancelF270 {
public:
    void UpdateCancelAnimation(signed char player);
};
#define BYTE(off,i) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+(off)+(i)))
#define FLOAT(off,i) (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(off)+4*(i)))
#define DWord(off,i) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this)+(off)+4*(i)))
#define STOP_FLOAT(i) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0xc0 + 4*(i))
#define MODE(i) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this)+0x18+0x1c*(i)))
void CharacterSelectCancelF270::UpdateCancelAnimation(signed char player)
{
    if (FLOAT(0xa0,player)<g_ChoiceCancelHorizontalLimitAt00658268)
        FLOAT(0xa0,player)=FLOAT(0xa0,player)+g_ChoiceCancelHorizontalStepAt00657D14;
    if (FLOAT(0xa8,player)<g_ChoiceCancelVerticalLimitAt00657858)
        FLOAT(0xa8,player)=FLOAT(0xa8,player)+g_ChoiceCancelVerticalStepAt00657480;
    if (FLOAT(0xb0,player)<g_ChoiceCancelHorizontalLimitAt00658268)
        FLOAT(0xb0,player)=FLOAT(0xb0,player)+g_ChoiceCancelHorizontalStepAt00657D14;
    if (FLOAT(0xb8,player)<g_ChoiceCancelVerticalLimitAt00657858)
        FLOAT(0xb8,player)=FLOAT(0xb8,player)+g_ChoiceCancelVerticalStepAt00657480;
    if (g_ChoiceZeroAt0065782C<FLOAT(0xc0,player))
        FLOAT(0xc0,player)=FLOAT(0xc0,player)-g_ChoiceCancelReturnStepAt0065747C;
    if (STOP_FLOAT(player)==g_ChoiceCancelStopAt00658264)
        DWord(0xc0,player)=0;
    if (MODE(player)==1) {
        g_ChoiceSoundAt00671618->Play(40);
        BYTE(0x96,player)=0;
        FLOAT(0xa0,player)=80.0f;
        FLOAT(0xa8,player)=40.0f;
        FLOAT(0xb0,player)=80.0f;
        FLOAT(0xb8,player)=40.0f;
        BYTE(0xe8,player)=1;
    }
}
#undef BYTE
#undef FLOAT
#undef DWord
#undef MODE
#undef STOP_FLOAT
