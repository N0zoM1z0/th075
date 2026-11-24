#include "DisplayOptions.hpp"
// Complete original Japanese TH075 1.11 WinMain, 00602A60..0060360A.
// The 15-entry post-RET scene table is compared separately from CODE coverage.
// Scene names are provisional. Their complete allocation carriers use the
// independently observed 15 new extents and native 8-byte scene-base boundary.
// observedSize is actual allocated private storage, not frame padding or a
// claim that its still-opaque private field meanings have been recovered.
// Never reuse these carriers as another callable's private semantic layout.
// The const pointer reference materializes the genuinely used construction
// value before transfer to currentSceneOwner; it creates no named dummy local.
#include <windows.h>
#include <mmsystem.h>
#include <objbase.h>
#include <string.h>
#include <stdlib.h>
#include "DiagnosticLog.hpp"
#include "EventQueue.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
#include "MathLookup.hpp"
// Complete startup lifecycle: anchored to every
// original window/resource/scene native call and all 15 scene allocations.
// Only actually observed scene allocation footprints and interface calls.
class AppModeF1171 {public:~AppModeF1171();AppModeF1171(int);};
class GraphicsClientF1171 {public:~GraphicsClientF1171();GraphicsClientF1171();};
class InputClientF1171 {public:~InputClientF1171();InputClientF1171();};
class SoundClientF1171 {public:~SoundClientF1171();SoundClientF1171();};
class ArchiveCatalogF1171 {public:ArchiveCatalogF1171();~ArchiveCatalogF1171();};
class GameDataResourcesF1171 {public:GameDataResourcesF1171();~GameDataResourcesF1171();};
namespace ArchiveCatalogF353 { void OpenAndRegister(const char*, const char*); }
class ReplayGlobalF1171 {public:void Initialize();void Finalize();};
class SceneCountLifetimeF1171 {public:SceneCountLifetimeF1171();~SceneCountLifetimeF1171();};
class GameScenesF1171 {SceneCountLifetimeF1171 sceneCount;public:virtual ~GameScenesF1171();virtual unsigned short Advance();unsigned short TranslateState(unsigned short);};
#define DEF_SCENE(N,SIZE) class Scene##N##F1171 : public GameScenesF1171 { public:Scene##N##F1171();private:unsigned char observedSize[(SIZE)-sizeof(GameScenesF1171)];};
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
extern unsigned char g_AppInitializedAt0068D674;
extern HWND g_GameMainWindowAt00671608;
extern ReplayGlobalF1171 g_ReplayGlobalAt006718F8;
namespace SharedSound4066C0 { bool Initialize(HWND); }
namespace GameGlobalsF212 { void InitializeSound(); }
extern LRESULT CALLBACK AppWindowProcF468(HWND,UINT,WPARAM,LPARAM);
extern const char g_ArchiveTh075At0065A1B8[];
extern const char g_ArchiveBgmAt0065A1CC[];
extern const char g_BgmRootAt0065A1C4[];
extern const char g_ArchiveTh075BAt0065A1E4[];
extern const char g_ArchiveDatabAt0065A1DC[];
extern const char g_LogFileAt0065A1F0[];
extern const char g_LogTextAt0065A1F8[];
extern const char g_LogOKAt0065A210[];
extern const char g_LogOKAt0065A230[];
extern const char g_LogOKAt0065A250[];
extern const char g_LogOKAt0065A270[];
extern const char g_LogOKAt0065A28C[];
extern const char g_LogOKAt0065A2A8[];
extern const char g_LogOKAt0065A2C8[];
extern const char g_LogOKAt0065A2E4[];
extern const char g_DirectGraphicsTextAt0065A218[];
extern const char g_DirectInputTextAt0065A238[];
extern const char g_DirectSoundTextAt0065A258[];
extern const char g_JoystickTextAt0065A278[];
extern const char g_KeyboardTextAt0065A294[];
extern const char g_ChangeScreenTextAt0065A2B0[];
extern const char g_SystemDataTextAt0065A2D0[];
int WINAPI GameApplicationRunF1171(HINSTANCE instance,HINSTANCE previous,LPSTR commandLine,int showCommand) {
    AppModeF1171 applicationMode(16);
    GameScenesF1171* currentSceneOwner = 0;
    char path[260];
    WNDCLASSEXA winClass;
    unsigned short oldSceneState;
    GraphicsClientF1171 renderContext;
    InputClientF1171 inputContext;
    SoundClientF1171 sound;
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
    ArchiveCatalogF1171 archiveOwner;
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveTh075At0065A1B8,g_ArchiveRootAt0065A1B0);
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveBgmAt0065A1CC,g_BgmRootAt0065A1C4);
    ArchiveCatalogF353::OpenAndRegister(g_ArchiveTh075BAt0065A1E4,g_ArchiveDatabAt0065A1DC);
    DiagnosticLog::InitializeFile(g_LogFileAt0065A1F0);
    DiagnosticLog::AppendString(g_LogTextAt0065A1F8);
    GameDataResourcesF1171 gameSettings;
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
    currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene4F1171);
    unsigned short activeSceneState=0x2004;
    activeSceneState=currentSceneOwner->TranslateState(activeSceneState);
    g_ReplayGlobalAt006718F8.Initialize();
    while(1) {
        if(PeekMessageA(&msg,0,0,0,PM_NOREMOVE)) {
            if(GetMessageA(&msg,0,0,0)==0) break;
            TranslateMessage(&msg);DispatchMessageA(&msg);
        } else {
            oldSceneState=activeSceneState;
            if ((activeSceneState&0xFF00)>0) activeSceneState=currentSceneOwner->TranslateState(activeSceneState);
            else activeSceneState=currentSceneOwner->Advance();
            if(activeSceneState!=oldSceneState && (activeSceneState&0xF00)==0 && (activeSceneState&0xF000)>0) {
                delete currentSceneOwner;
                switch(activeSceneState&0xFF) {
                case 4: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene4F1171); } break;
                case 0: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene0F1171); } break;
                case 1: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene1F1171); } break;
                case 2: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene2F1171); } break;
                case 3: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene3F1171); } break;
                case 5: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene5F1171); } break;
                case 6: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene6F1171); } break;
                case 7: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene7F1171); } break;
                case 8: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene8F1171); } break;
                case 9: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene9F1171); } break;
                case 10: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene10F1171); } break;
                case 11: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene11F1171); } break;
                case 12: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene12F1171); } break;
                case 13: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene13F1171); } break;
                case 14: { currentSceneOwner=static_cast<GameScenesF1171* const&>(new Scene14F1171); } break;
                }
            }
            WaitForSingleObject(eventReady,INFINITE);
        }
    }
    g_ReplayGlobalAt006718F8.Finalize();
    CloseHandle(eventReady);
    eventReady=0;
    if(currentSceneOwner) delete currentSceneOwner;
    CoUninitialize();
    // The game-data and archive owners destruct naturally in reverse
    // order on this successful exit, as the original PE shows.
    return 0;
}
