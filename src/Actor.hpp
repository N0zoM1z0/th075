#ifndef TH075_ACTOR_HPP
#define TH075_ACTOR_HPP
#include <stddef.h>

struct tagRECT;   // RECT; defined by <windows.h> where it is needed

// Pose record a frame points to (+0x08): blend mode, colour and transform.
struct ActorPose {
    unsigned char blendMode;  // +0x00
    unsigned char color[4];   // +0x01 A, R, G, B
    unsigned char unknown05[0x06 - 0x05];
    short offsetX;            // +0x06
    short offsetY;            // +0x08
    short offsetZ;            // +0x0A
    float scaleX;             // +0x0C
    float scaleY;             // +0x10
    float scaleZ;             // +0x14
    float rotationX;          // +0x18
    float rotationY;          // +0x1C
    float rotationZ;          // +0x20
};

// The vector of collision boxes a frame carries (std::vector<RECT>, 16 bytes).
class CollisionRectSequence {
public:
    unsigned int Size();
    tagRECT &At(unsigned int index);
private:
    unsigned char storage[0x10];
};

// Animation frame record (Actor+0x74, and its collision snapshot at +0xAC).
struct FighterFrameInfo {
    short originX;            // +0x00 sprite origin
    short originY;            // +0x02
    unsigned char unknown04[0x06 - 0x04];
    short textureIndex;       // +0x06
    ActorPose* pose;          // +0x08
    unsigned char field0C;    // +0x0C
    unsigned char unknown0D[0x10 - 0x0D];
    short damage;             // +0x10
    unsigned char unknown12[0x14 - 0x12];
    float comboRateScale;     // +0x14 multiplies the attacker's combo rate
    short field18;            // +0x18
    short field1A;            // +0x1A flash gauge given to the defender
    short attackerHitStop;    // +0x1C
    short defenderHitStop;    // +0x1E
    short field20;            // +0x20
    short field22;            // +0x22
    short meterGain;          // +0x24
    short field26;            // +0x26
    short field28;            // +0x28
    short field2A;            // +0x2A
    unsigned long field2C;    // +0x2C copied to the defender's +0x94
    unsigned long field30;    // +0x30 copied to the defender's +0x98
    short field34;            // +0x34
    short hitEffect;          // +0x36
    signed char field38;      // +0x38
    unsigned char unknown39[0x3C - 0x39];
    unsigned long flags;      // +0x3C defence flags; bit 0x20 is tested before action changes
    unsigned long attackFlags;// +0x40
    long bodyBox[4];          // +0x44 RECT
    CollisionRectSequence hurtBoxes;  // +0x54
    CollisionRectSequence hitBoxes;   // +0x64
};

// Action sequence record (Actor+0x78 and the entries of Fighter::sequenceSlots).
// A candidate's targetPriority is compared with the current priority.
struct FighterSequenceInfo {
    unsigned char unknown00[0x10];
    short targetPriority;     // +0x10
    short priority;           // +0x12
};

// Common head of every animated battle object: fighters, their projectiles
// and effect objects use 0x00-0xC3 with the same field widths and share
// vtable slots 0-4 (the vtable pointer is at +0). Derived classes add their
// own members from 0xC4. unknownNNN regions are unobserved;
// fieldNNN members are observed but not yet understood. The full object size
// is unknown, so these classes are only reached through the game's pointers.
class Actor {
public:
    // Helpers shared by every actor (src/Actor.cpp).
    short AdvanceNestedFrame();                                     // 0040FA30
    void ResetPrimaryCounters(short state);                         // 0040FAC0
    void SetThreeCounters(short action, short stage, short frame);  // 0040FB00
    void ResetSecondaryCounter(short stage);                        // 0040FB40
    void SetPolarVelocity(float angle, float speed);                // 0040FB70
    void ResetTransform(float pivotX, float pivotY, float pivotZ);  // 0040FBB0
    void ClearTransformFlag();                                      // 0040FC50
    void SaveCollisionFields();                                     // 00455500 snapshot for the hit tests

    // Slots shared by fighter and object vtables. Advance is pure in the
    // base fighter table (00658FE8 slot 1 is _purecall); each class's
    // per-frame state machine overrides it.
    virtual void BindAnimation();         // slot 0, fighters: 00453D80
    virtual void Advance() = 0;           // slot 1
    virtual void Render();                // slot 2, fighters: 00453F70
    virtual void RenderNode();            // slot 3, 00410350
    virtual void RenderMirroredNode();    // slot 4, 00410A00

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
    unsigned char unknown067[0x06C - 0x067];
    float field06C;                     // +0x06C
    short field070;                     // +0x070
    short field072;                     // +0x072
    // +0x074..0x07B is the animation binding that slot 0 maintains: fighters
    // and character objects keep two record pointers here, auxiliary
    // effects (CharacterAuxObject) keep four counters.
    union {
        struct {
            FighterFrameInfo* frameInfo;        // +0x074 current animation frame record
            FighterSequenceInfo* sequenceInfo;  // +0x078 current action sequence record
        };
        struct {
            short field074;
            short field076;
            short field078;
            short field07A;
        };
    };
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
    // Snapshot that SaveCollisionFields takes before collisions are resolved;
    // hit tests read these rather than the live fields above.
    int savedField07C;                  // +0x0A8 nonzero: this actor cannot hit
    FighterFrameInfo* savedFrameInfo;   // +0x0AC
    FighterSequenceInfo* savedSequenceInfo; // +0x0B0
    short savedAction;                  // +0x0B4
    unsigned char unknown0B6[0x0B8 - 0x0B6];
    float savedX;                       // +0x0B8
    float savedY;                       // +0x0BC
    signed char savedFacing;            // +0x0C0
    unsigned char unknown0C1[0x0C4 - 0x0C1];
};

typedef char ActorLayoutCheck[(
    offsetof(Actor, x) == 0x044 &&
    offsetof(Actor, action) == 0x060 &&
    offsetof(Actor, frameInfo) == 0x074 &&
    offsetof(Actor, savedFrameInfo) == 0x0AC &&
    sizeof(Actor) == 0x0C4) ? 1 : -1];

#endif
