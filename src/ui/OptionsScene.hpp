#ifndef TH075_OPTIONS_SCENE_HPP
#define TH075_OPTIONS_SCENE_HPP
#include "engine/SceneBase.hpp"

class TextureManagerF198;

struct IDirect3DTexture8;

// The options menu (vtable 00657F38). The full extent is unknown, so the
// scene is only reached through the game's pointer.
class OptionsScene : public SceneBase {
public:
    OptionsScene();                                                 // 00428D60
    virtual ~OptionsScene();                                        // slot 0, 00428E60
    virtual unsigned short Update();                                // slot 1, 00428F00
    virtual void Render();                                          // slot 2, 004292E0
    void PollInput();                                               // 00429DC0
    void Apply(unsigned char option);                               // 00429F00 redraws an option's value

    TextureManagerF198* textures;                     // +0x008 the scene's texture manager
    IDirect3DTexture8* canvas;          // +0x00C surface the option values are drawn on
    short currentItem;                  // +0x010
    short pressedItem;                  // +0x012
    unsigned char field014;             // +0x014 alpha of the menu
    signed char field015;               // +0x015 input this frame
    signed char field016;               // +0x016
    signed char field017;               // +0x017
    signed char field018;               // +0x018
};
#endif
