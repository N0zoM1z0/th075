#include "ui/BattleEndScene.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/Fighter.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/GraphicsDraw.hpp"
#include "graphics/TextOverlay.hpp"
#include <windows.h>
// Independently exact entire native R053 scene draw. Original borrowed
// overlay helper 00412EB0 has zero arguments; a made-up mode argument
// added a nonnative PUSH and changed complete code length by two bytes.
// Complete native R053 battle-end drawing sequence, original fighter actor
// render modes, 18th virtual call and 640x480 alpha-tinted screen overlay.
#define ACTOR g_BattleFightersAt00671418[0]
#define ACTOR_DRAWER static_cast<TextureManagerF198*>(ACTOR->drawing)
void BattleEndScene::Render() {
    if(Graphics::BeginFrame()) {
        ACTOR_DRAWER->SetDepthMode(0);
        ACTOR_DRAWER->SetBlendMode(0);
        ACTOR->RenderStage(g_StageAt0067161E);
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
