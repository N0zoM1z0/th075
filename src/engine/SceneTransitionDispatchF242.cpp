#include "config/DisplayOptions.hpp"
#include "engine/SceneTransition.hpp"
#include "engine/SceneTransitionLayers.hpp"
#include "engine/SceneBase.hpp"
#include <windows.h>
#include <d3d8.h>

unsigned short SceneBase::TranslateState(unsigned short command)
{
    if (g_TransitionFrame < 0) {
        if (!DisplayOptions::useRequestedTransitions && ((command & SceneTransition::OutMask)>0))
            command = (command & SceneTransition::KeepAfterOut) | SceneTransition::BlackOut;
        switch (command & SceneTransition::OutMask) {
        case SceneTransition::BlackOut:
        case 0x400:
        case 0x500:
        case 0x600:
        case 0x700:
            g_TransitionFrame = 10;
            Graphics::SetPresentCallback(DrawTransition00432360);
            Render();
            break;
        case SceneTransition::WhiteOut:
            g_TransitionFrame = 40;
            Graphics::SetPresentCallback(DrawTransition00432200);
            Render();
            break;
        case SceneTransition::TilesOut:
            g_TransitionFrame = 40;
            Graphics::SetPresentCallback(DrawTransition004324D0);
            Render();
            break;
        case SceneTransition::SkipOutAnimation:
            g_TransitionFrame = 0;
            break;
        case 0:
            if (!DisplayOptions::useRequestedTransitions && ((command & SceneTransition::InMask)>0))
                command = (command & SceneTransition::KeepBeforeIn) | SceneTransition::BlackIn;
            switch (command & SceneTransition::InMask) {
            case SceneTransition::BlackIn:
            case 0x6000:
                g_TransitionFrame = 10;
                Graphics::SetPresentCallback(DrawTransition00432410);
                Render();
                break;
            case SceneTransition::WhiteIn:
                g_TransitionFrame = 40;
                Graphics::SetPresentCallback(DrawTransition004322B0);
                Render();
                break;
            case SceneTransition::TilesIn:
                g_TransitionFrame = 40;
                Graphics::SetPresentCallback(DrawTransition00432660);
                Render();
                break;
            case SceneTransition::SkipInAnimation:
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
            if (command & SceneTransition::OutMask)
                return command & SceneTransition::KeepAfterOut;
            return command & SceneTransition::TargetMask;
        }
    }
    return command;
}
