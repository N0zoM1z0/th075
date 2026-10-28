// Borrowed record/scene side-only interfaces, not a complete original owner.
class NameEntrySoundF246 {public: void Play(int id);};
extern NameEntrySoundF246* g_NameEntrySoundAt00671618;
class NameEntryProgressF246 {
public:
    void SaveScore();
    void LoadWorkingEightBytes(unsigned char player);
};
extern NameEntryProgressF246 g_NameEntryProgressAt006718F8;
extern signed char g_NameEntryExtraFlagAt006714CE;
namespace NameEntryGraphicsF246 {void Present();}
class NameEntryUpdateF246 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short UpdatePlayer();
    void PollPlayerInput();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define SELECTION_CODE (static_cast<int>(FIELD(short,0x10))+static_cast<int>(FIELD(short,0x12))*26)
#define INDEX_OFFSET (static_cast<int>(FIELD(signed char,0x120))*16)
#define CHAR_FIELD(index) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x0c))+0x55c+INDEX_OFFSET+(index)))
#define LAST_CHAR (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x0c))+0x563+INDEX_OFFSET))
unsigned short NameEntryUpdateF246::UpdatePlayer()
{
    PollPlayerInput();
    if (FIELD(short,0x16)==1) {
        g_NameEntrySoundAt00671618->Play(0x2d);
        if (SELECTION_CODE==0x5b) {
            if (FIELD(short,0x14)>7)
                LAST_CHAR=100;
            else
                CHAR_FIELD(FIELD(short,0x14))=100;
        } else if (SELECTION_CODE==0x5c) {
            g_NameEntryProgressAt006718F8.SaveScore();
            g_NameEntryProgressAt006718F8.LoadWorkingEightBytes(FIELD(unsigned char,0x120));
            if (g_NameEntryExtraFlagAt006714CE) return 0x2207;
            return 0x2202;
        } else {
            if (FIELD(short,0x14)>7)
                LAST_CHAR=static_cast<unsigned char>(SELECTION_CODE);
            else
                CHAR_FIELD(FIELD(short,0x14))=static_cast<unsigned char>(SELECTION_CODE);
        }
        ++FIELD(short,0x14);
        if (FIELD(short,0x14)>8)
            FIELD(short,0x14)=8;
        if (FIELD(short,0x14)==8) {
            FIELD(short,0x10)=14;
            FIELD(short,0x12)=3;
        }
    }
    if (FIELD(short,0x16)==2) {
        g_NameEntrySoundAt00671618->Play(0x28);
        --FIELD(short,0x14);
        if (FIELD(short,0x14)<0)
            FIELD(short,0x14)=0;
        CHAR_FIELD(FIELD(short,0x14))=100;
    }
    DrawCurrent();
    NameEntryGraphicsF246::Present();
    return 10;
}
#undef LAST_CHAR
#undef CHAR_FIELD
#undef INDEX_OFFSET
#undef SELECTION_CODE
#undef FIELD
