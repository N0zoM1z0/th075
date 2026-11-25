#ifndef TH075_TITLE_SCENE_HPP
#define TH075_TITLE_SCENE_HPP
#include "engine/SceneBase.hpp"

class TextureManagerF198;

// The title menu (vtable 00658308). The scene allocator reserves 0x3C bytes.
class TitleScene : public SceneBase {
public:
    TitleScene();                                                   // 0043A020
    virtual ~TitleScene();                                          // slot 0, 0043A1E0
    virtual unsigned short Update();                                // slot 1, 0043A270
    virtual void Render();                                          // slot 2, 0043A7A0
    void PollMenuInput();                                           // 0043ABF0

    TextureManagerF198* textures;                     // +0x008 the scene's texture manager
    unsigned int elapsedMs;              // +0x00C elapsed time
    unsigned int openedAtMs;              // +0x010 start time
    int field014;                       // +0x014 cleared by PollMenuInput
    int verticalInput;                       // +0x018 vertical input: 1, -1 or 0
    int escapeHeldFrames;                       // +0x01C frames Escape has been held
    unsigned char backgroundAlpha;             // +0x020
    unsigned char logoAlpha;             // +0x021
    unsigned char footerAlpha;             // +0x022
    unsigned char menuAlpha;             // +0x023
    unsigned char itemAlpha[10];        // +0x024 per menu item
    unsigned char itemSlideX[10];        // +0x02E horizontal offset per item
    signed char menuIndex;              // +0x038 the selected item
};
extern short g_TitleSelectionAt00671630;
extern signed char g_TitleAttractSwitchAt00671633;
#endif
