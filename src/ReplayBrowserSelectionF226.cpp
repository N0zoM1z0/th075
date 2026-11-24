#include "AudioControl.hpp"
#include "Graphics.hpp"
#include "SoundBank.hpp"
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
extern unsigned char g_ReplayModeAt0066C238;
extern unsigned short g_SelectedReplayVariantAt006714A4;
extern char g_ReplayPathAt00671754[];
namespace BrowserSceneStepsF226 {
    void PollInputs();
}
class ReplayBrowserF226 {
public:
    virtual void SlotZero();
    virtual void SlotOne();
    virtual void DrawCurrent();
    unsigned short UpdateSelection();
    void ReadInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x048 - 0x004];
    short field048;
    short field04A;
    unsigned char field04C;
    signed char field04D;
    signed char field04E;
    signed char field04F;
    signed char field050;
    signed char field051;
};
#define NAME_LIST (*reinterpret_cast<ReplayNameListF226*>(reinterpret_cast<unsigned char*>(this)+0x0c))
#define ITEMS (*reinterpret_cast<ReplayItemsF226*>(reinterpret_cast<unsigned char*>(this)+0x20))
#define PLAY(sound) g_SoundBank->Play(sound)
#define TRANSITION() { \
  strcpy(g_ReplayPathAt00671754, *NAME_LIST.Entry(field048)); \
  AudioControl407CA0::ScheduleFade(-10000,-60,1,0); \
}
unsigned short ReplayBrowserF226::UpdateSelection()
{
    ReadInput();
    DrawCurrent();
    Graphics::Present();
    if (field051 == 0) {
        if (field04E < 0) {
            PLAY(0x27);
            --field048;
            if (field048 < 0)
                field048 = 0;
        }
        if (field04E > 0) {
            PLAY(0x27);
            ++field048;
            if (field048 >= static_cast<int>(NAME_LIST.Size()))
                field048 = NAME_LIST.Size() - 1;
        }
        if (field04D < 0) {
            PLAY(0x27);
            field048 = field048 - 10;
            if (field048 < 0)
                field048 = 0;
        }
        if (field04D > 0) {
            PLAY(0x27);
            field048 = field048 + 10;
            if (field048 >= static_cast<int>(NAME_LIST.Size()))
                field048 = NAME_LIST.Size() - 1;
        }
    } else {
        if (field04E < 0) {
            PLAY(0x27);
            --field04A;
            if (field04A < 0)
                field04A = ITEMS.Entry(field048)->variantCount - 1;
        }
        if (field04E > 0) {
            PLAY(0x27);
            ++field04A;
            if (field04A >= static_cast<int>(ITEMS.Entry(field048)->variantCount))
                field04A = 0;
        }
    }
    if (field04C < 255)
        field04C = field04C + 25;
    if (field04F == 1 && NAME_LIST.Size() > 0) {
        if (ITEMS.Entry(field048)->available > 0) {
            PLAY(0x2d);
            if (field051 == 0) {
                if (ITEMS.Entry(field048)->variantCount > 1) {
                    field051 = 1;
                    field04A = 0;
                } else {
                    g_SelectedReplayVariantAt006714A4 = 1;
                    g_ReplayModeAt0066C238 = 2;
                    TRANSITION();
                    return 0x2201;
                }
            } else {
                g_SelectedReplayVariantAt006714A4 = field04A + 1;
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
    if (field050 == 1) {
        if (field051 == 1) {
            PLAY(0x28);
            field051 = 0;
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
