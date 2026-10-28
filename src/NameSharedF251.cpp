// Borrowed player editor, sound device and score persistence receiver. The
// original parent layout remains unproven and is not instantiated.
class NameSharedSoundF251 { public: void Play(int sound); };
extern NameSharedSoundF251* g_NameSoundAt00671618;
class NameScoreF251 { public: void SaveCurrent(); };
extern NameScoreF251 g_NameScoreAt00671750;
extern signed char g_NameModeAt0066C238;
extern unsigned char g_NameLettersAt00671858[8];
extern unsigned char g_NameLastLetterAt0067185F;
namespace NameSharedGraphicsF251 { void Present(); }
class NameSharedSceneF251 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short UpdateShared();
    void PollInput();
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define BYTE(off) (*reinterpret_cast<signed char*>(RAW+(off)))
#define SHORT(off) (*reinterpret_cast<short*>(RAW+(off)))
#define SELECTED (static_cast<int>(SHORT(0xe))+static_cast<int>(SHORT(0x10))*26)
unsigned short NameSharedSceneF251::UpdateShared()
{
    PollInput();
    if (BYTE(0xc)==0) {
        if (SHORT(0x16)==1) {
            g_NameSoundAt00671618->Play(0x2d);
            if (SELECTED==0x5b) {
                if (SHORT(0x12)>7)
                    g_NameLastLetterAt0067185F=100;
                else
                    g_NameLettersAt00671858[SHORT(0x12)]=100;
            } else if (SELECTED==0x5c) {
                if (g_NameModeAt0066C238==1)
                    g_NameScoreAt00671750.SaveCurrent();
                return 0x2202;
            } else {
                if (SHORT(0x12)>7)
                    g_NameLastLetterAt0067185F=static_cast<unsigned char>(SELECTED);
                else
                    g_NameLettersAt00671858[SHORT(0x12)]=static_cast<unsigned char>(SELECTED);
            }
            ++SHORT(0x12);
            if (SHORT(0x12)>8)
                SHORT(0x12)=8;
            if (SHORT(0x12)==8) {
                SHORT(0xe)=14;
                SHORT(0x10)=3;
            }
        }
        if (SHORT(0x16)==2) {
            g_NameSoundAt00671618->Play(0x28);
            --SHORT(0x12);
            g_NameLettersAt00671858[SHORT(0x12)]=100;
            if (SHORT(0x12)<0) {
                BYTE(0xc)=1;
                SHORT(0x12)=0;
            }
        }
    } else if (SHORT(0x16)==1) {
        g_NameSoundAt00671618->Play(0x2d);
        if (SHORT(0x14)==0) {
            BYTE(0xc)=0;
            SHORT(0xe)=0;
            SHORT(0x10)=0;
        } else {
            return 0x2202;
        }
    }
    DrawCurrent();
    NameSharedGraphicsF251::Present();
    return 7;
}
#undef SELECTED
#undef SHORT
#undef BYTE
#undef RAW
