// Physical per-track byte records (16-byte stride), not a recovered nominal
// scene or collection type. All external receivers are existing callees.
class MusicTrackStateF234 {
public:
    unsigned char IsUnlocked(int id);
};
extern MusicTrackStateF234 g_TrackProgressAt006718F8;
class MusicInputF234 {
public:
    unsigned char IsKeyDown(int key);
};
extern MusicInputF234 g_MusicInputAt00671638;
extern int g_MusicUpAt00671668;
extern int g_MusicUpAltAt006716B0;
extern int g_MusicDownAt0067166C;
extern int g_MusicDownAltAt006716B4;
extern int g_MusicCancelAt00671670;
extern int g_MusicCancelAltAt006716B8;
namespace MusicAudioF234 {
    void PlayMusic(int trackId);
    void Transition(int x,int y,int one,int mode);
    void EndInput();
}
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
    MusicAudioF234::EndInput();
    if (g_MusicUpAt00671668==1 || g_MusicUpAltAt006716B0==1) {
        ++S(0x3de);
        if (S(0x3de)>=S(0x3dc)) B(0x3de)=0;
        if (g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100))
            Highlight(B(0x3de));
    } else if (g_MusicUpAt00671668==-1 || g_MusicUpAltAt006716B0==-1) {
        --S(0x3de);
        if (S(0x3de)<0) S(0x3de)=S(0x3dc)-1;
        if (g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100))
            Highlight(B(0x3de));
    }
    if (S(0x3de)<S(0x3df)) B(0x3df)=B(0x3de);
    if (S(0x3de)>S(0x3df)+9) S(0x3df)=S(0x3de)-9;
    if ((g_MusicDownAt0067166C==1 || g_MusicDownAltAt006716B4==1) && S(0x3dd)==0 &&
        g_TrackProgressAt006718F8.IsUnlocked(TRACKID+100)) {
        Choose(B(0x3de));
        MusicAudioF234::PlayMusic(TRACKID);
        MusicAudioF234::Transition(-10000,-170,1,1);
        B(0x3dd)=60;
    }
    if (((g_MusicCancelAt00671670==1 || g_MusicCancelAltAt006716B8==1) && S(0x3dd)==0) ||
        g_MusicInputAt00671638.IsKeyDown(1)) {
        MusicAudioF234::Transition(-10000,-160,1,0);
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
