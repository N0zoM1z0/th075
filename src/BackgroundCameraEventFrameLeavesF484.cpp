#include "CommandListF283.hpp"
#include "BattleEndScene.hpp"
#include "EventQueue.hpp"
#include "Graphics.hpp"
#include "CameraMotion.hpp"
#include "BackgroundStageBaseF479.hpp"
#include "WindowOverlayF212.hpp"

NativeBackgroundBaseF479* g_CurrentBattleStageAt00671424;

NativeBackgroundBaseF479::NativeBackgroundBaseF479()
{
}

NativeBackgroundBaseF479::~NativeBackgroundBaseF479()
{
}

// The true camera override is cdecl and writes exactly one byte and
// three raw float input bits to originally distinct camera globals.
extern unsigned char g_CameraOverrideEnabledAt00671414;
extern float g_CameraHorizontalOverrideAt006713E8;
extern float g_CameraVerticalOverrideAt006713BC;
extern float g_CameraZoomOverrideAt006713F4;
void CameraMotionOverrideF484::SetOverride(unsigned char active,float x,float y,float z) {
  g_CameraOverrideEnabledAt00671414=active;
  g_CameraHorizontalOverrideAt006713E8=x;
  g_CameraVerticalOverrideAt006713BC=y;
  g_CameraZoomOverrideAt006713F4=z;
}
void CommandListF283::RemoveFrontIfPresent()
{
    if (queue.size() > 0)
        queue.pop_front();
}
class EventContextF484 {public:EventContextF484* AcquireAndRelease();};
EventContextF484* EventContextF484::AcquireAndRelease() {
 { EventServiceF335 service(16); }
 return this;
}

void __cdecl PulseEventServiceAt00423B20()
{
    EventServiceF335 service(16);
}
namespace FrameCapturePresentF461 {
    void PresentPrimary(IDirect3DTexture8** texture);
}
void WindowOverlayF212::InstallPresentCallback() {
 Graphics::SetPresentCallback(FrameCapturePresentF461::PresentPrimary);
 enabled=0;
}
void WindowOverlayF212::EnableDirectDraw() {
 Graphics::SetPresentCallback(0);
 enabled=1;
}

BattleEndScene::~BattleEndScene()
{
}
