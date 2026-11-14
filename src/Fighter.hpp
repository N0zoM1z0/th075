#ifndef TH075_FIGHTER_HPP
#define TH075_FIGHTER_HPP
#include <stddef.h>

// Script reader embedded in every fighter at +0x714. Its methods are the
// native callees 0045DD00 (count) and the field getters next to it.
class FighterScriptAccessorF410 {
public:
    short CountPatternEntries(short script);
    signed char GetByteField(short script, short index);
    short GetWordField(short script, short index);
    void* GetDwordField(short script, short index);
};

// Action sequence container at Fighter+0x468 (native accessor 004420B0).
class ActionSequenceSlots {
public:
    void *&At(unsigned int index);
};

// Controller binding block embedded at Fighter+0x494. SetBindings copies 40
// bytes at +4 and clears 28 bytes at +0x2C, so the block spans 0x48 bytes.
class InputBindingsF171 {
public:
    void SetBindings(const void* source);

    unsigned char unknown00[0x04];
    signed char device;           // +0x04 joystick index, -1 when absent
    unsigned char bindings[0x2C - 0x05];
    unsigned char state[0x48 - 0x2C];
};

// Current animation frame record (Fighter+0x74).
struct FighterFrameInfo {
    unsigned char unknown00[0x3C];
    unsigned long flags;      // +0x3C bit 0x20 is tested before action changes
};

// Action sequence record (Fighter+0x78 and the entries of sequenceSlots).
// A candidate's targetPriority is compared with the current priority.
struct FighterSequenceInfo {
    unsigned char unknown00[0x10];
    short targetPriority;     // +0x10
    short priority;           // +0x12
};

// Fighter object shared by both players, as observed by accepted fighter
// methods. Offsets 0x000-0xF0F are common to every character; character
// classes declare their own members from 0xF10 on. unknownNNN regions have
// not been observed yet, and fieldNNN members are observed but not yet
// understood. The full object size is unknown, so a Fighter is only ever
// reached through the game's own pointers, never constructed or embedded.
class Fighter {
public:
    unsigned char unknown000[0x004 - 0x000];
    signed char field004;               // +0x004
    unsigned char unknown005[0x010 - 0x005];
    unsigned char field010;             // +0x010
    unsigned char unknown011[0x044 - 0x011];
    float x;                            // +0x044
    float y;                            // +0x048
    unsigned char unknown04C[0x050 - 0x04C];
    float velocityX;                    // +0x050
    float velocityY;                    // +0x054
    unsigned char unknown058[0x05C - 0x058];
    float field05C;                     // +0x05C
    short action;                       // +0x060
    short field062;                     // +0x062
    unsigned char unknown064[0x066 - 0x064];
    signed char facing;                 // +0x066 +1 facing right, -1 facing left
    unsigned char unknown067[0x074 - 0x067];
    FighterFrameInfo* frameInfo;        // +0x074 current animation frame record
    FighterSequenceInfo* sequenceInfo;  // +0x078 current action sequence record
    int field07C;                       // +0x07C
    unsigned char unknown080[0x084 - 0x080];
    short field084;                     // +0x084
    unsigned char unknown086[0x088 - 0x086];
    short field088;                     // +0x088
    unsigned char unknown08A[0x09C - 0x08A];
    float field09C;                     // +0x09C
    float field0A0;                     // +0x0A0
    float field0A4;                     // +0x0A4
    unsigned char unknown0A8[0x0AC - 0x0A8];
    void* field0AC;                     // +0x0AC
    unsigned char unknown0B0[0x2CC - 0x0B0];
    signed char field2CC;               // +0x2CC
    signed char field2CD;               // +0x2CD
    unsigned char unknown2CE[0x2E8 - 0x2CE];
    Fighter* opponent;                  // +0x2E8 the other player
    unsigned char unknown2EC[0x2F1 - 0x2EC];
    unsigned char field2F1;             // +0x2F1
    unsigned char field2F2;             // +0x2F2
    unsigned char field2F3;             // +0x2F3
    unsigned char field2F4;             // +0x2F4
    unsigned char unknown2F5[0x2F6 - 0x2F5];
    short field2F6;                     // +0x2F6
    short field2F8;                     // +0x2F8
    short field2FA;                     // +0x2FA
    float field2FC;                     // +0x2FC
    float field300;                     // +0x300
    unsigned char unknown304[0x308 - 0x304];
    float field308;                     // +0x308
    float field30C;                     // +0x30C
    float field310;                     // +0x310
    unsigned char unknown314[0x324 - 0x314];
    short field324;                     // +0x324
    unsigned char unknown326[0x328 - 0x326];
    short field328;                     // +0x328
    unsigned char field32A[20];         // +0x32A per-entry arrays written by RecordRoundFields (0x32A-0x45F);
    short field33E[20];                 // +0x33E array lengths follow from where the next array starts
    signed char field366;               // +0x366
    unsigned char unknown367[0x36C - 0x367];
    float field36C;                     // +0x36C
    signed char field370[20];           // +0x370
    unsigned char field384[20];         // +0x384
    short aiSelectors[2];               // +0x398 two AI mode selectors; character policies pick one by index
    unsigned char field39C;             // +0x39C
    signed char field39D;               // +0x39D highest entry index recorded so far
    signed char field39E;               // +0x39E
    unsigned char unknown39F[0x3A0 - 0x39F];
    short field3A0;                     // +0x3A0
    unsigned char unknown3A2[0x3AC - 0x3A2];
    signed char field3AC;               // +0x3AC
    signed char field3AD;               // +0x3AD
    unsigned char unknown3AE[0x3B0 - 0x3AE];
    short meter;                        // +0x3B0
    unsigned char unknown3B2[0x3B8 - 0x3B2];
    short field3B8;                     // +0x3B8
    unsigned char unknown3BA[0x3BC - 0x3BA];
    short field3BC;                     // +0x3BC
    unsigned char unknown3BE[0x3C0 - 0x3BE];
    float field3C0;                     // +0x3C0
    unsigned char unknown3C4[0x3D0 - 0x3C4];
    unsigned int field3D0[12];          // +0x3D0
    unsigned int field400[12];          // +0x400
    unsigned int field430[12];          // +0x430
    int field460;                       // +0x460
    unsigned char unknown464[0x465 - 0x464];
    unsigned char field465;             // +0x465
    unsigned char unknown466[0x468 - 0x466];
    ActionSequenceSlots sequenceSlots;  // +0x468 action sequences, indexed by action id
    unsigned char unknown469[0x490 - 0x469];
    float field490;                     // +0x490
    InputBindingsF171 inputBindings;    // +0x494 controller binding block
    int inputX;                         // +0x4DC held input: direction -1/0/+1, buttons count held frames
    int inputY;                         // +0x4E0
    int field4E4;                       // +0x4E4
    int inputA;                         // +0x4E8
    int inputB;                         // +0x4EC
    int inputC;                         // +0x4F0
    unsigned long inputD;               // +0x4F4
    int bufferedX;                      // +0x4F8 buffered input, consulted when the held value is not fresh
    int bufferedY;                      // +0x4FC
    unsigned long bufferedA;            // +0x500
    unsigned long bufferedB;            // +0x504
    unsigned long bufferedC;            // +0x508
    unsigned long bufferedD;            // +0x50C
    unsigned char unknown510[0x511 - 0x510];
    unsigned char aiCommand;            // +0x511 AI command chosen for the current decision
    short aiWaitTimer;                  // +0x512
    short aiStep;                       // +0x514
    short field516;                     // +0x516
    unsigned char unknown518[0x52F - 0x518];
    signed char field52F;               // +0x52F
    unsigned char unknown530[0x6E4 - 0x530];
    signed char sequencePhase;          // +0x6E4
    unsigned char unknown6E5[0x6E6 - 0x6E5];
    signed char noticeState;            // +0x6E6
    unsigned char unknown6E7[0x6EF - 0x6E7];
    unsigned char field6EF;             // +0x6EF
    short scriptId;                     // +0x6F0
    short scriptBitMask;                // +0x6F2
    short scriptIndex;                  // +0x6F4
    short scriptStep;                   // +0x6F6
    unsigned char field6F8;             // +0x6F8
    unsigned char unknown6F9[0x6FA - 0x6F9];
    short field6FA;                     // +0x6FA
    short field6FC;                     // +0x6FC
    unsigned char unknown6FE[0x713 - 0x6FE];
    unsigned char field713;             // +0x713
    FighterScriptAccessorF410 script;   // +0x714 script reader object embedded in the fighter
    unsigned char unknown715[0xEFC - 0x715];
    short sequenceTimer;                // +0xEFC
    unsigned char unknownEFE[0xF00 - 0xEFE];
    short fieldF00;                     // +0xF00
    unsigned char unknownF02[0xF04 - 0xF02];
    short fieldF04;                     // +0xF04
    unsigned char unknownF06[0xF0A - 0xF06];
    short fieldF0A;                     // +0xF0A
    short fieldF0C;                     // +0xF0C
    short fieldF0E;                     // +0xF0E
};

typedef char FighterLayoutCheck[(
    offsetof(Fighter, x) == 0x044 &&
    offsetof(Fighter, action) == 0x060 &&
    offsetof(Fighter, opponent) == 0x2E8 &&
    offsetof(Fighter, meter) == 0x3B0 &&
    offsetof(Fighter, inputX) == 0x4DC &&
    offsetof(Fighter, aiCommand) == 0x511 &&
    offsetof(Fighter, script) == 0x714 &&
    offsetof(Fighter, sequenceTimer) == 0xEFC &&
    sizeof(Fighter) == 0xF10) ? 1 : -1];

#endif
