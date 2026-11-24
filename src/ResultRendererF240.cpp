#include "FloatConstants.hpp"
#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "Graphics.hpp"
#include "TextureManagerF198.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "StaffTimeline438D00.hpp"
#include <d3d8.h>
#include <windows.h>
#include "Fighter.hpp"
#include "ResultScene.hpp"
#include "WindowOverlayF212.hpp"

// The native renderer/scene fields are borrowed physical views, not a
// declaration of complete original scene, actor or texture ownership.
class ResultSpriteDrawingF240 {
public:
};
// The observed native call to the accepted ScaleQuad callee transfers its
// float scale factors as three raw 32-bit IEEE754 values (MOV/PUSH). This
// borrowed call-only facade preserves that ABI; no original class identity
// or complete owner layout is asserted.
class ResultRawScaleF240 {
public: void ScaleQuad(float x,float y,float z,DWORD sxBits,DWORD syBits,DWORD szBits);
};
extern const float g_ResultAlphaOriginAt00658048;
extern const float g_ResultAlphaScaleAt00657864;
extern const float g_ResultFullAlphaMultiplierAt00657CF0;

#define DRAWER reinterpret_cast<ResultSpriteDrawingF240*>(textures)
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
#define RESULT_COLOR D3DCOLOR_ARGB(field018,255,255,255)
#define OFFSET_X(i) (static_cast<float>(offsets[i]+300))
#define PERCENT ((((field014) - g_ResultAlphaOriginAt00658048)/FloatConstants::ThreeFifths)*g_ResultAlphaScaleAt00657864)
void ResultScene::Render()
{
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quad;
        {
        RECT region;
        reinterpret_cast<TextureManagerF198*>(DRAWER)->SetDepthMode(0);
        reinterpret_cast<TextureManagerF198*>(DRAWER)->SetBlendMode(0);
        SetRect(&region,0,0,640,480);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawQuad(0,quad,&region,0xffffffff);
        reinterpret_cast<TextureManagerF198*>(DRAWER)->SetTextureFilter(2);
        SetRect(&region,0,0,640,480);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        TRANSFORM(quad)->RotateQuad(320.0f,240.0f,0.0f,PERCENT,PERCENT,PERCENT);
        reinterpret_cast<ResultRawScaleF240*>(&quad)->ScaleQuad(520.0f,360.0f,0.0f,reinterpret_cast<unsigned long&>(field014),reinterpret_cast<unsigned long&>(field014),reinterpret_cast<unsigned long&>(field014));
        g_WindowOverlayAt006714C4->DrawIfEnabled(quad,&region,D3DCOLOR_ARGB(static_cast<unsigned char>(g_ResultFullAlphaMultiplierAt00657CF0*field014),255,255,255));
        reinterpret_cast<TextureManagerF198*>(DRAWER)->SetTextureFilter(1);
        SetRect(&region,0,0,256,256);
        TRANSFORM(quad)->BuildQuadFromRect(&region);
        TRANSFORM(quad)->TranslateQuad(30.0f,30.0f,0.0f);
        reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawQuad(1,quad,&region,RESULT_COLOR);
        DrawDecimalDigits(OFFSET_X(0),70.0f,RESULT_COLOR,values[0],0,0);
        DrawDecimalDigits(OFFSET_X(1),94.0f,RESULT_COLOR,values[1],0,0);
        DrawDecimalDigits(OFFSET_X(2),118.0f,RESULT_COLOR,values[2],0,0);
        DrawDecimalDigits(OFFSET_X(3),142.0f,RESULT_COLOR,values[3],0,0);
        SetRect(&region,0,g_OptionsModeAt006714D0*32,160,g_OptionsModeAt006714D0*32+32);
        TRANSFORM(quad)->BuildQuad(156.0f,168.0f,316.0f,200.0f);
        TRANSFORM(quad)->TranslateQuad(static_cast<float>(offsets[4]),0.0f,0.0f);
        reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawQuad(2,quad,&region,RESULT_COLOR);
        DrawDecimalDigits(300.0f,221.0f,RESULT_COLOR,field038,1,0);
        DrawDecimalDigits(300.0f,245.0f,RESULT_COLOR,reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score,1,0);
        Graphics::EndFrame();
        }
    }
}
#undef PERCENT
#undef OFFSET_X
#undef RESULT_COLOR
#undef TRANSFORM
#undef DRAWER
