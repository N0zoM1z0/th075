#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "CameraUpdate4126C0.hpp"
#include <windows.h>
// Independently recovered complete original R049 1,291-byte Marisa chain renderer.
// Quad has 132 known rendered bytes but 136 physically owned bytes on this
// stack; no private meaning is asserted for its four-byte untyped tail.
// Genuine align(4) short radius recreates original EBP-4 physical slot.
// An unparenthesized FLOAT(0x1010) lvalue recreates original x87 FLD
// global-depth then FMUL fighter-field instruction evaluation order.
// Borrowed receiver/texture/record field ABIs only, not full owner classes.
// Borrowed receiver, texture manager, record fields and exact 132-byte quad.
// No complete original fighter/auxiliary owner layout is asserted.
class MarisaRendererF356 {
public:
    void SetBlendMode(int mode);
    void DrawProjectileChain(int texture, const void* records, int count);
};
struct MarisaParticleF356 {
    float x,y,z;
    float alpha;
    DWORD flags;
    float phase, tail;
};
typedef char MarisaParticleSizeF356[(sizeof(MarisaParticleF356)==28)?1:-1];
extern const float g_MarisaAngleStepAt00657828;
extern const float g_MarisaAngleMultiplierAt00657850;
extern const float g_MarisaParticleDepthAt006582E0;
extern const float g_MarisaDepthDivisorAt00657480;
extern const float g_MarisaPhaseDivisorAAt00659310;
extern const float g_MarisaPhaseDivisorBAt0065788C;
extern const float g_MarisaPhaseMultiplierAt00657878;
extern const float g_MarisaCameraOffsetXAt00657834;
extern const float g_MarisaCameraOffsetYAt00657830;
extern const float g_MarisaCameraXAt00671404;
extern const float g_MarisaCameraYAt006713C4;
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
class MarisaAuxF356 {public: void RenderChain();};
#define FLOAT(o) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(o))
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
#define DRAWER reinterpret_cast<MarisaRendererF356*>(FIELD(void*,4))
#define REC(i) (reinterpret_cast<MarisaParticleF356*>(reinterpret_cast<unsigned char*>(this)+0x1018)[(i)])
void MarisaAuxF356::RenderChain() {
    if (!FIELD(unsigned char,0x1006)) return;
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
    xShift=g_MarisaCameraXAt00671404-g_MarisaCameraOffsetXAt00657834;
    yOrigin=g_MarisaCameraYAt006713C4;
    DRAWER->SetBlendMode(2);
    for(i=1;i<=8;++i) {
        phaseA=static_cast<short>(i*0x150%40-20);
        phaseB=static_cast<short>(i*0x104%60-30);
        angle=static_cast<short>(i*100);
        radius=static_cast<short>(static_cast<float>(i*10+50)*FIELD(float,0x1010));
        for(j=0;j<36;++j) {
            quad.first.x=CameraCosineAt0040D900(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.first.y=CameraSineAt0040D940(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.first.z=0.0f;
            quad.fourth.x=CameraCosineAt0040D900(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.fourth.y=CameraSineAt0040D940(float(j)*g_MarisaAngleStepAt00657828*g_MarisaAngleMultiplierAt00657850)*radius;
            quad.fourth.z=g_MarisaParticleDepthAt006582E0*FLOAT(0x1010)/g_MarisaDepthDivisorAt00657480;
            reinterpret_cast<SpriteTransform*>(&quad)->RotateQuad(
              0.0f,0.0f,0.0f,
              float(phaseA)+CameraSineAt0040D940(float(i*6)+float(FIELD(unsigned short,0xef8))/g_MarisaPhaseDivisorBAt0065788C)*g_MarisaPhaseMultiplierAt00657878,
              float(phaseB+FIELD(signed char,0x66)*90)+CameraCosineAt0040D900(float(i*7)+float(FIELD(unsigned short,0xef8))/g_MarisaPhaseDivisorAAt00659310)*g_MarisaPhaseMultiplierAt00657878,
              float(FIELD(unsigned short,0xef8)*5+i*5));
            reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(
              float(FIELD(signed char,0x1014)*angle)+FIELD(float,0x1008),-FIELD(float,0x100c),0.0f);
            reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(xShift,yOrigin+g_MarisaCameraOffsetYAt00657830,0.0f);
            REC(j*2).x=quad.first.x;
            REC(j*2).y=quad.first.y;
            REC(j*2).z=quad.first.z;
            REC(j*2+1).x=quad.fourth.x;
            REC(j*2+1).y=quad.fourth.y;
            REC(j*2+1).z=quad.fourth.z;
        }
        REC(72).x=REC(0).x;REC(72).y=REC(0).y;REC(72).z=REC(0).z;
        REC(73).x=REC(1).x;REC(73).y=REC(1).y;REC(73).z=REC(1).z;
        DRAWER->DrawProjectileChain(0x277,&REC(0),0x4a);
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
#undef REC
#undef DRAWER
#undef FIELD
#undef FLOAT
