#include "engine/SceneTransition.hpp"
#include "input/InputControl.hpp"
#include "battle/CombatMode.hpp"
#include "ui/LoadingLogoScenes.hpp"
#include "engine/SequenceScenes.hpp"
#include "battle/BattleResourceLoaders.hpp"
#include "engine/GameSharedState.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "input/InputJoystick.hpp"
#include <windows.h>
#include <mmsystem.h>
unsigned short OpeningScene::Update(){
 PollInput(); Render(); Graphics::Present();
 if(g_InputMappings[0].held.counts[InputControl::ButtonA]==1 || g_InputMappings[1].held.counts[InputControl::ButtonA]==1) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
 if(elapsed>0xC15C) return SceneTransition::SkipInAnimation | SceneTransition::SkipOutAnimation | SceneId::Title;
 elapsed=timeGetTime()-startTicks;
 return 0xD;
}
unsigned short LoadingScene::Update(){
 Render();
 if(!loaded){
   BattleCharacterLoaderF398::LoadCharacters();
   if(g_CombatMode==CombatMode::Story && g_StageAt0067161E>=8)
      return SceneTransition::WhiteIn | SceneTransition::WhiteOut | SceneId::BattleEnding;
   BattleStageLoaderF389::LoadStage();
   loaded=1;
 }
 return SceneTransition::BlackIn | SceneId::Battle;
}
unsigned short LogoScene::Update(){
 PollInput();Render();Graphics::Present();
 elapsedFrames++;
 if(elapsedFrames>180)return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Opening;
 return 4;
}
void LogoScene::PollInput(){
 Input::PollKeyboard();Input::PollJoysticks();
 g_InputMappings[0].UpdateHeldCounts();
 if(g_InputMappings[0].IsKeyDown(0x1C) && (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8)))
   Graphics::ToggleWindowMode();
}
void StaffRollScene::PollSkipInput(){
 Input::PollKeyboard();Input::PollJoysticks();
 g_InputMappings[0].UpdateHeldCounts();
 if(g_InputMappings[0].IsKeyDown(0x1C) && (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8)))
   Graphics::ToggleWindowMode();
}
