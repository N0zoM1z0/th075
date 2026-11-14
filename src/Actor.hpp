#ifndef TH075_ACTOR_HPP
#define TH075_ACTOR_HPP
#include <stddef.h>

// Current animation frame record (Actor+0x74).
struct FighterFrameInfo {
    unsigned char unknown00[0x3C];
    unsigned long flags;      // +0x3C bit 0x20 is tested before action changes
};

// Action sequence record (Actor+0x78 and the entries of Fighter::sequenceSlots).
// A candidate's targetPriority is compared with the current priority.
struct FighterSequenceInfo {
    unsigned char unknown00[0x10];
    short targetPriority;     // +0x10
    short priority;           // +0x12
};

// Common head of every animated battle object: fighters, their projectiles
// and effect objects use 0x00-0xA7 with the same field widths. Derived
// classes add their own members from 0xA8. unknownNNN regions are unobserved;
// fieldNNN members are observed but not yet understood. The full object size
// is unknown, so these classes are only reached through the game's pointers.
class Actor {
public:
    unsigned char unknown000[0x004 - 0x000];
    signed char field004;               // +0x004
    unsigned char unknown005[0x010 - 0x005];
    unsigned char field010;             // +0x010
    unsigned char color[4];             // +0x011 four colour channels, all 255 when opaque
    unsigned char unknown015[0x016 - 0x015];
    short field016;                     // +0x016
    short field018;                     // +0x018
    short field01A;                     // +0x01A
    float scaleX;                       // +0x01C
    float scaleY;                       // +0x020
    float scaleZ;                       // +0x024
    float rotationX;                    // +0x028
    float rotationY;                    // +0x02C
    float rotationZ;                    // +0x030
    float pivotX;                       // +0x034
    float pivotY;                       // +0x038
    float pivotZ;                       // +0x03C
    unsigned char field040;             // +0x040
    unsigned char unknown041[0x044 - 0x041];
    float x;                            // +0x044
    float y;                            // +0x048
    float field04C;                     // +0x04C
    float velocityX;                    // +0x050
    float velocityY;                    // +0x054
    unsigned int field058;              // +0x058
    float field05C;                     // +0x05C
    short action;                       // +0x060 action or state id
    short animationStage;               // +0x062
    short animationFrame;               // +0x064
    signed char facing;                 // +0x066 +1 facing right, -1 facing left
    unsigned char unknown067[0x070 - 0x067];
    short field070;                     // +0x070
    short field072;                     // +0x072
    FighterFrameInfo* frameInfo;        // +0x074 current animation frame record
    FighterSequenceInfo* sequenceInfo;  // +0x078 current action sequence record
    int field07C;                       // +0x07C
    short field080;                     // +0x080
    short field082;                     // +0x082 nonzero: skip this frame and count down
    short field084;                     // +0x084
    short field086;                     // +0x086
    short field088;                     // +0x088
    short field08A;                     // +0x08A
    float field08C;                     // +0x08C
    float field090;                     // +0x090
    unsigned int field094;              // +0x094
    unsigned int field098;              // +0x098
    float field09C;                     // +0x09C
    float field0A0;                     // +0x0A0
    float field0A4;                     // +0x0A4
};

typedef char ActorLayoutCheck[(
    offsetof(Actor, x) == 0x044 &&
    offsetof(Actor, action) == 0x060 &&
    offsetof(Actor, frameInfo) == 0x074 &&
    sizeof(Actor) == 0x0A8) ? 1 : -1];

#endif
