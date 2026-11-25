#ifndef TH075_RESULT_SCENE_HPP
#define TH075_RESULT_SCENE_HPP
#include <windows.h>
#include "engine/SceneBase.hpp"

class TextureManagerF198;

// The scene that tallies a finished match (vtable 00658038). The full extent
// is unknown, so it is only reached through the game's pointer.
class ResultScene : public SceneBase {
public:
    ResultScene();                                                  // 0042E640
    virtual ~ResultScene();                                         // slot 0, 0042E870
    virtual unsigned short Update();                                // slot 1, 0042E8F0
    virtual void Render();                                          // slot 2, 0042EF10
    void PollInput();                                               // 0042F450
    void DrawDecimalDigits(float x, float y, DWORD color, int number,
                           signed char style, int minDigits);       // 0042F530

    TextureManagerF198* textures;                     // +0x008 the scene's texture manager
    signed char field00C;               // +0x00C
    unsigned char field00D;             // +0x00D
    unsigned char unknown00E[0x010 - 0x00E];
    int field010;                       // +0x010
    float field014;                     // +0x014 fade value
    unsigned char field018;             // +0x018 alpha of the counters
    signed char field019;               // +0x019
    unsigned char unknown01A[0x01C - 0x01A];
    int values[4];                      // +0x01C the four tallied rows
    float field02C;                     // +0x02C
    float field030;                     // +0x030
    float field034;                     // +0x034
    int field038;                       // +0x038 the total
    int field03C;                       // +0x03C
    signed char field040;               // +0x040
    unsigned char unknown041[0x042 - 0x041];
    short offsets[5];                   // +0x042 horizontal slide of each row
};
#endif
