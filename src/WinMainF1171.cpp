#include "ReplayBrowserScene.hpp"
#include "NameEntryScenes.hpp"
#include "MusicRoomScene.hpp"
#include "LoadingLogoScenes.hpp"
#include "BattleEndScene.hpp"
#include "SequenceScenes.hpp"
#include "ResultListScene.hpp"
#include "OptionsScene.hpp"
#include "ResultScene.hpp"
#include "CharacterSelectScene.hpp"
#include "TitleScene.hpp"
#include "BattleScene.hpp"
#include "DisplayOptions.hpp"
// Complete original Japanese TH075 1.11 WinMain, 00602A60..0060360A.
// The 15-entry post-RET scene table is compared separately from CODE coverage.
// The const pointer reference materializes the genuinely used construction
// value before transfer to currentSceneOwner; it creates no named dummy local.
#include <windows.h>
#include <mmsystem.h>
#include <objbase.h>
#include <string.h>
#include <stdlib.h>
#include "DiagnosticLog.hpp"
#include "SceneBase.hpp"
#include "ArchiveCatalog.hpp"
#include "AudioControl.hpp"
#include "EventQueue.hpp"
#include "GameProgress.hpp"
#include "GraphicsDevice.hpp"
#include "GraphicsResourceClient.hpp"
#include "InputJoystick.hpp"
#include "MathLookup.hpp"
// Complete startup lifecycle: anchored to every
// original window/resource/scene native call and all 15 scene allocations.
// Only actually observed scene allocation footprints and interface calls.
namespace ArchiveCatalogF353 { void OpenAndRegister(const char*, const char*); }
typedef char ReplayBrowserSceneAllocationSize[(sizeof(ReplayBrowserScene) == 0x54) ? 1 : -1];
typedef char LoadingSceneAllocationSize[(sizeof(LoadingScene) == 0x10) ? 1 : -1];
typedef char LogoSceneAllocationSize[(sizeof(LogoScene) == 0x10) ? 1 : -1];
typedef char BattleEndSceneAllocationSize[(sizeof(BattleEndScene) == 0xC) ? 1 : -1];
typedef char StaffRollSceneAllocationSize[(sizeof(StaffRollScene) == 0x14) ? 1 : -1];
typedef char OpeningSceneAllocationSize[(sizeof(OpeningScene) == 0x14) ? 1 : -1];
typedef char SharedNameEntrySceneAllocationSize[(sizeof(SharedNameEntryScene) == 0x120) ? 1 : -1];
typedef char PlayerNameEntrySceneAllocationSize[(sizeof(PlayerNameEntryScene) == 0x124) ? 1 : -1];
typedef char MusicRoomSceneAllocationSize[(sizeof(MusicRoomScene) == 0x3E0) ? 1 : -1];
typedef char BattleSceneAllocationSize[(sizeof(BattleScene) == 0x11C) ? 1 : -1];
typedef char TitleSceneAllocationSize[(sizeof(TitleScene) == 0x3C) ? 1 : -1];
typedef char CharacterSelectSceneAllocationSize[(sizeof(CharacterSelectScene) == 0xF4) ? 1 : -1];
typedef char ResultSceneAllocationSize[(sizeof(ResultScene) == 0x4C) ? 1 : -1];
typedef char OptionsSceneAllocationSize[(sizeof(OptionsScene) == 0x1C) ? 1 : -1];
typedef char ResultListSceneAllocationSize[(sizeof(ResultListScene) == 0x1D0) ? 1 : -1];
// The window title is passed to the ANSI Win32 API in CP932.
#define TH075_WINDOW_TITLE \
    "\x93\x8c\x95\xfb\xe4\xc2\x96\xb2\x91\x7a" " " "\x81\x60" " Immaterial and Missing Power. ver1.11"
extern const char g_AppWindowClassAt0065A104[] = TH075_WINDOW_TITLE;
extern const char g_AppWindowClassAltAt0065A17C[] = TH075_WINDOW_TITLE;
extern const char g_AppWindowTitleAt0065A148[] = TH075_WINDOW_TITLE;
#undef TH075_WINDOW_TITLE
extern const char g_AppIconAt0065A138[] = "ICON1";
extern const char g_AppIconAt0065A140[] = "ICON1";
extern const char g_ArchiveRootAt0065A1B0[] = "data";
extern unsigned char g_AppInitializedAt0068D674;
extern HWND g_GameMainWindowAt00671608;
namespace SharedSound4066C0 { bool Initialize(HWND); }
namespace GameGlobalsF212 { void InitializeSound(); }
extern LRESULT CALLBACK AppWindowProcF468(HWND,UINT,WPARAM,LPARAM);
extern const char g_ArchiveTh075At0065A1B8[] = "th075.dat";
extern const char g_ArchiveBgmAt0065A1CC[] = "th075bgm.dat";
extern const char g_BgmRootAt0065A1C4[] = "sound";
extern const char g_ArchiveTh075BAt0065A1E4[] = "th075b.dat";
extern const char g_ArchiveDatabAt0065A1DC[] = "datab";
extern const char g_LogFileAt0065A1F0[] = "log.txt";
extern const char g_LogTextAt0065A1F8[] = "SystemDataCreate...\r\n";
extern const char g_LogOKAt0065A210[] = "...OK\r\n";
extern const char g_LogOKAt0065A230[] = "...OK\r\n";
extern const char g_LogOKAt0065A250[] = "...OK\r\n";
extern const char g_LogOKAt0065A270[] = "...OK\r\n";
extern const char g_LogOKAt0065A28C[] = "...OK\r\n";
extern const char g_LogOKAt0065A2A8[] = "...OK\r\n";
extern const char g_LogOKAt0065A2C8[] = "...OK\r\n";
extern const char g_LogOKAt0065A2E4[] = "...OK\r\n";
extern const char g_DirectGraphicsTextAt0065A218[] = "DirectGraphicsInit...\r\n";
extern const char g_DirectInputTextAt0065A238[] = "DirectInputInit...\r\n";
extern const char g_DirectSoundTextAt0065A258[] = "DirectSoundInit...\r\n";
extern const char g_JoystickTextAt0065A278[] = "JoystickInit...\r\n";
extern const char g_KeyboardTextAt0065A294[] = "KeyboardInit...\r\n";
extern const char g_ChangeScreenTextAt0065A2B0[] = "ChangeScreenMode...\r\n";
extern const char g_SystemDataTextAt0065A2D0[] = "SystemDataInit...\r\n";
int WINAPI GameApplicationRunF1171(HINSTANCE instance,HINSTANCE previous,LPSTR commandLine,int showCommand) {
    EventServiceF335 applicationMode(16);
    SceneBase* currentSceneOwner = 0;
    char path[260];
    WNDCLASSEXA winClass;
    unsigned short oldSceneState;
    GraphicsResourceClient renderContext;
    InputResourceClient inputContext;
    SharedSoundClient406610 sound;
    MSG msg;
    GetModuleFileNameA(0,path,260);
    char* directoryEnd=strrchr(path,'\\');
    directoryEnd[1]=0;
    SetCurrentDirectoryA(path);
    int width=GetSystemMetrics(45)+640+GetSystemMetrics(5)+GetSystemMetrics(7);
    int heightOfWindow=GetSystemMetrics(46)+480+GetSystemMetrics(6)+GetSystemMetrics(8)+GetSystemMetrics(4);
    winClass.cbSize=sizeof(WNDCLASSEXA);
    winClass.hInstance=instance;
    winClass.lpszClassName=g_AppWindowClassAt0065A104;
    winClass.lpfnWndProc=AppWindowProcF468;
    winClass.style=0;
    winClass.hIcon=LoadIconA(instance,g_AppIconAt0065A138);
    winClass.hIconSm=LoadIconA(instance,g_AppIconAt0065A140);
    winClass.hCursor=LoadCursorA(0,MAKEINTRESOURCEA(32512));
    winClass.lpszMenuName=0;
    winClass.cbClsExtra=0;
    winClass.cbWndExtra=0;
    winClass.hbrBackground=(HBRUSH)GetStockObject(0);
    if(RegisterClassExA(&winClass)==0) { return 0; }
    HWND hWndMain=CreateWindowExA(0x40000,g_AppWindowClassAltAt0065A17C,g_AppWindowTitleAt0065A148,0xC80000,CW_USEDEFAULT,CW_USEDEFAULT,width,heightOfWindow,0,0,instance,0);
    if(!hWndMain) { return 0; }
    ShowWindow(hWndMain,showCommand);
    UpdateWindow(hWndMain);
    srand(timeGetTime());
    if(FAILED(CoInitialize(0))) { return 0; }
    while(!g_AppInitializedAt0068D674) {}
    HANDLE eventReady=CreateEventA(0,FALSE,FALSE,0);
    EventQueueGuardF457::AppendUnique(&eventReady);
    MathLookup::BuildCosTable();
    ArchiveCatalog archiveOwner;
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveTh075At0065A1B8,g_ArchiveRootAt0065A1B0);
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveBgmAt0065A1CC,g_BgmRootAt0065A1C4);
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveTh075BAt0065A1E4,g_ArchiveDatabAt0065A1DC);
    DiagnosticLog::InitializeFile(g_LogFileAt0065A1F0);
    DiagnosticLog::AppendString(g_LogTextAt0065A1F8);
    GameDefaultsF193 gameSettings;
    g_GameMainWindowAt00671608=hWndMain;
    DiagnosticLog::AppendString(g_LogOKAt0065A210);
    DiagnosticLog::AppendString(g_DirectGraphicsTextAt0065A218);
    Graphics::Initialize(hWndMain,640,480,true,DisplayOptions::squareTextures,DisplayOptions::use16BitBackBuffer);
    DiagnosticLog::AppendString(g_LogOKAt0065A230);
    DiagnosticLog::AppendString(g_DirectInputTextAt0065A238);
    Input::Initialize(hWndMain,instance);
    DiagnosticLog::AppendString(g_LogOKAt0065A250);
    DiagnosticLog::AppendString(g_DirectSoundTextAt0065A258);
    SharedSound4066C0::Initialize(hWndMain);
    DiagnosticLog::AppendString(g_LogOKAt0065A270);
    DiagnosticLog::AppendString(g_JoystickTextAt0065A278);
    Input::InitializeJoysticks();
    DiagnosticLog::AppendString(g_LogOKAt0065A28C);
    DiagnosticLog::AppendString(g_KeyboardTextAt0065A294);
    Input::CreateKeyboard();
    DiagnosticLog::AppendString(g_LogOKAt0065A2A8);
    if (DisplayOptions::startFullscreen) {
        Sleep(50);
        DiagnosticLog::AppendString(g_ChangeScreenTextAt0065A2B0);
        Graphics::ToggleWindowMode();
        DiagnosticLog::AppendString(g_LogOKAt0065A2C8);
    }
    DiagnosticLog::AppendString(g_SystemDataTextAt0065A2D0);
    GameGlobalsF212::InitializeSound();
    DiagnosticLog::AppendString(g_LogOKAt0065A2E4);
    currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new LogoScene));
    unsigned short activeSceneState=0x2004;
    activeSceneState=currentSceneOwner->TranslateState(activeSceneState);
    g_GameProgress.LoadScoreFile();
    while(1) {
        if(PeekMessageA(&msg,0,0,0,PM_NOREMOVE)) {
            if(GetMessageA(&msg,0,0,0)==0) break;
            TranslateMessage(&msg);DispatchMessageA(&msg);
        } else {
            oldSceneState=activeSceneState;
            if ((activeSceneState&0xFF00)>0) activeSceneState=currentSceneOwner->TranslateState(activeSceneState);
            else activeSceneState=currentSceneOwner->Update();
            if(activeSceneState!=oldSceneState && (activeSceneState&0xF00)==0 && (activeSceneState&0xF000)>0) {
                delete currentSceneOwner;
                switch(activeSceneState&0xFF) {
                case 4: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new LogoScene)); } break;
                case 0: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new BattleScene)); } break;
                case 1: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new LoadingScene)); } break;
                case 2: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new TitleScene)); } break;
                case 3: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new CharacterSelectScene)); } break;
                case 5: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new ReplayBrowserScene)); } break;
                case 6: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new ResultScene)); } break;
                case 7: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new SharedNameEntryScene)); } break;
                case 8: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new BattleEndScene)); } break;
                case 9: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new OptionsScene)); } break;
                case 10: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new PlayerNameEntryScene)); } break;
                case 11: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new StaffRollScene)); } break;
                case 12: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new MusicRoomScene)); } break;
                case 13: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new OpeningScene)); } break;
                case 14: { currentSceneOwner=static_cast<SceneBase* const&>(static_cast<SceneBase*>(new ResultListScene)); } break;
                }
            }
            WaitForSingleObject(eventReady,INFINITE);
        }
    }
    g_GameProgress.SaveScoreFile();
    CloseHandle(eventReady);
    eventReady=0;
    if(currentSceneOwner) delete currentSceneOwner;
    CoUninitialize();
    // The game-data and archive owners destruct naturally in reverse
    // order on this successful exit, as the original PE shows.
    return 0;
}
