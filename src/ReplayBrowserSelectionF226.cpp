#include <string.h>
// Borrowed physical interfaces. Original scene, list and item layouts remain
// unproved; none of these interfaces creates/embeds an original owner object.
class ReplayNameListF226 {
public:
    unsigned int Size();
    char** Entry(int index);
};
struct ReplayItemF226 {
    unsigned char unknownBeforeAvailability[13];
    signed char available;
    signed char variantCount;
};
class ReplayItemsF226 {
public:
    ReplayItemF226* Entry(int index);
};
class SoundDeviceF226 {
public:
    void Play(int soundId);
};
extern SoundDeviceF226* g_SoundAt00671618;
extern unsigned char g_ReplayModeAt0066C238;
extern unsigned short g_SelectedReplayVariantAt006714A4;
extern char g_ReplayPathAt00671754[];
namespace BrowserSceneStepsF226 {
    void PollInputs();
    void ResetInputState();
    void BeginSelectedReplay(int x, int y, int flag, int mode);
}
class ReplayBrowserF226 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short UpdateSelection();
    void ReadInput();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define NAME_LIST (*reinterpret_cast<ReplayNameListF226*>(reinterpret_cast<unsigned char*>(this)+0x0c))
#define ITEMS (*reinterpret_cast<ReplayItemsF226*>(reinterpret_cast<unsigned char*>(this)+0x20))
#define PLAY(sound) g_SoundAt00671618->Play(sound)
#define TRANSITION() { \
  strcpy(g_ReplayPathAt00671754, *NAME_LIST.Entry(FIELD(short,0x48))); \
  BrowserSceneStepsF226::BeginSelectedReplay(-10000,-60,1,0); \
}
unsigned short ReplayBrowserF226::UpdateSelection()
{
    ReadInput();
    DrawCurrent();
    BrowserSceneStepsF226::ResetInputState();
    if (FIELD(signed char,0x51) == 0) {
        if (FIELD(signed char,0x4e) < 0) {
            PLAY(0x27);
            --FIELD(short,0x48);
            if (FIELD(short,0x48) < 0)
                FIELD(short,0x48) = 0;
        }
        if (FIELD(signed char,0x4e) > 0) {
            PLAY(0x27);
            ++FIELD(short,0x48);
            if (FIELD(short,0x48) >= static_cast<int>(NAME_LIST.Size()))
                FIELD(short,0x48) = NAME_LIST.Size() - 1;
        }
        if (FIELD(signed char,0x4d) < 0) {
            PLAY(0x27);
            FIELD(short,0x48) = FIELD(short,0x48) - 10;
            if (FIELD(short,0x48) < 0)
                FIELD(short,0x48) = 0;
        }
        if (FIELD(signed char,0x4d) > 0) {
            PLAY(0x27);
            FIELD(short,0x48) = FIELD(short,0x48) + 10;
            if (FIELD(short,0x48) >= static_cast<int>(NAME_LIST.Size()))
                FIELD(short,0x48) = NAME_LIST.Size() - 1;
        }
    } else {
        if (FIELD(signed char,0x4e) < 0) {
            PLAY(0x27);
            --FIELD(short,0x4a);
            if (FIELD(short,0x4a) < 0)
                FIELD(short,0x4a) = ITEMS.Entry(FIELD(short,0x48))->variantCount - 1;
        }
        if (FIELD(signed char,0x4e) > 0) {
            PLAY(0x27);
            ++FIELD(short,0x4a);
            if (FIELD(short,0x4a) >= static_cast<int>(ITEMS.Entry(FIELD(short,0x48))->variantCount))
                FIELD(short,0x4a) = 0;
        }
    }
    if (FIELD(unsigned char,0x4c) < 255)
        FIELD(unsigned char,0x4c) = FIELD(unsigned char,0x4c) + 25;
    if (FIELD(signed char,0x4f) == 1 && NAME_LIST.Size() > 0) {
        if (ITEMS.Entry(FIELD(short,0x48))->available > 0) {
            PLAY(0x2d);
            if (FIELD(signed char,0x51) == 0) {
                if (ITEMS.Entry(FIELD(short,0x48))->variantCount > 1) {
                    FIELD(signed char,0x51) = 1;
                    FIELD(short,0x4a) = 0;
                } else {
                    g_SelectedReplayVariantAt006714A4 = 1;
                    g_ReplayModeAt0066C238 = 2;
                    TRANSITION();
                    return 0x2201;
                }
            } else {
                g_SelectedReplayVariantAt006714A4 = FIELD(short,0x4a) + 1;
                g_ReplayModeAt0066C238 = 2;
                TRANSITION();
                return 0x2201;
            }
        } else {
            PLAY(0x2d);
            g_ReplayModeAt0066C238 = 2;
            TRANSITION();
            return 0x2201;
        }
    }
    if (FIELD(signed char,0x50) == 1) {
        if (FIELD(signed char,0x51) == 1) {
            PLAY(0x28);
            FIELD(signed char,0x51) = 0;
        } else {
            PLAY(0x28);
            return 0x2202;
        }
    }
    return 5;
}
#undef TRANSITION
#undef PLAY
#undef ITEMS
#undef NAME_LIST
#undef FIELD
