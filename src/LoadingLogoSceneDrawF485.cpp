#include "LoadingLogoScenes.hpp"
#include "Graphics.hpp"
#include "TextureManagerF198.hpp"
#include "SpriteQuad.hpp"
#include "SpriteTransform.hpp"
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
};
struct DrawFrameF470 {RECT rectangle; DrawQuadF470 quad;};
typedef char CheckFrame152F470[(sizeof(DrawFrameF470)==152)?1:-1];
void LoadingScene::Render() {
 if(Graphics::BeginFrame()) {
    DrawFrameF470 frame;
    frame.quad.ConstructNative();
    texture->SetDepthMode(0);
    texture->SetBlendMode(0);
    SetRect(&frame.rectangle,0,0,640,480);
    reinterpret_cast<SpriteTransform*>(&frame.quad)->BuildQuadFromRect(&frame.rectangle);
    texture->DrawQuad(0, reinterpret_cast<const SpriteQuad40CA80&>(frame.quad),&frame.rectangle,0xffffffff);
    Graphics::EndFrame();
 }
}
void LogoScene::Render() {
 if(Graphics::BeginFrame()) {
    DrawFrameF470 frame;
    frame.quad.ConstructNative();
    texture->SetDepthMode(0);
    texture->SetBlendMode(0);
    SetRect(&frame.rectangle,0,0,640,480);
    reinterpret_cast<SpriteTransform*>(&frame.quad)->BuildQuadFromRect(&frame.rectangle);
    texture->DrawQuad(0, reinterpret_cast<const SpriteQuad40CA80&>(frame.quad),&frame.rectangle,0xffffffff);
    Graphics::EndFrame();
 }
}
