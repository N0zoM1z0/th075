#include <windows.h>
#include <d3d8.h>

// Borrow only the observed scene virtual call slots. No scene is embedded.
class TransitionDispatcherF242 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short DispatchMode(unsigned short mode);
};
typedef void (__cdecl *TransitionCallbackF242)(IDirect3DTexture8**);
namespace ScenePresentationF242 {
    void Present();
    void SetCallback(TransitionCallbackF242 callback);
}
extern void __cdecl RenderTransition100F242(IDirect3DTexture8**);
extern void __cdecl RenderTransition300F242(IDirect3DTexture8**);
extern void __cdecl RenderTransitionGroupF242(IDirect3DTexture8**);
extern void __cdecl RenderTransition1000F242(IDirect3DTexture8**);
extern void __cdecl RenderTransition2000F242(IDirect3DTexture8**);
extern void __cdecl RenderTransition3000F242(IDirect3DTexture8**);
extern int g_TransitionCountAt0066C240;
extern unsigned char g_TransitionRemapAt006714D2;
unsigned short TransitionDispatcherF242::DispatchMode(unsigned short mode)
{
    if (g_TransitionCountAt0066C240 < 0) {
        if (!g_TransitionRemapAt006714D2 && ((mode & 0xf00)>0))
            mode = (mode & 0xf0ff) | 0x200;
        switch (mode & 0xf00) {
        case 0x200:
        case 0x400:
        case 0x500:
        case 0x600:
        case 0x700:
            g_TransitionCountAt0066C240 = 10;
            ScenePresentationF242::SetCallback(RenderTransitionGroupF242);
            DrawCurrent();
            break;
        case 0x100:
            g_TransitionCountAt0066C240 = 40;
            ScenePresentationF242::SetCallback(RenderTransition100F242);
            DrawCurrent();
            break;
        case 0x300:
            g_TransitionCountAt0066C240 = 40;
            ScenePresentationF242::SetCallback(RenderTransition300F242);
            DrawCurrent();
            break;
        case 0xf00:
            g_TransitionCountAt0066C240 = 0;
            break;
        case 0:
            if (!g_TransitionRemapAt006714D2 && ((mode & 0xf000)>0))
                mode = (mode & 0x0fff) | 0x2000;
            switch (mode & 0xf000) {
            case 0x2000:
            case 0x6000:
                g_TransitionCountAt0066C240 = 10;
                ScenePresentationF242::SetCallback(RenderTransition2000F242);
                DrawCurrent();
                break;
            case 0x1000:
                g_TransitionCountAt0066C240 = 40;
                ScenePresentationF242::SetCallback(RenderTransition1000F242);
                DrawCurrent();
                break;
            case 0x3000:
                g_TransitionCountAt0066C240 = 40;
                ScenePresentationF242::SetCallback(RenderTransition3000F242);
                DrawCurrent();
                break;
            case 0xf000:
                g_TransitionCountAt0066C240 = 0;
                break;
            }
            break;
        }
    } else {
        DrawCurrent();
        ScenePresentationF242::Present();
        --g_TransitionCountAt0066C240;
        if (g_TransitionCountAt0066C240 < 0) {
            ScenePresentationF242::SetCallback(0);
            if (mode & 0xf00)
                return mode & 0xf0ff;
            return mode & 0xff;
        }
    }
    return mode;
}
