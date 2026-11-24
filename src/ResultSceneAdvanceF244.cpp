#include "PlayerState.hpp"
#include "ReplaySegmentedQueueF219.hpp"
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
#include "SoundBank.hpp"
#include <windows.h>
#include "Fighter.hpp"
#include "ResultScene.hpp"
extern unsigned int g_ResultBestAt006714B0;
extern unsigned char g_ResultLeaveAt006714CE;
extern const double g_ResultFactor0At00658050;
extern const double g_ResultFactor1At00657D00;
extern const double g_ResultFactor2At00657D08;
extern const float g_ResultMinAlphaAt00658048;
extern const float g_ResultAlphaStepAt00658044;
namespace ResultPresentationF244 {
}
unsigned short ResultScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if ((field00C)==1) {
        if ((field040)<6) {
            offsets[4]=0;
            offsets[3]=0;
            offsets[2]=0;
            offsets[1]=0;
            offsets[0]=0;
            field038=values[0];
            field038=static_cast<int>((field038)*(field02C));
            field038=static_cast<int>((field038)*(field030));
            field038=static_cast<int>((field038)*(field034));
            switch (g_OptionsModeAt006714D0) {
            case 0: field038=static_cast<int>((field038)*g_ResultFactor0At00658050);break;
            case 1: field038=static_cast<int>((field038)*g_ResultFactor1At00657D00);break;
            case 2: field038=static_cast<int>((field038)*g_ResultFactor2At00657D08);break;
            case 3: field038=static_cast<int>((field038)*2.0);break;
            }
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score+=field038;
            field038=0;
            field040=7;
            field03C=400;
        } else if ((field040)==6) {
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score+=field038;
            field03C=400;
            field038=0;
            field040=7;
        } else {
            if (static_cast<unsigned int>(reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score)>g_ResultBestAt006714B0)
                g_ResultBestAt006714B0=reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score;
            if (g_ReplayModeAt0066C238==2 && g_StageAt0067161E>=g_ReplayRecords.fileHeader.recordCount) {
                MusicF204::PlayTrackByIndex(0x28);
                AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                return 0x2205;
            }
            if (g_StoryResultAt00671621) {
                MusicF204::PlayTrackByIndex(0x28);
                AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                g_ResultLeaveAt006714CE=0xff;
                return 0x2207;
            }
            if ((reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->field713)>=8) {
                if (g_ReplayModeAt0066C238==2) {
                    MusicF204::PlayTrackByIndex(0x28);
                    AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                    return 0x2205;
                }
                return 0x1108;
            }
            return 0x2301;
        }
    }
    if ((reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->field713)==10) {
        field014=1.0f;
    } else if ((field014)>g_ResultMinAlphaAt00658048) {
        field014=(field014)-g_ResultAlphaStepAt00658044;
    } else {
        field014=0.4f;
    }
    if ((field018)<255) {
        field018=(field018)+5;
    } else {
        field03C=(field03C)+1;
        if ((field040)<5 && (offsets[static_cast<int>(field040)])>0)
            offsets[static_cast<int>(field040)]=(offsets[static_cast<int>(field040)])-30;
    }
    switch (field03C) {
    case 30:
        field040=1;
        field038=(field038)+(values[0]);
        g_SoundBank->Play(0x2d);
        break;
    case 60:
        field040=2;
        field038=static_cast<int>((field038)*(field02C));
        g_SoundBank->Play(0x2d);
        break;
    case 90:
        field040=3;
        field038=static_cast<int>((field038)*(field030));
        g_SoundBank->Play(0x2d);
        break;
    case 120:
        field040=4;
        field038=static_cast<int>((field038)*(field034));
        g_SoundBank->Play(0x2d);
        break;
    case 180:
        field040=5;
        g_SoundBank->Play(0x28);
        switch (g_OptionsModeAt006714D0) {
        case 0: field038=static_cast<int>((field038)*g_ResultFactor0At00658050);break;
        case 1: field038=static_cast<int>((field038)*g_ResultFactor1At00657D00);break;
        case 2: field038=static_cast<int>((field038)*g_ResultFactor2At00657D08);break;
        case 3: field038=static_cast<int>((field038)*2.0);break;
        }
        break;
    case 300:
        field010=(field038)/600;
        if ((field010)<1234) field010=1234;
        field040=6;
        break;
    }
    if ((field040)==6) {
        if ((field038)>(field010)) {
            field038=(field038)-(field010);
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score+=field010;
            field019=((field019)+1)%3;
            if ((field019)==0)
                g_SoundBank->Play(0x31);
        } else {
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score+=field038;
            field038=0;
            field040=7;
        }
    }
    return 6;
}
