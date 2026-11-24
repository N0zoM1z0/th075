#include "Graphics.hpp"
// Native actual background base lifetime: vtable and borrowed +0x18
// resource member destroyed by the compiler, no guessed private fields.
class BackgroundResourceF484 {public:~BackgroundResourceF484();};
class BackgroundBaseF484 {
  unsigned char untypedOwnerBytes[0x14];
  BackgroundResourceF484 resource;
public:virtual ~BackgroundBaseF484();
};
BackgroundBaseF484::~BackgroundBaseF484() {}
// The true camera override is cdecl and writes exactly one byte and
// three raw float input bits to originally distinct camera globals.
extern unsigned char g_CameraOverrideEnabledAt00671414;
extern float g_CameraHorizontalOverrideAt006713E8;
extern float g_CameraVerticalOverrideAt006713BC;
extern float g_CameraZoomOverrideAt006713F4;
namespace CameraMotionOverrideF484 {
 void SetOverride(unsigned char active,float x,float y,float z);
}
void CameraMotionOverrideF484::SetOverride(unsigned char active,float x,float y,float z) {
  g_CameraOverrideEnabledAt00671414=active;
  g_CameraHorizontalOverrideAt006713E8=x;
  g_CameraVerticalOverrideAt006713BC=y;
  g_CameraZoomOverrideAt006713F4=z;
}
class SpriteDequeF484 {public: unsigned int Size();void PopFront();};
class SpriteSequenceF484 {
 unsigned int originalPrefixWord;
 SpriteDequeF484 deque;
public:void RemoveFrontIfPresent();
};
void SpriteSequenceF484::RemoveFrontIfPresent() {
 if(deque.Size()>0) deque.PopFront();
}
class EventLocalServiceF484 {public:EventLocalServiceF484(int);~EventLocalServiceF484();};
class EventContextF484 {public:EventContextF484* AcquireAndRelease();};
EventContextF484* EventContextF484::AcquireAndRelease() {
 { EventLocalServiceF484 service(16); }
 return this;
}

void __cdecl PulseEventServiceAt00423B20()
{
    EventLocalServiceF484 service(16);
}
namespace FrameCapturePresentF461 {
    void PresentPrimary(IDirect3DTexture8** texture);
}
class FrameCapturePolicyF484 {
 IDirect3DTexture8* target;
 unsigned char directDrawEnabled;
public:void InstallPresentCallback();void EnableDirectDraw();
};
void FrameCapturePolicyF484::InstallPresentCallback() {
 Graphics::SetPresentCallback(FrameCapturePresentF461::PresentPrimary);
 directDrawEnabled=0;
}
void FrameCapturePolicyF484::EnableDirectDraw() {
 Graphics::SetPresentCallback(0);
 directDrawEnabled=1;
}
class NativeSceneBaseF484 {public:virtual ~NativeSceneBaseF484();};
class BattleEndSceneF484: public NativeSceneBaseF484 {public:virtual ~BattleEndSceneF484();};
BattleEndSceneF484::~BattleEndSceneF484(){}
