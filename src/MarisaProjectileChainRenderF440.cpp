#include "TextureManagerF198.hpp"
#include "MarisaFighter.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "CameraUpdate4126C0.hpp"
#include <windows.h>
// Independently recovered complete original R049 1,291-byte Marisa chain renderer.
// Quad has 132 known rendered bytes but 136 physically owned bytes on this
// stack; no private meaning is asserted for its four-byte untyped tail.
// Genuine align(4) short radius recreates original EBP-4 physical slot.
// An unparenthesized field1010 lvalue recreates original x87 FLD
// global-depth then FMUL fighter-field instruction evaluation order.
// Borrowed receiver/texture/record field ABIs only, not full owner classes.
// Borrowed receiver, texture manager, record fields and exact 132-byte quad.
// No complete original fighter/auxiliary owner layout is asserted.
class MarisaRendererF356 {
public:
    void DrawProjectileChain(int texture, const void* records, int count);
};
extern const float g_MarisaAngleStepAt00657828;
extern const float g_MarisaAngleMultiplierAt00657850;
extern const float g_MarisaParticleDepthAt006582E0;
extern const float g_MarisaDepthDivisorAt00657480;
extern const float g_MarisaPhaseDivisorAAt00659310;
extern const float g_MarisaPhaseDivisorBAt0065788C;
extern const float g_MarisaPhaseMultiplierAt00657878;
extern const float g_MarisaCameraOffsetXAt00657834;
extern const float g_MarisaCameraOffsetYAt00657830;
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
struct NativeMarisaQuadF362 { DWORD words[34]; void Construct(); };
typedef char ConfirmMarisaQuadNativeF438[(sizeof(NativeMarisaQuadF362)==136)?1:-1];
struct NativeMarisaStateF358 {
    int j;
    int i;
    short phaseA;
    float xShift;
    NativeMarisaQuadF362 quad;
    short phaseB;
    float yOrigin;
    short angle;
    __declspec(align(4)) short radius;
};
#define DRAWER reinterpret_cast<MarisaRendererF356*>(drawing)
void MarisaFighter::RenderChain() {
    if (!field1006) return;
    NativeMarisaStateF358 state;
    state.quad.Construct();
#define quad (*reinterpret_cast<SpriteQuad40CA80*>(&state.quad))
#define xShift state.xShift
#define yOrigin state.yOrigin
#define i state.i
#define j state.j
#define phaseA state.phaseA
#define phaseB state.phaseB
#define angle state.angle
#define radius state.radius
    xShift=g_CombatViewOffsetX-g_MarisaCameraOffsetXAt00657834;
    yOrigin=g_CombatViewOffsetY;
    reinterpret_cast<TextureManagerF198*>(DRAWER)->SetBlendMode(2);
    for(i=1;i<=8;++i) {
        phaseA=static_cast<short>(i*0x150%40-20);
        phaseB=static_cast<short>(i*0x104%60-30);
        angle=static_cast<short>(i*100);
        radius=static_cast<short>(static_cast<float>(i*10+50)*(field1010));
        for(j=0;j<36;++j) {
            quad.first.x=CameraCosineAt0040D900(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.first.y=CameraSineAt0040D940(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.first.z=0.0f;
            quad.fourth.x=CameraCosineAt0040D900(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.fourth.y=CameraSineAt0040D940(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.fourth.z=g_MarisaParticleDepthAt006582E0*field1010/g_MarisaDepthDivisorAt00657480;
            reinterpret_cast<SpriteTransform*>(&quad)->RotateQuad(
              0.0f,0.0f,0.0f,
              float(phaseA)+CameraSineAt0040D940(float(i*6)+float(fieldEF8)/g_MarisaPhaseDivisorBAt0065788C)*g_MarisaPhaseMultiplierAt00657878,
              float(phaseB+(facing)*90)+CameraCosineAt0040D900(float(i*7)+float(fieldEF8)/g_MarisaPhaseDivisorAAt00659310)*g_MarisaPhaseMultiplierAt00657878,
              float((fieldEF8)*5+i*5));
            reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(
              float((field1014)*angle)+(field1008),-(field100C),0.0f);
            reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(xShift,yOrigin+g_MarisaCameraOffsetYAt00657830,0.0f);
            chain[j*2].x=quad.first.x;
            chain[j*2].y=quad.first.y;
            chain[j*2].z=quad.first.z;
            chain[j*2+1].x=quad.fourth.x;
            chain[j*2+1].y=quad.fourth.y;
            chain[j*2+1].z=quad.fourth.z;
        }
        chain[72].x=chain[0].x;chain[72].y=chain[0].y;chain[72].z=chain[0].z;
        chain[73].x=chain[1].x;chain[73].y=chain[1].y;chain[73].z=chain[1].z;
        DRAWER->DrawProjectileChain(0x277,&chain[0],0x4a);
    }
}
#undef radius
#undef angle
#undef phaseB
#undef phaseA
#undef j
#undef i
#undef yOrigin
#undef xShift
#undef quad
#undef DRAWER
