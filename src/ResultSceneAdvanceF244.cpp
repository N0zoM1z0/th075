#include <windows.h>
// Borrowed only the observed virtual slots and physically read byte fields.
// No complete native actor or result-scene layout is claimed or instantiated.
class ResultSceneAdvanceF244 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short Advance();
    void PollInput();
};
class ResultSoundF244 {public: void Play(int id);};
extern ResultSoundF244* g_ResultSoundAt00671618;
extern void* g_ResultActorAt00671418;
extern unsigned int g_ResultBestAt006714B0;
extern signed char g_ResultModeAt0066C238;
extern signed char g_ResultFocusAt006714D0;
extern signed char g_ResultFrameAt0067161E;
extern signed char g_ResultThresholdAt00671866;
extern unsigned char g_ResultContinueAt00671621;
extern unsigned char g_ResultLeaveAt006714CE;
extern const double g_ResultFactor0At00658050;
extern const double g_ResultFactor1At00657D00;
extern const double g_ResultFactor2At00657D08;
extern const float g_ResultMinAlphaAt00658048;
extern const float g_ResultAlphaStepAt00658044;
namespace ResultPresentationF244 {
    void Present();
    void MusicCue(int id);
    void ChangeScene(int x,int y,int one,int mode);
}
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,offset) (*reinterpret_cast<type*>(RAW+(offset)))
#define ACTOR(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(g_ResultActorAt00671418)+(offset)))
unsigned short ResultSceneAdvanceF244::Advance()
{
    PollInput();
    DrawCurrent();
    ResultPresentationF244::Present();
    if (FIELD(signed char,0x0c)==1) {
        if (FIELD(signed char,0x40)<6) {
            FIELD(short,0x4a)=0;
            FIELD(short,0x48)=0;
            FIELD(short,0x46)=0;
            FIELD(short,0x44)=0;
            FIELD(short,0x42)=0;
            FIELD(int,0x38)=FIELD(int,0x1c);
            FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x2c));
            FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x30));
            FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x34));
            switch (g_ResultFocusAt006714D0) {
            case 0: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor0At00658050);break;
            case 1: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor1At00657D00);break;
            case 2: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor2At00657D08);break;
            case 3: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*2.0);break;
            }
            ACTOR(int,0x2d0)+=FIELD(int,0x38);
            FIELD(int,0x38)=0;
            FIELD(signed char,0x40)=7;
            FIELD(int,0x3c)=400;
        } else if (FIELD(signed char,0x40)==6) {
            ACTOR(int,0x2d0)+=FIELD(int,0x38);
            FIELD(int,0x3c)=400;
            FIELD(int,0x38)=0;
            FIELD(signed char,0x40)=7;
        } else {
            if (static_cast<unsigned int>(ACTOR(int,0x2d0))>g_ResultBestAt006714B0)
                g_ResultBestAt006714B0=ACTOR(int,0x2d0);
            if (g_ResultModeAt0066C238==2 && g_ResultFrameAt0067161E>=g_ResultThresholdAt00671866) {
                ResultPresentationF244::MusicCue(0x28);
                ResultPresentationF244::ChangeScene(-10000,-160,1,1);
                return 0x2205;
            }
            if (g_ResultContinueAt00671621) {
                ResultPresentationF244::MusicCue(0x28);
                ResultPresentationF244::ChangeScene(-10000,-160,1,1);
                g_ResultLeaveAt006714CE=0xff;
                return 0x2207;
            }
            if (ACTOR(signed char,0x713)>=8) {
                if (g_ResultModeAt0066C238==2) {
                    ResultPresentationF244::MusicCue(0x28);
                    ResultPresentationF244::ChangeScene(-10000,-160,1,1);
                    return 0x2205;
                }
                return 0x1108;
            }
            return 0x2301;
        }
    }
    if (ACTOR(signed char,0x713)==10) {
        FIELD(float,0x14)=1.0f;
    } else if (FIELD(float,0x14)>g_ResultMinAlphaAt00658048) {
        FIELD(float,0x14)=FIELD(float,0x14)-g_ResultAlphaStepAt00658044;
    } else {
        FIELD(float,0x14)=0.4f;
    }
    if (FIELD(unsigned char,0x18)<255) {
        FIELD(unsigned char,0x18)=FIELD(unsigned char,0x18)+5;
    } else {
        FIELD(int,0x3c)=FIELD(int,0x3c)+1;
        if (FIELD(signed char,0x40)<5 && FIELD(short,0x42+static_cast<int>(FIELD(signed char,0x40))*2)>0)
            FIELD(short,0x42+static_cast<int>(FIELD(signed char,0x40))*2)=FIELD(short,0x42+static_cast<int>(FIELD(signed char,0x40))*2)-30;
    }
    switch (FIELD(int,0x3c)) {
    case 30:
        FIELD(signed char,0x40)=1;
        FIELD(int,0x38)=FIELD(int,0x38)+FIELD(int,0x1c);
        g_ResultSoundAt00671618->Play(0x2d);
        break;
    case 60:
        FIELD(signed char,0x40)=2;
        FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x2c));
        g_ResultSoundAt00671618->Play(0x2d);
        break;
    case 90:
        FIELD(signed char,0x40)=3;
        FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x30));
        g_ResultSoundAt00671618->Play(0x2d);
        break;
    case 120:
        FIELD(signed char,0x40)=4;
        FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*FIELD(float,0x34));
        g_ResultSoundAt00671618->Play(0x2d);
        break;
    case 180:
        FIELD(signed char,0x40)=5;
        g_ResultSoundAt00671618->Play(0x28);
        switch (g_ResultFocusAt006714D0) {
        case 0: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor0At00658050);break;
        case 1: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor1At00657D00);break;
        case 2: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*g_ResultFactor2At00657D08);break;
        case 3: FIELD(int,0x38)=static_cast<int>(FIELD(int,0x38)*2.0);break;
        }
        break;
    case 300:
        FIELD(int,0x10)=FIELD(int,0x38)/600;
        if (FIELD(int,0x10)<1234) FIELD(int,0x10)=1234;
        FIELD(signed char,0x40)=6;
        break;
    }
    if (FIELD(signed char,0x40)==6) {
        if (FIELD(int,0x38)>FIELD(int,0x10)) {
            FIELD(int,0x38)=FIELD(int,0x38)-FIELD(int,0x10);
            ACTOR(int,0x2d0)+=FIELD(int,0x10);
            FIELD(signed char,0x19)=(FIELD(signed char,0x19)+1)%3;
            if (FIELD(signed char,0x19)==0)
                g_ResultSoundAt00671618->Play(0x31);
        } else {
            ACTOR(int,0x2d0)+=FIELD(int,0x38);
            FIELD(int,0x38)=0;
            FIELD(signed char,0x40)=7;
        }
    }
    return 6;
}
#undef ACTOR
#undef FIELD
#undef RAW
