#include "Graphics.hpp"
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
class NameEntryUpdateF246 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short UpdatePlayer();
    void PollPlayerInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x00C - 0x004];
    void* field00C;
    short field010;
    short field012;
    short field014;
    short field016;
    unsigned char unknown018[0x120 - 0x018];
    signed char field120;
};
#define SELECTION_CODE (static_cast<int>(field010)+static_cast<int>(field012)*26)
#define INDEX_OFFSET (static_cast<int>(field120)*16)
#define CHAR_FIELD(index) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(field00C)+0x55c+INDEX_OFFSET+(index)))
#define LAST_CHAR (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(field00C)+0x563+INDEX_OFFSET))
unsigned short NameEntryUpdateF246::UpdatePlayer()
{
    PollPlayerInput();
    if (field016==1) {
        g_NameEntrySoundAt00671618->Play(0x2d);
        if (SELECTION_CODE==0x5b) {
            if (field014>7)
                LAST_CHAR=100;
            else
                CHAR_FIELD(field014)=100;
        } else if (SELECTION_CODE==0x5c) {
            g_NameEntryProgressAt006718F8.SaveScore();
            g_NameEntryProgressAt006718F8.LoadWorkingEightBytes(field120);
            if (g_NameEntryExtraFlagAt006714CE) return 0x2207;
            return 0x2202;
        } else {
            if (field014>7)
                LAST_CHAR=static_cast<unsigned char>(SELECTION_CODE);
            else
                CHAR_FIELD(field014)=static_cast<unsigned char>(SELECTION_CODE);
        }
        ++field014;
        if (field014>8)
            field014=8;
        if (field014==8) {
            field010=14;
            field012=3;
        }
    }
    if (field016==2) {
        g_NameEntrySoundAt00671618->Play(0x28);
        --field014;
        if (field014<0)
            field014=0;
        CHAR_FIELD(field014)=100;
    }
    DrawCurrent();
    Graphics::Present();
    return 10;
}
#undef LAST_CHAR
#undef CHAR_FIELD
#undef INDEX_OFFSET
#undef SELECTION_CODE
