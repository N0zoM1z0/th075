#include <stdlib.h>
// Independently native-confirmed complete R065 3,232-CODE-byte battle character
// loader, plus both originally owned post-RET switch tables (11+5 case entries
// = 64 bytes DATA only). This is a natural VC7.1 game source reconstruction:
// all 11 original fighter ctor addresses and observed allocation sizes,
// four story/record modes, real virtual scalar deleting destructor at vtbl
// +0x14, genuine signed 8-byte selection tracker layout and original float/
// byte/short game fields are compared across the *entire* function.
// No complete private fighter class or constructor body is asserted.
// Fighter allocations are opaque *observed footprints*, not inferred layouts.
// The actual two-field SelectionTrackerF408 has both original useful values:
// low stack count first, upper stack seen bits second. Initialize seen first
// then count to reproduce real physical native EBP slots.
// All borrowed game methods have only their observed C++ caller ABI.
class FighterNativeF398 {
public:
 virtual void V00();virtual void V04();virtual void V08();virtual void V0C();virtual void V10();
 virtual ~FighterNativeF398();
 virtual void InitializeAction();
 virtual void V1C();virtual void V20();virtual void V24();virtual void V28();virtual void V2C();virtual void V30();virtual void V34();
 virtual void SelectVariant();
 virtual void ConfigureStory();
 void ResetControlState();
 void InitializeResources(void* controls);
 void SetOpponent(FighterNativeF398* other);
 void ActivateStoryStage();
};
#define FIGHTER(T) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+0))
class Fighter0F398 : public FighterNativeF398 {public:Fighter0F398(); private:unsigned char observedNativeAllocation[0x1000-sizeof(FighterNativeF398)];};
class Fighter1F398 : public FighterNativeF398 {public:Fighter1F398(); private:unsigned char observedNativeAllocation[0x1830-sizeof(FighterNativeF398)];};
class Fighter2F398 : public FighterNativeF398 {public:Fighter2F398(); private:unsigned char observedNativeAllocation[0x0FEC-sizeof(FighterNativeF398)];};
class Fighter3F398 : public FighterNativeF398 {public:Fighter3F398(); private:unsigned char observedNativeAllocation[0x0FEC-sizeof(FighterNativeF398)];};
class Fighter4F398 : public FighterNativeF398 {public:Fighter4F398(); private:unsigned char observedNativeAllocation[0x0FE8-sizeof(FighterNativeF398)];};
class Fighter5F398 : public FighterNativeF398 {public:Fighter5F398(); private:unsigned char observedNativeAllocation[0x0FF8-sizeof(FighterNativeF398)];};
class Fighter6F398 : public FighterNativeF398 {public:Fighter6F398(); private:unsigned char observedNativeAllocation[0x0FE4-sizeof(FighterNativeF398)];};
class Fighter7F398 : public FighterNativeF398 {public:Fighter7F398(); private:unsigned char observedNativeAllocation[0x0FE8-sizeof(FighterNativeF398)];};
class Fighter8F398 : public FighterNativeF398 {public:Fighter8F398(); private:unsigned char observedNativeAllocation[0x1008-sizeof(FighterNativeF398)];};
class Fighter9F398 : public FighterNativeF398 {public:Fighter9F398(); private:unsigned char observedNativeAllocation[0x1000-sizeof(FighterNativeF398)];};
class Fighter10F398: public FighterNativeF398 {public:Fighter10F398(); private:unsigned char observedNativeAllocation[0x1000-sizeof(FighterNativeF398)];};
extern FighterNativeF398* g_BattleFightersAt00671418[2];
extern signed char g_BattleCharactersAt006714C8[2];
extern signed char g_BattleSkinAt006714AC[2];
extern signed char g_BattleChosenLevelAt00671610[2];
extern signed char g_BattleSelectionFlagsAt006714CC[2];
extern signed char g_BattleLevelAt00671434[2];
extern signed char g_BattleSoundSettingAt00671438[2];
extern signed char g_BattleModeAt006714B4;
extern signed char g_ReplayModeAt0066C238;
extern signed char g_CharacterProgressAt0067161E;
extern signed char g_CharacterCountAt0067161F;
extern signed char g_RosterAt0067148F[];
extern signed char g_StoryRosterAt00671490[];
extern signed char g_StageSelectionAt0067161D;
extern signed char g_SelectedCharacterAt006714C9;
extern signed char g_PlayerDefaultAt006714C8;
extern signed char g_CpuDefaultAt006714C9;
extern signed char g_SelectedSkinAt006714AD;
extern signed char g_StoryFlagsAt006714D0;
extern signed char g_BattleDifficultyAt00671611;
extern signed char g_EnemyDifficultyAt006714CD;
extern signed char g_PlaySideAt006714B8;
extern signed char g_StoryChoiceAt00671620;
extern unsigned char g_StoryResultAt00671621;
extern unsigned char g_StoryStatusAt00671623;
extern unsigned char g_StoryCurrentAt00671622;
extern unsigned char g_StoryLoadingAt006714D1;
extern short g_StoryCounterAt006714C0;
extern int g_CumulativeScoreAt006714BC;
extern int g_StoryTransitionsAt0067160C;
extern unsigned int g_PlayerScoreAt006714B0;
extern unsigned int g_RankAt00671420;
extern short g_ReplayScoreAt0067189C;
extern unsigned int g_ReplayRoundAt006718A0;
extern const char g_LoadCharacterLogAt00657A30[];
extern const char g_LoadCharactersDoneAt00657A44[];
extern unsigned char g_StageParametersAt00671440[];
extern void BattleLogAt0041CC50(const char*);
extern void LoadReplaySelectionAt004195B0();
extern unsigned char CanChooseCharacterAt00419E10(signed char,int);
extern void CameraAttachAt00412660(float*,float*,float*,float*);

extern void SaveReplayStateAt00419920();
class EffectCollectionsF398 {public:void ClearEntries();};
extern EffectCollectionsF398 g_EffectCollectionsAt006716C8;
class GameProgressRecordsF398 {public:
 void SelectScore(signed char,signed char);
 void SaveSelectedCharacter(signed char);
 unsigned char* CurrentRecord();
 void WriteSelection();
 void SaveScoreFile();
};
extern GameProgressRecordsF398 g_ProgressAt006718F8;
#define F(T,f,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(f)+(o)))
namespace BattleCharacterLoaderF398 { void LoadCharacters(); }
void BattleCharacterLoaderF398::LoadCharacters() {
 BattleLogAt0041CC50(g_LoadCharacterLogAt00657A30);
 if (g_ReplayModeAt0066C238==2) LoadReplaySelectionAt004195B0();
 else if (g_BattleModeAt006714B4==4) {
   ++g_CharacterProgressAt0067161E;
   if (g_CharacterProgressAt0067161E==1) {
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
         if(CanChooseCharacterAt00419E10(selection,0)) {
            g_StoryRosterAt00671490[j]=selection;
            ++state.count;
         }
      }
      g_CharacterCountAt0067161F=static_cast<signed char>(state.count);
   }
   g_SelectedCharacterAt006714C9=g_RosterAt0067148F[g_CharacterProgressAt0067161E];
   g_StageSelectionAt0067161D=g_SelectedCharacterAt006714C9;
   if(g_SelectedCharacterAt006714C9<6) {
      g_StageSelectionAt0067161D+=((rand()<0x4000 || g_PlayerDefaultAt006714C8==6)?1:0)*10;
   }
   g_SelectedSkinAt006714AD=0;
   if(g_PlayerDefaultAt006714C8==g_SelectedCharacterAt006714C9)
      g_SelectedSkinAt006714AD=1-g_BattleSkinAt006714AC[0];
   g_BattleDifficultyAt00671611=static_cast<signed char>(rand()%3);
   g_EnemyDifficultyAt006714CD=static_cast<signed char>(rand()%3);
 }
 for(int side=0;side<2;++side) {
    if ((g_BattleModeAt006714B4!=3 && g_BattleModeAt006714B4!=4) || side!=0 || !g_BattleFightersAt00671418[side]) {
       if(g_BattleFightersAt00671418[side]) delete g_BattleFightersAt00671418[side];
       switch(g_BattleCharactersAt006714C8[side]) {
         case 0:g_BattleFightersAt00671418[side]=new Fighter0F398;break;
         case 1:g_BattleFightersAt00671418[side]=new Fighter1F398;break;
         case 2:g_BattleFightersAt00671418[side]=new Fighter2F398;break;
         case 3:g_BattleFightersAt00671418[side]=new Fighter3F398;break;
         case 4:g_BattleFightersAt00671418[side]=new Fighter4F398;break;
         case 5:g_BattleFightersAt00671418[side]=new Fighter5F398;break;
         case 6:g_BattleFightersAt00671418[side]=new Fighter6F398;break;
         case 7:g_BattleFightersAt00671418[side]=new Fighter7F398;break;
         case 8:g_BattleFightersAt00671418[side]=new Fighter8F398;break;
         case 9:g_BattleFightersAt00671418[side]=new Fighter9F398;break;
         case 10:g_BattleFightersAt00671418[side]=new Fighter10F398;break;
       }
       F(unsigned char,g_BattleFightersAt00671418[side],0x2CC)=static_cast<unsigned char>(side);
       F(unsigned char,g_BattleFightersAt00671418[side],0x2CE)=g_BattleSkinAt006714AC[side];
       F(short,g_BattleFightersAt00671418[side],0x398)=g_BattleChosenLevelAt00671610[side];
       F(short,g_BattleFightersAt00671418[side],0x39A)=g_BattleSelectionFlagsAt006714CC[side];
       g_BattleFightersAt00671418[side]->ResetControlState();
       g_BattleFightersAt00671418[side]->InitializeResources(g_StageParametersAt00671440+side*0x28);
       if (g_BattleModeAt006714B4==3 || (g_BattleModeAt006714B4==4 && side==1)) {
          F(float,g_BattleFightersAt00671418[side],0xA4)=1.0f;
          F(unsigned char,g_BattleFightersAt00671418[side],0x465)=static_cast<int>(g_StoryFlagsAt006714D0==0);
       } else {
          switch(g_BattleLevelAt00671434[side]) {
             case 0:F(float,g_BattleFightersAt00671418[side],0xA4)=0.5f;break;
             case 1:F(float,g_BattleFightersAt00671418[side],0xA4)=0.75f;break;
             case 2:F(float,g_BattleFightersAt00671418[side],0xA4)=1.0f;break;
             case 3:F(float,g_BattleFightersAt00671418[side],0xA4)=1.5f;break;
             case 4:F(float,g_BattleFightersAt00671418[side],0xA4)=2.0f;break;
          }
          F(unsigned char,g_BattleFightersAt00671418[side],0x465)=g_BattleSoundSettingAt00671438[side];
       }
    }
    if(side==0 && g_BattleModeAt006714B4==3) {
       if(g_ReplayModeAt0066C238!=2) {
          g_StoryResultAt00671621=0;
          if(g_StoryChoiceAt00671620!=0) {
             g_StoryResultAt00671621=1;
             g_StoryStatusAt00671623=0;
             g_StoryCurrentAt00671622=2;
             F(signed char,g_BattleFightersAt00671418[0],0x713)=g_StoryChoiceAt00671620;
             g_StoryChoiceAt00671620=0;
             F(int,g_BattleFightersAt00671418[0],0x2D0)=0;
             F(short,g_BattleFightersAt00671418[0],0x326)=10000;
             F(short,g_BattleFightersAt00671418[0],0x324)=10000;
          }
          g_CharacterProgressAt0067161E=F(signed char,g_BattleFightersAt00671418[0],0x713);
       }
       g_BattleFightersAt00671418[0]->SelectVariant();
       g_SelectedCharacterAt006714C9=F(signed char,g_BattleFightersAt00671418[0],0x6E5);
    }
    g_BattleFightersAt00671418[side]->InitializeAction();
 }
 if(g_BattleModeAt006714B4==5 || g_BattleModeAt006714B4==1 || g_BattleModeAt006714B4==3 || g_BattleModeAt006714B4==4) {
   if(g_PlaySideAt006714B8==0) {F(unsigned char,g_BattleFightersAt00671418[0],0x2CD)=0;F(unsigned char,g_BattleFightersAt00671418[1],0x2CD)=1;}
   else {F(unsigned char,g_BattleFightersAt00671418[0],0x2CD)=1;F(unsigned char,g_BattleFightersAt00671418[1],0x2CD)=0;}
 } else if (g_BattleModeAt006714B4==6) {
   F(unsigned char,g_BattleFightersAt00671418[0],0x2CD)=1;F(unsigned char,g_BattleFightersAt00671418[1],0x2CD)=1;
 } else {F(unsigned char,g_BattleFightersAt00671418[0],0x2CD)=0;F(unsigned char,g_BattleFightersAt00671418[1],0x2CD)=0;}
 g_BattleFightersAt00671418[0]->SetOpponent(g_BattleFightersAt00671418[1]);
 g_BattleFightersAt00671418[1]->SetOpponent(g_BattleFightersAt00671418[0]);
 CameraAttachAt00412660(&F(float,g_BattleFightersAt00671418[0],0x44),&F(float,g_BattleFightersAt00671418[0],0x48),&F(float,g_BattleFightersAt00671418[1],0x44),&F(float,g_BattleFightersAt00671418[1],0x48));
 if(g_BattleModeAt006714B4==3) {
   g_StoryLoadingAt006714D1=0;
   g_BattleFightersAt00671418[0]->ConfigureStory();
   g_BattleFightersAt00671418[0]->ActivateStoryStage();
   F(short,g_BattleFightersAt00671418[1],0x324)=F(short,g_BattleFightersAt00671418[1],0x33E+F(signed char,g_BattleFightersAt00671418[1],0x39D)*2);
   F(short,g_BattleFightersAt00671418[1],0x326)=F(short,g_BattleFightersAt00671418[1],0x324);
   if(g_CharacterProgressAt0067161E==1 || g_CharacterProgressAt0067161E>=8 || g_StoryResultAt00671621!=0) {
       if(g_StoryResultAt00671621!=0) g_StoryStatusAt00671623=0;
       else g_StoryStatusAt00671623=3;
       g_StoryCurrentAt00671622=2;
       g_ProgressAt006718F8.SelectScore(g_PlayerDefaultAt006714C8,g_StoryFlagsAt006714D0);
       F(int,g_BattleFightersAt00671418[0],0x2D0)=0;
       g_PlayerScoreAt006714B0=*reinterpret_cast<unsigned int*>(g_ProgressAt006718F8.CurrentRecord()+0x568);
       g_RankAt00671420=*reinterpret_cast<unsigned int*>(g_ProgressAt006718F8.CurrentRecord()+0x5F8);
       if(g_ReplayModeAt0066C238!=2) g_ProgressAt006718F8.WriteSelection();
       F(short,g_BattleFightersAt00671418[0],0x326)=10000;
       F(short,g_BattleFightersAt00671418[0],0x324)=10000;
   }
   g_StoryCounterAt006714C0=0;g_StoryTransitionsAt0067160C=0;g_CumulativeScoreAt006714BC=0;
   for(int k=1;k<=F(signed char,g_BattleFightersAt00671418[1],0x39D);++k)
     g_CumulativeScoreAt006714BC+=F(int,g_BattleFightersAt00671418[1],0x400+k*4);
   if(g_ReplayModeAt0066C238==2) {
     g_PlayerScoreAt006714B0=0;g_RankAt00671420=0;
     F(short,g_BattleFightersAt00671418[0],0x326)=g_ReplayScoreAt0067189C;
     F(short,g_BattleFightersAt00671418[0],0x324)=g_ReplayScoreAt0067189C;
     F(unsigned int,g_BattleFightersAt00671418[0],0x2D0)=g_ReplayRoundAt006718A0;
   } else {g_ProgressAt006718F8.SaveSelectedCharacter(g_CharacterProgressAt0067161E);g_ProgressAt006718F8.SaveScoreFile();}
 } else {
   F(int,g_BattleFightersAt00671418[0],0x2D0)=0;F(int,g_BattleFightersAt00671418[1],0x2D0)=0;
   g_PlayerScoreAt006714B0=0;g_RankAt00671420=0;g_StoryLoadingAt006714D1=0;
   F(short,g_BattleFightersAt00671418[0],0x326)=10000;F(short,g_BattleFightersAt00671418[0],0x324)=10000;
   F(short,g_BattleFightersAt00671418[1],0x326)=10000;F(short,g_BattleFightersAt00671418[1],0x324)=10000;
 }
 g_EffectCollectionsAt006716C8.ClearEntries();
 if(g_ReplayModeAt0066C238==1) SaveReplayStateAt00419920();
 BattleLogAt0041CC50(g_LoadCharactersDoneAt00657A44);
}
#undef F
