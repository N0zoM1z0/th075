#include "MusicRoomScene.hpp"
#include "GameProgress.hpp"
#include "SelectionInput4388D0.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
#define TRACKID (static_cast<int>(records[selectedTrack].counter))
unsigned short MusicRoomScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if (g_InputMappings[0].held.counts[1]==1 || g_InputMappings[1].held.counts[1]==1) {
        ++selectedTrack;
        if (selectedTrack>=trackCount) selectedTrack=0;
        if (g_GameProgress.TestUnlockBit(TRACKID+100))
            RenderSelectedDetails(selectedTrack);
    } else if (g_InputMappings[0].held.counts[1]==-1 || g_InputMappings[1].held.counts[1]==-1) {
        --selectedTrack;
        if (selectedTrack<0) selectedTrack=trackCount-1;
        if (g_GameProgress.TestUnlockBit(TRACKID+100))
            RenderSelectedDetails(selectedTrack);
    }
    if (selectedTrack<firstVisibleTrack) firstVisibleTrack=selectedTrack;
    if (selectedTrack>firstVisibleTrack+9) firstVisibleTrack=selectedTrack-9;
    if ((g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1) && inputCooldown==0 &&
        g_GameProgress.TestUnlockBit(TRACKID+100)) {
        RenderSelectedTitle(selectedTrack);
        MusicF204::PlayTrackByIndex(TRACKID);
        AudioControl407CA0::ScheduleFade(-10000,-170,1,1);
        inputCooldown=60;
    }
    if (((g_InputMappings[0].held.counts[3]==1 || g_InputMappings[1].held.counts[3]==1) && inputCooldown==0) ||
        g_InputMappings[0].IsKeyDown(1)) {
        AudioControl407CA0::ScheduleFade(-10000,-160,1,0);
        return 0x2202;
    } else {
        if (inputCooldown>0) --inputCooldown;
        return 12;
    }
}
#undef TRACKID
