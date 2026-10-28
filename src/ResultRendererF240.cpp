#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "StaffTimeline438D00.hpp"
#include <d3d8.h>
#include <windows.h>

// The native renderer/scene fields are borrowed physical views, not a
// declaration of complete original scene, actor or texture ownership.
class ResultSceneRendererF240 {
    unsigned char nativePrefixAt0000[0x14];
public:
    float physicallyObservedAlphaAt0014;
    void RenderCounters();
    void DrawDecimalDigits(float x, float y, DWORD color, int value, int mode, int unused);
};
class ResultSpriteDrawingF240 {
public:
    void SetDepthMode(int mode);
    void SetBlendMode(int mode);
    void SetTextureFilter(int mode);
    void DrawQuad(int texture, const SpriteQuad40CA80&, const RECT*, DWORD color);
};
// The observed native call to the accepted ScaleQuad callee transfers its
// float scale factors as three raw 32-bit IEEE754 values (MOV/PUSH). This
// borrowed call-only facade preserves that ABI; no original class identity
// or complete owner layout is asserted.
class ResultRawScaleF240 {
public: void ScaleQuad(float x,float y,float z,DWORD sxBits,DWORD syBits,DWORD szBits);
};
class ResultFrameCaptureF240 {
public:
    void Draw(const SpriteQuad40CA80&, const RECT*, DWORD color);
};
extern ResultFrameCaptureF240* g_FrameCaptureAt006714C4;
extern void* g_ActorAt00671418;
extern signed char g_SelectionAt006714D0;
extern const float g_ResultAlphaOriginAt00658048;
extern const float g_ResultAlphaRangeAt00658058;
extern const float g_ResultAlphaScaleAt00657864;
extern const float g_ResultFullAlphaMultiplierAt00657CF0;

#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
#define DRAWER reinterpret_cast<ResultSpriteDrawingF240*>(FIELD(void*,8))
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
#define RESULT_COLOR D3DCOLOR_ARGB(FIELD(unsigned char,0x18),255,255,255)
#define VALUE(i) FIELD(int,0x1c+(i)*4)
#define OFFSET_X(i) (static_cast<float>(FIELD(short,0x42+(i)*2)+300))
#define PERCENT (((FIELD(float,0x14) - g_ResultAlphaOriginAt00658048)/g_ResultAlphaRangeAt00658058)*g_ResultAlphaScaleAt00657864)
void ResultSceneRendererF240::RenderCounters()
{
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 quad;
        {
        RECT region;
        DRAWER->SetDepthMode(0);
        DRAWER->SetBlendMode(0);
        SetRect(&region,0,0,640,480);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        DRAWER->DrawQuad(0,quad,&region,0xffffffff);
        DRAWER->SetTextureFilter(2);
        SetRect(&region,0,0,640,480);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        TRANSFORM(quad)->RotateQuad(320.0f,240.0f,0.0f,PERCENT,PERCENT,PERCENT);
        reinterpret_cast<ResultRawScaleF240*>(&quad)->ScaleQuad(520.0f,360.0f,0.0f,FIELD(DWORD,0x14),FIELD(DWORD,0x14),FIELD(DWORD,0x14));
        g_FrameCaptureAt006714C4->Draw(quad,&region,D3DCOLOR_ARGB(static_cast<unsigned char>(g_ResultFullAlphaMultiplierAt00657CF0*physicallyObservedAlphaAt0014),255,255,255));
        DRAWER->SetTextureFilter(1);
        SetRect(&region,0,0,256,256);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        TRANSFORM(quad)->TranslateQuad(30.0f,30.0f,0.0f);
        DRAWER->DrawQuad(1,quad,&region,RESULT_COLOR);
        DrawDecimalDigits(OFFSET_X(0),70.0f,RESULT_COLOR,VALUE(0),0,0);
        DrawDecimalDigits(OFFSET_X(1),94.0f,RESULT_COLOR,VALUE(1),0,0);
        DrawDecimalDigits(OFFSET_X(2),118.0f,RESULT_COLOR,VALUE(2),0,0);
        DrawDecimalDigits(OFFSET_X(3),142.0f,RESULT_COLOR,VALUE(3),0,0);
        SetRect(&region,0,g_SelectionAt006714D0*32,160,g_SelectionAt006714D0*32+32);
        TRANSFORM(quad)->BuildQuad(156.0f,168.0f,316.0f,200.0f);
        TRANSFORM(quad)->TranslateQuad(static_cast<float>(FIELD(short,0x4a)),0.0f,0.0f);
        DRAWER->DrawQuad(2,quad,&region,RESULT_COLOR);
        DrawDecimalDigits(300.0f,221.0f,RESULT_COLOR,FIELD(int,0x38),1,0);
        DrawDecimalDigits(300.0f,245.0f,RESULT_COLOR,*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(g_ActorAt00671418)+0x2d0),1,0);
        Graphics::EndFrame();
        }
    }
}
#undef PERCENT
#undef OFFSET_X
#undef VALUE
#undef RESULT_COLOR
#undef TRANSFORM
#undef DRAWER
#undef FIELD
