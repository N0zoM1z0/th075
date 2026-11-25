#include "engine/SequenceScenes.hpp"
#include "audio/AudioControl.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>
#include <mmsystem.h>

extern const char g_OpeningPathAt00657CCC[] = "data\\system\\opening.dat";
extern const char g_OpeningRootAt00657CC4[] = "data";
extern const char g_StaffPathAt006582A0[] = "data\\system\\staffroll.dat";
extern const char g_StaffRootAt00658298[] = "data";

OpeningScene::OpeningScene() {
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(24);
    texture->LoadDefault(g_OpeningPathAt00657CCC,g_OpeningRootAt00657CC4);
    MusicF204::PlayTrackByIndex(40);
    MusicF205::ScheduleTransitionFade();
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
}
StaffRollScene::StaffRollScene() {
    AudioControl407CA0::Stop();
    MusicF204::PlayTrackByIndex(41);
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(27);
    texture->LoadDefault(g_StaffPathAt006582A0,g_StaffRootAt00658298);
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
    AudioControl407CA0::Start();
}
