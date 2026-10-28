#include <windows.h>
#include <mmsystem.h>
// Five independently full original scene state and input-policy functions.
// Native sign-extension on global loading mode 006714B4 and exact
// original 32-bit/16-bit elapsed-frame counters are preserved.
// Three complete native scene update policies and two independent original
// game-scene input paths. These own only borrowed native base call ABIs.
extern unsigned int g_OpeningPhaseAt0067166C;
extern unsigned int g_OpeningAlternateAt006716B4;
extern signed char g_LoadModeAt006714B4;
extern signed char g_LoadCharacterAt0067161E;
extern void __cdecl NativeGraphicsBeforeAt004028F0();
extern void __cdecl LoadFightersAt004176F0();
extern void __cdecl LoadStageAt004183D0();
class SceneAdvanceBaseF488 {
public:virtual void F0();virtual void F1();virtual void VAdvance();
};
class OpeningSceneAdvanceF488:public SceneAdvanceBaseF488 {
public:
 unsigned short Advance();void PollInput();
};
class LoadingSceneAdvanceF488:public SceneAdvanceBaseF488 {
public:unsigned short Advance();
};
class TimedSceneAdvanceF488:public SceneAdvanceBaseF488 {
public:unsigned short Advance();void PollInput();
};
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
unsigned short OpeningSceneAdvanceF488::Advance(){
 PollInput(); VAdvance(); NativeGraphicsBeforeAt004028F0();
 if(g_OpeningPhaseAt0067166C==1 || g_OpeningAlternateAt006716B4==1) return 0x2202;
 if(FIELD(unsigned int,0xC)>0xC15C) return 0xFF02;
 FIELD(unsigned int,0xC)=timeGetTime()-FIELD(unsigned int,0x10);
 return 0xD;
}
unsigned short LoadingSceneAdvanceF488::Advance(){
 VAdvance();
 if(!FIELD(unsigned char,0xC)){
   LoadFightersAt004176F0();
   if(g_LoadModeAt006714B4==3 && g_LoadCharacterAt0067161E>=8)
      return 0x1108;
   LoadStageAt004183D0();
   FIELD(unsigned char,0xC)=1;
 }
 return 0x2000;
}
unsigned short TimedSceneAdvanceF488::Advance(){
 PollInput();VAdvance();NativeGraphicsBeforeAt004028F0();
 FIELD(unsigned short,0xC)++;
 if(FIELD(unsigned short,0xC)>180)return 0x220D;
 return 4;
}
extern void __cdecl JoystickTickAt00403E50();
extern void __cdecl KeyboardTickAt00403F40();
extern void __cdecl FullscreenToggleAt004018A0();
class InputStateF488 {public:void Advance();unsigned char CheckPressed(int);};
extern InputStateF488 g_FirstInputAt00671638;
class LoadingSceneInputF488 {public:void PollInput();};
class StaffRollSceneInputF488 {public:void PollSkipInput();};
void LoadingSceneInputF488::PollInput(){
 JoystickTickAt00403E50();KeyboardTickAt00403F40();
 g_FirstInputAt00671638.Advance();
 if(g_FirstInputAt00671638.CheckPressed(0x1C) && (g_FirstInputAt00671638.CheckPressed(0x38) || g_FirstInputAt00671638.CheckPressed(0xB8)))
   FullscreenToggleAt004018A0();
}
void StaffRollSceneInputF488::PollSkipInput(){
 JoystickTickAt00403E50();KeyboardTickAt00403F40();
 g_FirstInputAt00671638.Advance();
 if(g_FirstInputAt00671638.CheckPressed(0x1C) && (g_FirstInputAt00671638.CheckPressed(0x38) || g_FirstInputAt00671638.CheckPressed(0xB8)))
   FullscreenToggleAt004018A0();
}
#undef FIELD
