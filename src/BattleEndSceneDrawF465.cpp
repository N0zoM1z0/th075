#include "GameSharedState.hpp"
#include "TextureManagerF198.hpp"
#include "Fighter.hpp"
#include "Graphics.hpp"
#include "GraphicsDraw.hpp"
#include "TextOverlay.hpp"
#include <windows.h>
// Independently exact entire native R053 scene draw. Original borrowed
// overlay helper 00412EB0 has zero arguments; a made-up mode argument
// added a nonnative PUSH and changed complete code length by two bytes.
// Complete native R053 battle-end drawing sequence, original fighter actor
// render modes, 18th virtual call and 640x480 alpha-tinted screen overlay.
class BattleActorF464 {
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void DrawCharacter(unsigned char);
};
extern BattleActorF464* g_BattleEndActorAt00671418;
class BattleEndDrawF464 {public:void Draw();};
#define ACTOR reinterpret_cast<Fighter*>(g_BattleEndActorAt00671418)
#define ACTOR_DRAWER static_cast<TextureManagerF198*>(ACTOR->drawing)
void BattleEndDrawF464::Draw() {
    if(Graphics::BeginFrame()) {
        ACTOR_DRAWER->SetDepthMode(0);
        ACTOR_DRAWER->SetBlendMode(0);
        g_BattleEndActorAt00671418->DrawCharacter(g_StageAt0067161E);
        if(ACTOR->noticeEnabled)
            g_TextRenderer->DrawBox();
        if (g_StateFadeAlpha>0) {
            RECT region;
            SetRect(&region,0,0,640,480);
            Graphics::DrawFilledRectangle(&region, (static_cast<unsigned int>(g_StateFadeAlpha)<<24) | static_cast<unsigned int>(g_StateResetCounter));
        }
        Graphics::EndFrame();
    }
}
#undef ACTOR
#undef ACTOR_DRAWER
