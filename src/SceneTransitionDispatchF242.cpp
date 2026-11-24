#include "SceneTransitionLayers.hpp"
#include "SceneBase.hpp"
#include <windows.h>
#include <d3d8.h>

extern unsigned char g_SettingsByteAt006714D2;
unsigned short SceneBase::TranslateState(unsigned short mode)
{
    if (g_TransitionFrame < 0) {
        if (!g_SettingsByteAt006714D2 && ((mode & 0xf00)>0))
            mode = (mode & 0xf0ff) | 0x200;
        switch (mode & 0xf00) {
        case 0x200:
        case 0x400:
        case 0x500:
        case 0x600:
        case 0x700:
            g_TransitionFrame = 10;
            Graphics::SetPresentCallback(DrawTransition00432360);
            Render();
            break;
        case 0x100:
            g_TransitionFrame = 40;
            Graphics::SetPresentCallback(DrawTransition00432200);
            Render();
            break;
        case 0x300:
            g_TransitionFrame = 40;
            Graphics::SetPresentCallback(DrawTransition004324D0);
            Render();
            break;
        case 0xf00:
            g_TransitionFrame = 0;
            break;
        case 0:
            if (!g_SettingsByteAt006714D2 && ((mode & 0xf000)>0))
                mode = (mode & 0x0fff) | 0x2000;
            switch (mode & 0xf000) {
            case 0x2000:
            case 0x6000:
                g_TransitionFrame = 10;
                Graphics::SetPresentCallback(DrawTransition00432410);
                Render();
                break;
            case 0x1000:
                g_TransitionFrame = 40;
                Graphics::SetPresentCallback(DrawTransition004322B0);
                Render();
                break;
            case 0x3000:
                g_TransitionFrame = 40;
                Graphics::SetPresentCallback(DrawTransition00432660);
                Render();
                break;
            case 0xf000:
                g_TransitionFrame = 0;
                break;
            }
            break;
        }
    } else {
        Render();
        Graphics::Present();
        --g_TransitionFrame;
        if (g_TransitionFrame < 0) {
            Graphics::SetPresentCallback(0);
            if (mode & 0xf00)
                return mode & 0xf0ff;
            return mode & 0xff;
        }
    }
    return mode;
}
