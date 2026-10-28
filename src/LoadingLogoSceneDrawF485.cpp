#include <windows.h>
// Independently complete original native Loading/Logo scene draw routines.
// The borrowed DrawQuad::ConstructNative() is the original 0040D990
// zero-argument native quad CONSTRUCTOR ENTRYPOINT, not a claim of its
// original C++ public method spelling. Expressing it as a callable
// constructor entrypoint on a physically observed contiguous 152-byte
// RECT+quad stack carrier restores the native receiver EBP-0x88, whereas
// implicit construction of the enclosing aggregate incorrectly calls
// the receiver at EBP-0x98. Its final quad bytes remain untyped.
// Two independently original R036 native loading/logo scene drawing paths.
// Native 0x98 byte combined RECT and physical136 quad scene frame, no
// claim to private quad's untyped final four payload bytes.
class DrawQuadF470 {
  unsigned int physicalStorage[34];
public:
  void ConstructNative();
  void BuildQuadFromRect(const RECT* rectangle);
};
struct DrawFrameF470 {RECT rectangle; DrawQuadF470 quad;};
typedef char CheckFrame152F470[(sizeof(DrawFrameF470)==152)?1:-1];
class SceneTextureDrawerF470 {
public:
 void SetDepthMode(int);
 void SetBlendMode(int);
 void DrawQuad(int,const DrawQuadF470*,const RECT*,unsigned int);
};
extern unsigned char __cdecl GraphicsBeginAt00402660();
extern void __cdecl GraphicsAdvanceAt004027D0();
class LoadingSceneDrawF470 {
  unsigned char borrowedNativeBase[8];
  SceneTextureDrawerF470* drawer;
public: void Draw();
};
class LogoSceneDrawF470 {
  unsigned char borrowedNativeBase[8];
  SceneTextureDrawerF470* drawer;
public: void Draw();
};
void LoadingSceneDrawF470::Draw() {
 if(GraphicsBeginAt00402660()) {
    DrawFrameF470 frame;
    frame.quad.ConstructNative();
    drawer->SetDepthMode(0);
    drawer->SetBlendMode(0);
    SetRect(&frame.rectangle,0,0,640,480);
    frame.quad.BuildQuadFromRect(&frame.rectangle);
    drawer->DrawQuad(0,&frame.quad,&frame.rectangle,0xffffffff);
    GraphicsAdvanceAt004027D0();
 }
}
void LogoSceneDrawF470::Draw() {
 if(GraphicsBeginAt00402660()) {
    DrawFrameF470 frame;
    frame.quad.ConstructNative();
    drawer->SetDepthMode(0);
    drawer->SetBlendMode(0);
    SetRect(&frame.rectangle,0,0,640,480);
    frame.quad.BuildQuadFromRect(&frame.rectangle);
    drawer->DrawQuad(0,&frame.quad,&frame.rectangle,0xffffffff);
    GraphicsAdvanceAt004027D0();
 }
}
