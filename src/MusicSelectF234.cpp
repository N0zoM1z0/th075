#include "SelectionInput4388D0.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
// Physical per-track byte records (16-byte stride), not a recovered nominal
// scene or collection type. All external receivers are existing callees.
class MusicTrackStateF234 {
public:
    unsigned char IsUnlocked(int id);
};
extern MusicTrackStateF234 g_TrackProgressAt006718F8;
class MusicRoomSelectionF234 {
public:
    virtual void VirtualZero();
    virtual void VirtualOne();
    virtual void DrawCurrent();
    unsigned short UpdateSelection();
    void PollInput();
    void Highlight(unsigned char index);
    void Choose(unsigned char index);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define S(off) (*reinterpret_cast<signed char*>(RAW+(off)))
#define B(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define TRACKID (static_cast<int>(S(0x1c + S(0x3de)*16)))
unsigned short MusicRoomSelectionF234::UpdateSelection()
{
    PollInput();
    DrawCurrent();
    Graphics::Present();
    if (g_InputMappings[0].held.counts[1]==1 || g_InputMappings[1].held.counts[1]==1) {
        ++S(0x3de);
        if (S(0x3de)>=S(0x3dc)) B(0x3de)=0;
        if (g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100))
            Highlight(B(0x3de));
    } else if (g_InputMappings[0].held.counts[1]==-1 || g_InputMappings[1].held.counts[1]==-1) {
        --S(0x3de);
        if (S(0x3de)<0) S(0x3de)=S(0x3dc)-1;
        if (g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100))
            Highlight(B(0x3de));
    }
    if (S(0x3de)<S(0x3df)) B(0x3df)=B(0x3de);
    if (S(0x3de)>S(0x3df)+9) S(0x3df)=S(0x3de)-9;
    if ((g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1) && S(0x3dd)==0 &&
        g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100)) {
        Choose(B(0x3de));
        MusicF204::PlayTrackByIndex(TRACKID);
        AudioControl407CA0::ScheduleFade(-10000,-170,1,1);
        B(0x3dd)=60;
    }
    if (((g_InputMappings[0].held.counts[3]==1 || g_InputMappings[1].held.counts[3]==1) && S(0x3dd)==0) ||
        g_InputMappings[0].IsKeyDown(1)) {
        AudioControl407CA0::ScheduleFade(-10000,-160,1,0);
        return 0x2202;
    } else {
        if (S(0x3dd)>0) --S(0x3dd);
        return 12;
    }
}
#undef TRACKID
#undef B
#undef S
#undef RAW
