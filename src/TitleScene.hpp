#ifndef TH075_TITLE_SCENE_HPP
#define TH075_TITLE_SCENE_HPP
#include "SceneBase.hpp"

// The title menu (vtable 00658308). The full extent is unknown, so the
// scene is only reached through the game's pointer.
class TitleScene : public SceneBase {
public:
    TitleScene();                                                   // 0043A020
    virtual ~TitleScene();                                          // slot 0, 0043A1E0
    virtual unsigned short Update();                                // slot 1, 0043A270
    virtual void Render();                                          // slot 2, 0043A7A0
    void PollMenuInput();                                           // 0043ABF0

    void* textures;                     // +0x008 the scene's texture manager
    unsigned int field00C;              // +0x00C elapsed time
    unsigned int field010;              // +0x010 start time
    int field014;                       // +0x014 confirm pressed
    int field018;                       // +0x018 vertical input: 1, -1 or 0
    int field01C;                       // +0x01C frames Escape has been held
    unsigned char field020;             // +0x020
    unsigned char field021;             // +0x021
    unsigned char field022;             // +0x022
    unsigned char field023;             // +0x023
    unsigned char itemAlpha[10];        // +0x024 per menu item
    unsigned char itemDelay[10];        // +0x02E per menu item, frames before it slides in
    signed char menuIndex;              // +0x038 the selected item
};
extern short g_TitleSelectionAt00671630;
extern signed char g_TitleAttractSwitchAt00671633;
#endif
