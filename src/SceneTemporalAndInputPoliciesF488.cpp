#include "LoadingLogoScenes.hpp"
#include "SequenceScenes.hpp"
#include "BattleResourceLoaders.hpp"
#include "GameSharedState.hpp"
#include "SelectionInput4388D0.hpp"
#include "Graphics.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
#include <windows.h>
#include <mmsystem.h>
unsigned short OpeningScene::Update(){
 PollInput(); Render(); Graphics::Present();
 if(g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1) return 0x2202;
 if(elapsed>0xC15C) return 0xFF02;
 elapsed=timeGetTime()-startTicks;
 return 0xD;
}
unsigned short LoadingScene::Update(){
 Render();
 if(!loaded){
   BattleCharacterLoaderF398::LoadCharacters();
   if(g_CombatMode==3 && g_StageAt0067161E>=8)
      return 0x1108;
   BattleStageLoaderF389::LoadStage();
   loaded=1;
 }
 return 0x2000;
}
unsigned short LogoScene::Update(){
 PollInput();Render();Graphics::Present();
 elapsedFrames++;
 if(elapsedFrames>180)return 0x220D;
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
