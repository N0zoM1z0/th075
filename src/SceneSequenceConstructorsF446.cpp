#include "AudioControl.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include <mmsystem.h>
// Two independently original-R036/R043 complete authored scene C++
// constructors; actual 24 vs 27 texture records and stage mode 40 vs 41
// are separately checked. C++ /GX EH, vtables and the imported WinMM
// timeGetTime call are compiled, not embedded native bytes.
// Only the physical 8-byte base, 80-byte texture allocation and real fields.
class SceneBaseF446 {
    void* originalConfiguration;
public: SceneBaseF446(); virtual ~SceneBaseF446();
};
extern const char g_OpeningPathAt00657CCC[];
extern const char g_OpeningRootAt00657CC4[];
extern const char g_StaffPathAt006582A0[];
extern const char g_StaffRootAt00658298[];
class OpeningSceneF446 : public SceneBaseF446 {
    TextureManagerF198* texture;
    unsigned int elapsed;
    unsigned int startTicks;
public:OpeningSceneF446();virtual ~OpeningSceneF446();
};
class StaffRollSceneF446 : public SceneBaseF446 {
    TextureManagerF198* texture;
    unsigned int elapsed;
    unsigned int startTicks;
public:StaffRollSceneF446();virtual ~StaffRollSceneF446();
};
OpeningSceneF446::OpeningSceneF446() {
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(24);
    texture->LoadDefault(g_OpeningPathAt00657CCC,g_OpeningRootAt00657CC4);
    MusicF204::PlayTrackByIndex(40);
    MusicF205::ScheduleTransitionFade();
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
}
StaffRollSceneF446::StaffRollSceneF446() {
    AudioControl407CA0::Stop();
    MusicF204::PlayTrackByIndex(41);
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(27);
    texture->LoadDefault(g_StaffPathAt006582A0,g_StaffRootAt00658298);
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
    AudioControl407CA0::Start();
}
