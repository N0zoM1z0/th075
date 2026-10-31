// F914 complete native-shaped WinMain; still NONEXACT.
// Recovered original frame 0x278 and actual HWND/scene/path EBP slots
// by grouping only the actually used first-scene pointer.
// Native firstScene temp is -0x19C but source still uses -0x7C.
// F911: complete ordinary native-shaped WinMain; original 00602A60 NONEXACT.
// Native resource HWND is adjacent BEFORE currentScene/path, so encode
// their genuinely used C++ ownership as one group in original physical
// order without any fake filler members. This probe still has wrong
// native storage/lifetimes and must never count as a whole exact unit.
// F910: entire native-shaped original WinMain 00602A60 source-only.
// The verified original scene dispatch table emits case 4 BEFORE cases
// 0,1,2,3, despite numeric jump-table indexing. Preserve the original
// true C++ scene sizes and ctor identities; the whole function is NOT exact.
// F615: complete original-shaped but still NONEXACT TH075 authored
// WinMain/GameApplication startup source. Pinned Japanese original
// 00602A60 has 2,987 native CODE bytes/654 x86 plus 60 separately
// owned after-RET DATA bytes. This source baseline emits 2,981 CODE
// bytes/654 x86, with *wrong* physical EBP owners. No exact credit.
// F615 verifies actual useful C++ local/RAII source-layout controls;
// do not treat symbolic class names as historical source provenance.
#include <windows.h>
#include <mmsystem.h>
#include <objbase.h>
#include <string.h>
#include <stdlib.h>
// Exploratory complete WinMain original lifecycle: anchored to every
// original window/resource/scene native call and all 15 scene allocations.
// Only actually observed scene allocation footprints and interface calls.
class AppModeF455 {public:~AppModeF455();AppModeF455(int);void Release();};
class GraphicsClientF455 {public:~GraphicsClientF455();GraphicsClientF455();void Release();};
class InputClientF455 {public:~InputClientF455();InputClientF455();void Release();};
class SoundClientF455 {public:~SoundClientF455();SoundClientF455();void Release();};
class WindowResourceF455 {public:WindowResourceF455();void Release();};
class ArchiveCatalogF455 {public:ArchiveCatalogF455();~ArchiveCatalogF455();};
class GameDataResourcesF527 {public:GameDataResourcesF527();~GameDataResourcesF527();};
extern void __cdecl OpenArchiveFileAt0041CF80(const char*,const char*);
class ReplayGlobalF455 {public:void Initialize();void Finalize();};
class GameScenesF455 {public:virtual ~GameScenesF455();virtual unsigned short Advance();unsigned short TranslateState(unsigned short);};
struct NativeStartupScenePathF500 {HWND main; GameScenesF455* currentScene; char path[260]; GameScenesF455* firstConstructedScene; WNDCLASSEXA win; HANDLE readyEvent; char* directoryEnd; unsigned short sceneState; unsigned short previousState; };
#define DEF_SCENE(N,SIZE) class Scene##N##F455 : public GameScenesF455 { public:Scene##N##F455();private:unsigned char observedSize[(SIZE)-sizeof(GameScenesF455)];};
DEF_SCENE(0,0x11C)
DEF_SCENE(1,0x10)
DEF_SCENE(2,0x3C)
DEF_SCENE(3,0xF4)
DEF_SCENE(4,0x10)
DEF_SCENE(5,0x54)
DEF_SCENE(6,0x4C)
DEF_SCENE(7,0x120)
DEF_SCENE(8,0xC)
DEF_SCENE(9,0x1C)
DEF_SCENE(10,0x124)
DEF_SCENE(11,0x14)
DEF_SCENE(12,0x3E0)
DEF_SCENE(13,0x14)
DEF_SCENE(14,0x1D0)
#undef DEF_SCENE
extern const char g_AppWindowClassAt0065A104[];
extern const char g_AppWindowClassAltAt0065A17C[];
extern const char g_AppWindowTitleAt0065A148[];
extern const char g_AppIconAt0065A138[];
extern const char g_AppIconAt0065A140[];
extern const char g_ArchiveRootAt0065A1B0[];
extern const char g_LogPathAt0065A1C4[];
extern const char g_MainArchiveAt0065A1C0[];
extern const char g_MusicArchiveAt0065A1D0[];
extern const char g_SoundRootAt0065A1E4[];
extern const char g_DataBArchiveAt0065A1EC[];
extern const char g_DataBRootAt0065A1FC[];
extern const char g_LogStartAt0065A200[];
extern unsigned char g_AppWindowModeAt00671605;
extern unsigned char g_WindowGraphModeAt006714B5;
extern unsigned char g_WindowGraphAlphaAt006714A0;
extern unsigned char g_AppReadyAt0068D674;
extern HWND g_GameMainWindowAt00671608;
extern ReplayGlobalF455 g_ReplayGlobalAt006718F8;
extern void __cdecl StartTimersAt004239F0(int);
extern void __cdecl ResetStartupAt004407D70();
extern void __cdecl SceneResetAt00431F60();
extern unsigned short __cdecl SceneTranslateAt00431F60(unsigned short);
extern void __cdecl ContextStartAt00416B10();
extern void __cdecl ConfigureEventAt00423C80(HANDLE*);
extern void __cdecl InitializeArchivesAt0041CAE0();
extern void __cdecl OpenAppLogAt0041CC00(const char*);
extern void __cdecl AppLogAt0041CC50(const char*);
extern void __cdecl SetArchiveGlobalsAt00417210();
extern void __cdecl InitGraphicsAt00401110(HWND,int,int,int,unsigned char,unsigned char);
extern void __cdecl InitDirectInputAt00403D20(HWND,HINSTANCE);
extern void __cdecl InitDirectSoundAt004066E0(HWND);
extern void __cdecl InitJoystickAt00403EB0();
extern void __cdecl InitKeyboardAt00403D80();
extern void __cdecl ChangeScreenAt004018A0();
extern void __cdecl InitializeGameDataAt004175A0();
extern void __cdecl SaveCloseGameDataAt00417430();
extern void __cdecl InitializeSoundMenuAt00416B10();
extern void __cdecl EndSoundMenuAt004169E0();
extern void __cdecl ExitReportAt004407D70();
extern LRESULT CALLBACK NativeWinProcAt00603650(HWND,UINT,WPARAM,LPARAM);
extern const char g_ArchiveTh075At0065A1A8[];
extern const char g_ArchiveBgmAt0065A1D0[];
extern const char g_BgmRootAt0065A1D8[];
extern const char g_ArchiveTh075BAt0065A1E0[];
extern const char g_ArchiveDatabAt0065A1E8[];
extern const char g_LogFileAt0065A1F8[];
extern const char g_LogTextAt0065A208[];
extern const char g_LogOKAt0065A21C[];
extern const char g_DirectGraphicsTextAt0065A228[];
extern const char g_DirectInputTextAt0065A240[];
extern const char g_DirectSoundTextAt0065A258[];
extern const char g_JoystickTextAt0065A270[];
extern const char g_KeyboardTextAt0065A288[];
extern const char g_ChangeScreenTextAt0065A2A0[];
extern const char g_SystemDataTextAt0065A2B8[];
extern const char g_OpeningTextAt0065A2D0[];
static void NoopCompilerFunctionF455() { }
int WINAPI GameApplicationRunF455(HINSTANCE instance,HINSTANCE previous,LPSTR commandLine,int showCommand) {
          MSG msg;
    AppModeF455 appMode(16);
    NativeStartupScenePathF500 context;
    context.currentScene = 0;
    GraphicsClientF455 graphics;
    InputClientF455 input;
    SoundClientF455 sound;
    GetModuleFileNameA(0,context.path,260);
    context.directoryEnd=strrchr(context.path,'\\');
    context.directoryEnd[1]=0;
    SetCurrentDirectoryA(context.path);
    int windowWidth=GetSystemMetrics(45)+640+GetSystemMetrics(5)+GetSystemMetrics(7);
    int windowHeight=GetSystemMetrics(46)+480+GetSystemMetrics(6)+GetSystemMetrics(8)+GetSystemMetrics(4);
    context.win.cbSize=sizeof(WNDCLASSEXA);
    context.win.hInstance=instance;
    context.win.lpszClassName=g_AppWindowClassAt0065A104;
    context.win.lpfnWndProc=NativeWinProcAt00603650;
    context.win.style=0;
    context.win.hIcon=LoadIconA(instance,g_AppIconAt0065A138);
    context.win.hIconSm=LoadIconA(instance,g_AppIconAt0065A140);
    context.win.hCursor=LoadCursorA(0,MAKEINTRESOURCEA(32512));
    context.win.lpszMenuName=0;
    context.win.cbClsExtra=0;
    context.win.cbWndExtra=0;
    context.win.hbrBackground=(HBRUSH)GetStockObject(0);
    if(RegisterClassExA(&context.win)==0) { return 0; }
    {
      context.main=CreateWindowExA(0x40000,g_AppWindowClassAltAt0065A17C,g_AppWindowTitleAt0065A148,0xC80000,CW_USEDEFAULT,CW_USEDEFAULT,windowWidth,windowHeight,0,0,instance,0);
      if(!context.main) { return 0; }
    {
        ShowWindow(context.main,showCommand);
        UpdateWindow(context.main);
        srand(timeGetTime());
        if(FAILED(CoInitialize(0))) { return 0; }
    {
          while(!g_AppReadyAt0068D674) {}
          context.readyEvent=CreateEventA(0,FALSE,FALSE,0);
          ConfigureEventAt00423C80(&context.readyEvent);
          InitializeArchivesAt0041CAE0();
          ArchiveCatalogF455 catalog;
          OpenArchiveFileAt0041CF80(g_ArchiveTh075At0065A1A8,g_ArchiveRootAt0065A1B0);
          OpenArchiveFileAt0041CF80(g_ArchiveBgmAt0065A1D0,g_BgmRootAt0065A1D8);
          OpenArchiveFileAt0041CF80(g_ArchiveTh075BAt0065A1E0,g_ArchiveDatabAt0065A1E8);
          OpenAppLogAt0041CC00(g_LogFileAt0065A1F8);
          AppLogAt0041CC50(g_LogTextAt0065A208);
          GameDataResourcesF527 gameData;
          g_GameMainWindowAt00671608=context.main;
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          AppLogAt0041CC50(g_DirectGraphicsTextAt0065A228);
          InitGraphicsAt00401110(context.main,640,480,1,g_WindowGraphModeAt006714B5,g_WindowGraphAlphaAt006714A0);
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          AppLogAt0041CC50(g_DirectInputTextAt0065A240);
          InitDirectInputAt00403D20(context.main,instance);
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          AppLogAt0041CC50(g_DirectSoundTextAt0065A258);
          InitDirectSoundAt004066E0(context.main);
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          AppLogAt0041CC50(g_JoystickTextAt0065A270);
          InitJoystickAt00403EB0();
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          AppLogAt0041CC50(g_KeyboardTextAt0065A288);
          InitKeyboardAt00403D80();
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          if (g_AppWindowModeAt00671605) {
             Sleep(50);
             AppLogAt0041CC50(g_ChangeScreenTextAt0065A2A0);
             ChangeScreenAt004018A0();
             AppLogAt0041CC50(g_LogOKAt0065A21C);
          }
          AppLogAt0041CC50(g_SystemDataTextAt0065A2B8);
          InitializeGameDataAt004175A0();
          AppLogAt0041CC50(g_LogOKAt0065A21C);
          context.firstConstructedScene = new Scene4F455;
          context.currentScene = context.firstConstructedScene;
          context.sceneState=0x2004;
          context.sceneState=context.currentScene->TranslateState(context.sceneState);
          g_ReplayGlobalAt006718F8.Initialize();
          while(1) {
             if(PeekMessageA(&msg,0,0,0,PM_NOREMOVE)) {
                 if(GetMessageA(&msg,0,0,0)==0) break;
                 TranslateMessage(&msg);DispatchMessageA(&msg);
             } else {

              context.previousState=context.sceneState;
              if ((context.sceneState&0xFF00)>0) context.sceneState=context.currentScene->TranslateState(context.sceneState);
              else context.sceneState=context.currentScene->Advance();
              if(context.sceneState!=context.previousState && (context.sceneState&0xF00)==0 && (context.sceneState&0xF000)>0) {
                delete context.currentScene;
                switch(context.sceneState&0xFF) {
                  case 4: { Scene4F455* built = new Scene4F455; context.currentScene=built; } break;
                  case 0: { Scene0F455* built = new Scene0F455; context.currentScene=built; } break;
                  case 1: { Scene1F455* built = new Scene1F455; context.currentScene=built; } break;
                  case 2: { Scene2F455* built = new Scene2F455; context.currentScene=built; } break;
                  case 3: { Scene3F455* built = new Scene3F455; context.currentScene=built; } break;
                  case 5: { Scene5F455* built = new Scene5F455; context.currentScene=built; } break;
                  case 6: { Scene6F455* built = new Scene6F455; context.currentScene=built; } break;
                  case 7: { Scene7F455* built = new Scene7F455; context.currentScene=built; } break;
                  case 8: { Scene8F455* built = new Scene8F455; context.currentScene=built; } break;
                  case 9: { Scene9F455* built = new Scene9F455; context.currentScene=built; } break;
                  case 10: { Scene10F455* built = new Scene10F455; context.currentScene=built; } break;
                  case 11: { Scene11F455* built = new Scene11F455; context.currentScene=built; } break;
                  case 12: { Scene12F455* built = new Scene12F455; context.currentScene=built; } break;
                  case 13: { Scene13F455* built = new Scene13F455; context.currentScene=built; } break;
                  case 14: { Scene14F455* built = new Scene14F455; context.currentScene=built; } break;
                }
              }
              WaitForSingleObject(context.readyEvent,INFINITE);
             }
          }
          g_ReplayGlobalAt006718F8.Finalize();
          CloseHandle(context.readyEvent);
          context.readyEvent=0;
          if(context.currentScene) delete context.currentScene;
          CoUninitialize();
          // The game-data and archive owners destruct naturally in reverse
          // order on this successful exit, as the original PE shows.
          return 0;

        }
      }
    }
    return 0;
}
