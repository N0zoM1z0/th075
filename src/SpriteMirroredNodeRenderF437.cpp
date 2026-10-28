#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>

// All scene, child, and drawing owner declarations are borrowed call-only
// views: only the two complete native 132-byte stack quad values are owned.
class SpriteRenderDeviceF254 {
public:
    void GetTextureRect(int texture, RECT* result);
    void SetTextureFilter(int value);
    void DrawQuad(int texture, const SpriteQuad40CA80&, const RECT*, DWORD);
    void DrawTintedQuad(int texture, const SpriteQuad40CA80&, const RECT*,float,float,float,DWORD);
};
class SpriteCameraF254 { public: void CopyVector(float* out); };
extern SpriteCameraF254* g_ActiveCameraAt00671424;
extern float g_CameraXAt00671404;
extern float g_CameraYAt006713C4;
extern const float g_CameraOffsetXAt00657834;
extern const float g_CameraOffsetYAt00657830;
extern const float g_ZeroAt0065782C;

namespace SpriteDispatchF254 {
    void Combine(SpriteQuad40CA80* destination,DWORD* color,SpriteQuad40CA80* source);
}
class RawSpriteScaleF254 {
public: void ScaleQuad(float,float,float,DWORD,DWORD,DWORD);
};
class FloatSpriteScaleF254 {
public: void ScaleQuad(float,float,float,float,DWORD,DWORD);
};
class RawSpriteRotateF254 {
public: void RotateQuad(float,float,float,DWORD,DWORD,DWORD);
};
class RawZSpriteScaleF381 {public:void ScaleQuad(float,float,DWORD,DWORD,DWORD,DWORD);};
class FloatSpriteRotateF254 {
public: void RotateQuad(float,float,DWORD,DWORD,DWORD,float);
};
// Only genuine live native fields are represented, no private scene owner.
// F437 independently reconstructed entire 1,268-byte R035 mirrored-node
// sprite renderer; the native stack has two *observed* 140-byte allocation
// extents even though only 132 bytes in each are decoded as geometry. The
// final eight bytes of each carrier have no asserted private field identity
// and are never read, written or counted separately as additional CODE.
// Comparison of previously exact F129/F126 renderers proves an
// unparenthesized float field lvalue makes VC7.1 emit native FILD/MOV/FSUBR
// rather than nonnative FLD/loaded-index/FISUB. No manual assembly.
// Original stack layout has each independently constructed quad carrier at
// a 140-byte interval, with 132 known rendered packet bytes and two unused
// but physically reserved DWORDs. Only first 132 bytes are ever accessed.
struct RawQuadCarrierF355 { DWORD words[35]; void Construct(); };
typedef char CheckCarrierSizeF355[(sizeof(RawQuadCarrierF355)==140)?1:-1];
struct NativeMirrorFrameF355 {
    RECT sourceRect;
    RawQuadCarrierF355 composed;
    float tint[3];
    float xShift;
    DWORD color;
    RawQuadCarrierF355 transformed;
    float yOrigin;
};
class MirroredNodeF254 {public:void RenderMirroredNode();};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(offset))
#define NODE_RAW reinterpret_cast<unsigned char*>(FIELD(void*,0x08))
#define NODE(type,off) (*reinterpret_cast<type*>(NODE_RAW+(off)))
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
#define DRAWER (*reinterpret_cast<SpriteRenderDeviceF254**>(RAW+4))
#define SCALE(q,x,y,z,sx,sy,sz) reinterpret_cast<RawSpriteScaleF254*>(&(q))->ScaleQuad(x,y,z,sx,sy,sz)
#define SCALE_RAWZ(q,x,y,z,sx,sy,sz) reinterpret_cast<RawZSpriteScaleF381*>(&(q))->ScaleQuad(x,y,z,sx,sy,sz)
#define SCALE_FLOAT(q,x,y,z,sx,sy,sz) reinterpret_cast<FloatSpriteScaleF254*>(&(q))->ScaleQuad(x,y,z,sx,sy,sz)
#define ROTATE_FLOAT(q,x,y,z,sx,sy,sz) reinterpret_cast<FloatSpriteRotateF254*>(&(q))->RotateQuad(x,y,z,sx,sy,sz)
#define ROTATE(q,x,y,z,sx,sy,sz) reinterpret_cast<RawSpriteRotateF254*>(&(q))->RotateQuad(x,y,z,sx,sy,sz)
void MirroredNodeF254::RenderMirroredNode()
{
    NativeMirrorFrameF355 state;
    state.transformed.Construct();
    state.composed.Construct();
#define transformed (*reinterpret_cast<SpriteQuad40CA80*>(&state.transformed))
#define composed (*reinterpret_cast<SpriteQuad40CA80*>(&state.composed))
#define xShift state.xShift
#define yOrigin state.yOrigin
#define sourceRect state.sourceRect
#define color state.color
#define tint state.tint
    xShift = g_CameraXAt00671404 - g_CameraOffsetXAt00657834;
    yOrigin = g_CameraYAt006713C4;
    DRAWER->GetTextureRect(NODE(short,6),&sourceRect);
    TRANSFORM(transformed)->BuildQuadFromRect(&sourceRect);
    if (NODE(void*,8)) {
        SCALE(transformed,static_cast<float>(NODE(short,0)),static_cast<float>(NODE(short,2)),0.0f,
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x0c),
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x10),
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x14));
        ROTATE(transformed,static_cast<float>(NODE(short,0)),static_cast<float>(NODE(short,2)),0.0f,
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x18),
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x1c),
              *reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(NODE(void*,8))+0x20));
        SCALE_FLOAT(transformed,0.0f,0.0f,0.0f,static_cast<float>(FIELD(signed char,0x66)),0x3f800000,0x3f800000);
    } else if (NODE(unsigned char,0x0c)) {
        SCALE_FLOAT(transformed,0.0f,0.0f,0.0f,static_cast<float>(static_cast<int>(FIELD(signed char,0x66))<<1),0x40000000,0x40000000);
    }
    if (FIELD(unsigned char,0x40)) {
        SCALE_RAWZ(transformed,static_cast<float>(FIELD(signed char,0x66))*(static_cast<float>(NODE(short,0))+FIELD(float,0x34)),static_cast<float>(NODE(short,2))-FIELD(float,0x38),FIELD(DWORD,0x3c),FIELD(DWORD,0x1c),FIELD(DWORD,0x20),FIELD(DWORD,0x24));
        ROTATE_FLOAT(transformed,static_cast<float>(FIELD(signed char,0x66))*(static_cast<float>(NODE(short,0))+FIELD(float,0x34)),static_cast<float>(NODE(short,2))-FIELD(float,0x38),FIELD(DWORD,0x3c),FIELD(DWORD,0x28),FIELD(DWORD,0x2c),
               static_cast<float>(FIELD(signed char,0x66))*FIELD(float,0x30));
    }
    TRANSFORM(transformed)->TranslateQuad(FLOAT(0x44)-FIELD(signed char,0x66)*NODE(short,0),
                                         -FIELD(float,0x48)-static_cast<float>(NODE(short,2)),0.0f);
    SpriteDispatchF254::Combine(&composed,&color,&transformed);
    TRANSFORM(composed)->TranslateQuad(xShift,yOrigin+g_CameraOffsetYAt00657830+FIELD(float,0x6c),0.0f);
    g_ActiveCameraAt00671424->CopyVector(tint);
    DRAWER->SetTextureFilter(2);
    if (tint[0] != g_ZeroAt0065782C || tint[1] != g_ZeroAt0065782C || tint[2] != g_ZeroAt0065782C) {
        DRAWER->DrawTintedQuad(NODE(short,6),composed,&sourceRect,tint[0]+xShift,tint[1]+yOrigin,tint[2],color);
    } else {
        DRAWER->DrawQuad(NODE(short,6),composed,&sourceRect,color);
    }
    DRAWER->SetTextureFilter(1);
}
#undef tint
#undef color
#undef sourceRect
#undef yOrigin
#undef xShift
#undef composed
#undef transformed
#undef ROTATE
#undef SCALE_RAWZ
#undef SCALE
#undef SCALE_FLOAT
#undef ROTATE_FLOAT
#undef DRAWER
#undef TRANSFORM
#undef NODE
#undef FLOAT
#undef NODE_RAW
#undef FIELD
#undef RAW
