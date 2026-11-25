#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "battle/BattleResultState.hpp"
#include "battle/PlayerState.hpp"
#include "replay/ReplayRecords.hpp"
#include "config/GameConfigStorage.hpp"
#include "battle/BattleSessionState.hpp"
#include "battle/BattleResourceLoaders.hpp"
#include "engine/GameSharedState.hpp"
#include "platform/DiagnosticLog.hpp"
#include "engine/GameProgress.hpp"
#include "engine/GameSnapshot.hpp"
#include <stdlib.h>
#include "battle/CameraInputs412660.hpp"
#include "characters/ReimuFighter.hpp"
#include "characters/MarisaFighter.hpp"
#include "characters/SakuyaFighter.hpp"
#include "characters/AliceFighter.hpp"
#include "characters/PatchouliFighter.hpp"
#include "characters/YoumuFighter.hpp"
#include "characters/RemiliaFighter.hpp"
#include "characters/YuyukoFighter.hpp"
#include "characters/YukariFighter.hpp"
#include "characters/SuikaFighter.hpp"
#include "characters/MeilingFighter.hpp"
#include "battle/CombatEffects.hpp"

typedef char ReimuFighterAllocationSize[sizeof(ReimuFighter) == 0x1000 ? 1 : -1];
typedef char MarisaFighterAllocationSize[sizeof(MarisaFighter) == 0x1830 ? 1 : -1];
typedef char SakuyaFighterAllocationSize[sizeof(SakuyaFighter) == 0xFEC ? 1 : -1];
typedef char AliceFighterAllocationSize[sizeof(AliceFighter) == 0xFEC ? 1 : -1];
typedef char PatchouliFighterAllocationSize[sizeof(PatchouliFighter) == 0xFE8 ? 1 : -1];
typedef char YoumuFighterAllocationSize[sizeof(YoumuFighter) == 0xFF8 ? 1 : -1];
typedef char RemiliaFighterAllocationSize[sizeof(RemiliaFighter) == 0xFE4 ? 1 : -1];
typedef char YuyukoFighterAllocationSize[sizeof(YuyukoFighter) == 0xFE8 ? 1 : -1];
typedef char YukariFighterAllocationSize[sizeof(YukariFighter) == 0x1008 ? 1 : -1];
typedef char SuikaFighterAllocationSize[sizeof(SuikaFighter) == 0x1000 ? 1 : -1];
typedef char MeilingFighterAllocationSize[sizeof(MeilingFighter) == 0x1000 ? 1 : -1];

signed char g_StoryRosterAt00671490[10];
extern const char g_LoadCharacterLogAt00657A30[] = "LoadCharacter...\r\n";
extern const char g_LoadCharactersDoneAt00657A44[] = "...OK\r\n";

void BattleCharacterLoaderF398::LoadCharacters() {
 DiagnosticLog::AppendString(g_LoadCharacterLogAt00657A30);
 if (g_ReplayModeAt0066C238==ReplayMode::Playback) GameStateF202::RestoreFromSnapshot();
 else if (g_CombatMode==CombatMode::Arcade) {
   ++g_StageAt0067161E;
   if (g_StageAt0067161E==1) {
      struct SelectionTrackerF408 {int count; unsigned int seen;};
      SelectionTrackerF408 state;
      state.seen=0;
      state.count=0;
      for(int j=0;j<10;++j) {
         signed char selection=static_cast<signed char>(j);
         if(j<6) {
            selection=static_cast<signed char>(rand()%6);
            while((1 << selection & state.seen)!=0) selection=static_cast<signed char>(rand()%6);
            state.seen |= 1 << selection;
         }
         if(GameProgressF203::CheckSelection(selection,0)) {
            g_StoryRosterAt00671490[j]=selection;
            ++state.count;
         }
      }
      g_CharacterCountAt0067161F=static_cast<signed char>(state.count);
   }
   g_PlayerIdAt006714C8[1]=g_StoryRosterAt00671490[g_StageAt0067161E - 1];
   g_StageSelectionAt0067161D=g_PlayerIdAt006714C8[1];
   if(g_StageSelectionAt0067161D<6) {
      g_StageSelectionAt0067161D+=((rand()<0x4000 || g_PlayerIdAt006714C8[0]==6)?1:0)*10;
   }
   g_PlayerRoundAt006714AC[1]=0;
   if(g_PlayerIdAt006714C8[0]==g_PlayerIdAt006714C8[1])
      g_PlayerRoundAt006714AC[1]=1-g_PlayerRoundAt006714AC[0];
   g_PlayerAltAt00671610[1]=static_cast<signed char>(rand()%3);
   g_PlayerOtherAt006714CC[1]=static_cast<signed char>(rand()%3);
 }
 for(int side=0;side<2;++side) {
    if ((g_CombatMode!=CombatMode::Story && g_CombatMode!=CombatMode::Arcade) || side!=0 || !g_BattleFightersAt00671418[side]) {
       if(g_BattleFightersAt00671418[side]) delete g_BattleFightersAt00671418[side];
       switch(g_PlayerIdAt006714C8[side]) {
         case 0:g_BattleFightersAt00671418[side]=new ReimuFighter;break;
         case 1:g_BattleFightersAt00671418[side]=new MarisaFighter;break;
         case 2:g_BattleFightersAt00671418[side]=new SakuyaFighter;break;
         case 3:g_BattleFightersAt00671418[side]=new AliceFighter;break;
         case 4:g_BattleFightersAt00671418[side]=new PatchouliFighter;break;
         case 5:g_BattleFightersAt00671418[side]=new YoumuFighter;break;
         case 6:g_BattleFightersAt00671418[side]=new RemiliaFighter;break;
         case 7:g_BattleFightersAt00671418[side]=new YuyukoFighter;break;
         case 8:g_BattleFightersAt00671418[side]=new YukariFighter;break;
         case 9:g_BattleFightersAt00671418[side]=new SuikaFighter;break;
         case 10:g_BattleFightersAt00671418[side]=new MeilingFighter;break;
       }
       g_BattleFightersAt00671418[side]->playerSide=static_cast<signed char>(side);
       g_BattleFightersAt00671418[side]->paletteIndex=g_PlayerRoundAt006714AC[side];
       g_BattleFightersAt00671418[side]->selectedSpellCards[0]=g_PlayerAltAt00671610[side];
       g_BattleFightersAt00671418[side]->selectedSpellCards[1]=g_PlayerOtherAt006714CC[side];
       g_BattleFightersAt00671418[side]->LoadResources();
       g_BattleFightersAt00671418[side]->SetBindings(&g_PlayerKeyBindings[side]);
       if (g_CombatMode==CombatMode::Story || (g_CombatMode==CombatMode::Arcade && side==1)) {
          g_BattleFightersAt00671418[side]->field0A4=1.0f;
          g_BattleFightersAt00671418[side]->autoGuard=static_cast<int>(g_OptionsModeAt006714D0==0);
       } else {
          switch(g_PlayerSettingsAt00671434[side]) {
             case 0:g_BattleFightersAt00671418[side]->field0A4=0.5f;break;
             case 1:g_BattleFightersAt00671418[side]->field0A4=0.75f;break;
             case 2:g_BattleFightersAt00671418[side]->field0A4=1.0f;break;
             case 3:g_BattleFightersAt00671418[side]->field0A4=1.5f;break;
             case 4:g_BattleFightersAt00671418[side]->field0A4=2.0f;break;
          }
          g_BattleFightersAt00671418[side]->autoGuard=g_PlayerDifficultyAt00671438[side];
       }
    }
    if(side==0 && g_CombatMode==CombatMode::Story) {
       if(g_ReplayModeAt0066C238!=ReplayMode::Playback) {
          g_StoryResultAt00671621=0;
          if(g_StoryChoiceAt00671620!=0) {
             g_StoryResultAt00671621=1;
             g_ContinueCountAt00671623=0;
             g_SequenceCounterAt00671622=2;
             g_BattleFightersAt00671418[0]->field713=g_StoryChoiceAt00671620;
             g_StoryChoiceAt00671620=0;
             g_BattleFightersAt00671418[0]->score=0;
             g_BattleFightersAt00671418[0]->recoverableHealth=10000;
             g_BattleFightersAt00671418[0]->health=10000;
          }
          g_StageAt0067161E=g_BattleFightersAt00671418[0]->field713;
       }
       g_BattleFightersAt00671418[0]->SelectVariant();
       g_PlayerIdAt006714C8[1]=static_cast<signed char>(g_BattleFightersAt00671418[0]->field6E5);
    }
    g_BattleFightersAt00671418[side]->ResetRound();
 }
 if(g_CombatMode==CombatMode::Practice || g_CombatMode==CombatMode::DuelCpu || g_CombatMode==CombatMode::Story || g_CombatMode==CombatMode::Arcade) {
   if(g_SelectedSideAt006714B8==0) {g_BattleFightersAt00671418[0]->cpuControlled=0;g_BattleFightersAt00671418[1]->cpuControlled=1;}
   else {g_BattleFightersAt00671418[0]->cpuControlled=1;g_BattleFightersAt00671418[1]->cpuControlled=0;}
 } else if (g_CombatMode==CombatMode::Attract) {
   g_BattleFightersAt00671418[0]->cpuControlled=1;g_BattleFightersAt00671418[1]->cpuControlled=1;
 } else {g_BattleFightersAt00671418[0]->cpuControlled=0;g_BattleFightersAt00671418[1]->cpuControlled=0;}
 g_BattleFightersAt00671418[0]->BindOpponent(g_BattleFightersAt00671418[1]);
 g_BattleFightersAt00671418[1]->BindOpponent(g_BattleFightersAt00671418[0]);
 CameraInputs412660::Initialize(&g_BattleFightersAt00671418[0]->x,&g_BattleFightersAt00671418[0]->y,&g_BattleFightersAt00671418[1]->x,&g_BattleFightersAt00671418[1]->y);
 if(g_CombatMode==CombatMode::Story) {
   g_StateFadeAlpha=0;
   g_BattleFightersAt00671418[0]->ConfigureStage();
   g_BattleFightersAt00671418[0]->LoadStageResource();
   g_BattleFightersAt00671418[1]->health=g_BattleFightersAt00671418[1]->healthLimits[g_BattleFightersAt00671418[1]->field39D];
   g_BattleFightersAt00671418[1]->recoverableHealth=g_BattleFightersAt00671418[1]->health;
   if(g_StageAt0067161E==1 || g_StageAt0067161E>=8 || g_StoryResultAt00671621!=0) {
       if(g_StoryResultAt00671621!=0) g_ContinueCountAt00671623=0;
       else g_ContinueCountAt00671623=3;
       g_SequenceCounterAt00671622=2;
       g_GameProgress.SetSelection(g_PlayerIdAt006714C8[0],g_OptionsModeAt006714D0);
       g_BattleFightersAt00671418[0]->score=0;
       g_MaxCombatScore=g_GameProgress.GetSelectedDifficultyRecord()->scores[0].score;
       g_StateScoreThreshold=g_GameProgress.GetSelectedDifficultyRecord()->scores[9].score;
       if(g_ReplayModeAt0066C238!=ReplayMode::Playback) g_GameProgress.RecordStoryAttempt();
       g_BattleFightersAt00671418[0]->recoverableHealth=10000;
       g_BattleFightersAt00671418[0]->health=10000;
   }
   g_MaxComboCount=0;g_ResultScoreTotalAt0067160C=0;g_CumulativeScoreAt006714BC=0;
   for(int k=1;k<=g_BattleFightersAt00671418[1]->field39D;++k)
     g_CumulativeScoreAt006714BC+=g_BattleFightersAt00671418[1]->field400[k];
   if(g_ReplayModeAt0066C238==ReplayMode::Playback) {
     g_MaxCombatScore=0;g_StateScoreThreshold=0;
     g_BattleFightersAt00671418[0]->recoverableHealth=g_ReplayRecords.recordHeader.startingHealth;
     g_BattleFightersAt00671418[0]->health=g_ReplayRecords.recordHeader.startingHealth;
     g_BattleFightersAt00671418[0]->score=g_ReplayRecords.recordHeader.startingScore;
   } else {g_GameProgress.UpdateHighestStoryStage(g_StageAt0067161E);g_GameProgress.SaveScoreFile();}
 } else {
   g_BattleFightersAt00671418[0]->score=0;g_BattleFightersAt00671418[1]->score=0;
   g_MaxCombatScore=0;g_StateScoreThreshold=0;g_StateFadeAlpha=0;
   g_BattleFightersAt00671418[0]->recoverableHealth=10000;g_BattleFightersAt00671418[0]->health=10000;
   g_BattleFightersAt00671418[1]->recoverableHealth=10000;g_BattleFightersAt00671418[1]->health=10000;
 }
 g_CombatEffects.ReleaseEntries();
 if(g_ReplayModeAt0066C238==ReplayMode::Recording) GameStateF201::SaveSnapshot();
 DiagnosticLog::AppendString(g_LoadCharactersDoneAt00657A44);
}
