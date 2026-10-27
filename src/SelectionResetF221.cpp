// Constructor-independent character selection reset policy. Offsets are
// physically observed fields only; no complete original scene is declared.
extern signed char g_PlayerSelectionAt006714C8;
extern unsigned char g_SecondPlayerAt006714C9;
extern unsigned char g_OptionModeAt006714D0;
extern signed char g_StageSelectionAt0067161D;
class ProgressSelectionF221 {
public:
    void RegisterSelection(unsigned char player, unsigned char mode);
};
extern ProgressSelectionF221 g_ProgressSelectionAt006718F8;
class CharacterSelectionF221 {
public:
    void ResetSelection();
};
#define BYTE(off) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define FLOAT(off) (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define DWORD(off) (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this)+(off)))
void CharacterSelectionF221::ResetSelection()
{
    BYTE(0xe5)=1;
    BYTE(0xe4)=1;
    BYTE(0xe7)=0;
    BYTE(0xe6)=0;
    FLOAT(0xd0)=100.0f;
    FLOAT(0xcc)=100.0f;
    FLOAT(0x9c)=100.0f;
    FLOAT(0x98)=100.0f;
    FLOAT(0xa4)=80.0f;
    FLOAT(0xa0)=80.0f;
    FLOAT(0xac)=40.0f;
    FLOAT(0xa8)=40.0f;
    FLOAT(0xb4)=80.0f;
    FLOAT(0xb0)=80.0f;
    FLOAT(0xbc)=40.0f;
    FLOAT(0xb8)=40.0f;
    DWORD(0xc4)=0;
    DWORD(0xc0)=0;
    BYTE(0xc8)=0;
    DWORD(0xd4)=0;
    BYTE(0x97)=0;
    BYTE(0x96)=0;
    BYTE(0xeb)=0;
    BYTE(0xea)=0;
    BYTE(0xef)=0;
    BYTE(0xee)=0;
    BYTE(0xed)=0;
    BYTE(0xec)=0;
    FLOAT(0xd8)=80.0f;
    // Native field +0xDC stores IEEE-754 0x4096CBE2; 4.712388f is the
    // meaningful rounded float literal, unlike 4.712389f (0x4096CBE4).
    FLOAT(0xdc)=4.712388f;
    BYTE(0xe0)=g_PlayerSelectionAt006714C8;
    BYTE(0xe1)=g_SecondPlayerAt006714C9;
    BYTE(0xe2)=(g_PlayerSelectionAt006714C8+1)%10;
    BYTE(0xe3)=(g_PlayerSelectionAt006714C8+1)%10;
    BYTE(0xe9)=1;
    BYTE(0xe8)=1;
    if (g_StageSelectionAt0067161D==20) {
        BYTE(0xf1)=8;
        BYTE(0xf0)=1;
    } else {
        BYTE(0xf1)=g_StageSelectionAt0067161D%10;
        BYTE(0xf0)=g_StageSelectionAt0067161D>=10;
    }
    g_ProgressSelectionAt006718F8.RegisterSelection(
        g_PlayerSelectionAt006714C8,g_OptionModeAt006714D0);
}
#undef BYTE
#undef FLOAT
#undef DWORD
