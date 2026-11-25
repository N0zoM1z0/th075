#ifndef TH075_ACTOR_HPP
#define TH075_ACTOR_HPP
#include <stddef.h>
#include <vector>
#include "engine/TransformRecordF136.hpp"

struct tagRECT;   // RECT; defined by <windows.h> where vector operations are instantiated

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

// Each collision-box sequence is the native VC7.1 std::vector<RECT>
// object (16 bytes); its size()/at() methods are the original game STL
// instantiations at 004452D0 and 00445310.
typedef char RectVectorLayoutCheck[(sizeof(std::vector<tagRECT>) == 0x10) ? 1 : -1];

// The first 16 bytes are copied as four words by the native memberwise
// assignment. Keep their observed names while preserving the contiguous header.
struct FighterFrameInfoHeader {
    FighterFrameInfoHeader();
    ~FighterFrameInfoHeader();
    void ResetExtension();


    short originX;            // +0x00 sprite origin
    short originY;            // +0x02
    short unknown04;          // +0x04
    short textureIndex;       // +0x06
    ActorPose* pose;           // +0x08
    unsigned char doubleScale;    // +0x0C
    unsigned char unknown0D[3];
};

// RECT-compatible body bounds. The Windows RECT view is used only at the
// collision API boundary; this four-LONG record retains the native 16-byte copy.
struct CollisionBounds {
    long left;
    long top;
    long right;
    long bottom;
};

typedef char CollisionBoundsLayoutCheck[(sizeof(CollisionBounds) == 0x10) ? 1 : -1];

// Animation frame record (Actor+0x74, and its collision snapshot at +0xAC).
struct FighterFrameInfo : public FighterFrameInfoHeader {
    FighterFrameInfo();
    ~FighterFrameInfo();

    short damage;             // +0x10
    float comboRateScale;     // +0x14 multiplies the attacker's combo rate
    short guardDamage;            // +0x18
    short baseHitstun;            // +0x1A flash gauge given to the defender
    short attackerHitStop;    // +0x1C
    short defenderHitStop;    // +0x1E
    short guardAttackerHitStop;            // +0x20
    short guardDefenderHitStop;            // +0x22
    short meterGain;          // +0x24
    short guardSpellCharge;            // +0x26
    short airHitAction;            // +0x28
    short groundHitAction;            // +0x2A
    float reactionVelocityX;            // +0x2C horizontal reaction velocity
    float reactionVelocityY;            // +0x30 vertical reaction velocity
    short hitSound;            // +0x34
    short hitEffect;          // +0x36
    signed char reactionVariant;      // +0x38
    unsigned long flags;      // +0x3C current animation-frame flags (FrameFlags)
    unsigned long attackFlags;// +0x40 attack behavior flags (AttackFlags)
    CollisionBounds bodyBox;  // +0x44 RECT
    std::vector<tagRECT> hurtBoxes;  // +0x54
    std::vector<tagRECT> hitBoxes;   // +0x64

    FighterFrameInfo& operator=(const FighterFrameInfo& other);
};

typedef char FighterFrameInfoLayoutCheck[(
    offsetof(FighterFrameInfo, damage) == 0x10 &&
    offsetof(FighterFrameInfo, flags) == 0x3C &&
    offsetof(FighterFrameInfo, bodyBox) == 0x44 &&
    offsetof(FighterFrameInfo, hurtBoxes) == 0x54 &&
    offsetof(FighterFrameInfo, hitBoxes) == 0x64 &&
    sizeof(FighterFrameInfo) == 0x74) ? 1 : -1];

// Action sequence record (Actor+0x78 and the entries of Fighter::sequenceSlots).
// A candidate's targetPriority is compared with the current priority.
struct FighterSequenceInfo {
    FighterSequenceInfo();
    ~FighterSequenceInfo();

    std::vector<FighterFrameInfo> frames;
    short targetPriority;     // +0x10
    short priority;           // +0x12
};

// Actor collision results are shared with character object state machines.
namespace CollisionResult {
enum Value {
    None = 0,
    Hit = 1,
    Blocked = 2,
    SpecialContact = 3,
    ClashConsumedHit = 4,
    ClashPreservedHits = 5,
    Grazed = 6,
    ConditionalHit = 7,
};
}

// The rendering and animation fields shared by fighters, projectiles and
// auxiliary effects. The concrete classes own their state after offset 0x74.
class ActorRenderingBase {
public:
    ActorRenderingBase();                                                        // 00458670

    // Slots shared by fighter and object vtables. Advance is pure in the
    // base fighter table (00658FE8 slot 1 is _purecall); each class's
    // per-frame state machine overrides it.
    virtual void BindAnimation() = 0;         // slot 0, fighters: 00453D80
    virtual void Advance() = 0;           // slot 1
    virtual void Render();                // slot 2, fighters: 00453F70
    virtual void RenderNode();            // slot 3, 00410350
    virtual void RenderMirroredNode();    // slot 4, 00410A00

    void* drawing;                      // +0x004 sprite drawing context, shared with the owner's objects
    FighterFrameInfoHeader* drawFrame;        // +0x008 frame record the node renderers draw
    unsigned char unknown00C[0x010 - 0x00C];
    // The transform packet at +0x10 is also copied as a 36-byte record
    // when a fighter spawns a linked effect. Keep the individual Actor
    // fields and the packet view over exactly the same native storage.
    union {
        struct {
            unsigned char transformFlags; // +0x010 draw flags
            unsigned char color[4];     // +0x011 four colour channels
            unsigned char unknown015[0x016 - 0x015];
            short spriteOffsetX;             // +0x016
            short spriteOffsetY;             // +0x018
            short spriteOffsetZ;             // +0x01A
            float scaleX;               // +0x01C
            float scaleY;               // +0x020
            float scaleZ;               // +0x024
            float rotationX;            // +0x028
            float rotationY;            // +0x02C
            float rotationZ;            // +0x030
        };
        TransformRecordF136 transformRecord;
    };
    float pivotX;                       // +0x034
    float pivotY;                       // +0x038
    float pivotZ;                       // +0x03C
    unsigned char transformEnabled;             // +0x040
    unsigned char unknown041[0x044 - 0x041];
    float x;                            // +0x044
    float y;                            // +0x048
    float field04C;                     // +0x04C
    float velocityX;                    // +0x050
    float velocityY;                    // +0x054
    unsigned int field058;              // +0x058
    float verticalAcceleration;                     // +0x05C
    short action;                       // +0x060 action or state id
    short animationStage;               // +0x062
    short animationFrame;               // +0x064
    signed char facing;                 // +0x066 +1 facing right, -1 facing left
    unsigned char field067;             // +0x067
    unsigned char field068;             // +0x068
    unsigned char unknown069[0x06C - 0x069];
    float field06C;                     // +0x06C
    union {
        short field070;                 // +0x070 native stage-count word
        short animationStageCount;      // semantic alias
    };
    union {
        short field072;                 // +0x072 native frame-count word
        short animationFrameCount;     // semantic alias
    };
    // Helpers shared by every actor.
    short AdvanceNestedFrame();                                     // 0040FA30
    void ResetPrimaryCounters(short state);                         // 0040FAC0
    void SetThreeCounters(short action, short stage, short frame);  // 0040FB00
    void ResetSecondaryCounter(short stage);                        // 0040FB40
    void SetPolarVelocity(float angle, float speed);                // 0040FB70
    void ResetTransform(float pivotX, float pivotY, float pivotZ);  // 0040FBB0
    void ClearTransformFlag();                                      // 0040FC50
};

class Actor : public ActorRenderingBase {
public:
    Actor();                                                        // 00458650

    int RecordedRange(int lower, int upper);                         // 00455580: recorded/native random sample
    void SaveCollisionFields();                                     // 00455500 snapshot for the hit tests

    // The frame and sequence bindings used by fighters and their projectiles.
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
    int collisionResult;                    // +0x07C
    short remainingHits;                    // +0x080
    short hitstopFrames;                    // +0x082 nonzero: skip this frame and count down
    short hitInvulnerabilityFrames;         // +0x084
    short throwInvulnerabilityFrames;       // +0x086
    short grazeFrames;                      // +0x088
    short field08A;                     // +0x08A
    float collisionPointX;                  // +0x08C
    float collisionPointY;                  // +0x090
    float hitReactionVelocityX;             // +0x094 horizontal reaction velocity
    float hitReactionVelocityY;             // +0x098 vertical reaction velocity
    float field09C;                     // +0x09C
    float field0A0;                     // +0x0A0
    float field0A4;                     // +0x0A4
    // Snapshot that SaveCollisionFields takes before collisions are resolved;
    // hit tests read these rather than the live fields above.
    int savedCollisionResult;               // +0x0A8 nonzero: this actor cannot hit
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
    sizeof(ActorRenderingBase) == 0x074 &&
    offsetof(Actor, x) == 0x044 &&
    offsetof(Actor, transformRecord) == 0x010 &&
    offsetof(Actor, action) == 0x060 &&
    offsetof(Actor, frameInfo) == 0x074 &&
    offsetof(Actor, savedFrameInfo) == 0x0AC &&
    sizeof(Actor) == 0x0C4) ? 1 : -1];

#endif
