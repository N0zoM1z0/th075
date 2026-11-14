#ifndef TH075_FIGHTER_HPP
#define TH075_FIGHTER_HPP
#include "Actor.hpp"
class TimelineDrawing438D00;

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

// Fighter object shared by both players. Offsets up to 0xF0F are common to
// every character; character classes declare their own members from 0xF10.
class Fighter : public Actor {
public:
    // Fighter vtable slots 5-19. The base table (00658FE8) implements only
    // slots 6 and 8; the rest are _purecall and per character.
    virtual void VirtualSlot5() = 0;      // 44-byte compiler function per character
    virtual void ResetRound();            // slot 6, base 00457010
    virtual void CreateOwnedObject(void** object) = 0;  // slot 7, typed per character
    virtual void ForwardBaseAction();     // slot 8, base 00451EB0
    virtual void RenderChain() = 0;       // slot 9
    virtual void DispatchActions() = 0;   // slot 10
    virtual void ChooseAction() = 0;      // slot 11
    virtual void ChooseCardAction() = 0;  // slot 12
    virtual void PollCommands() = 0;      // slot 13
    virtual void SelectVariant() = 0;     // slot 14
    virtual void ConfigureStage() = 0;    // slot 15
    virtual void AdvanceSequence() = 0;   // slot 16
    virtual void RenderStage(signed char mode) = 0;  // slot 17
    virtual void NoOpSlot18() = 0;        // slot 18
    virtual void AdvanceAuxiliary() = 0;  // slot 19

    unsigned char unknown0A8[0x0AC - 0x0A8];
    void* field0AC;                     // +0x0AC
    unsigned char unknown0B0[0x0E4 - 0x0B0];
    void* field0E4;                     // +0x0E4
    unsigned char unknown0E8[0x2CC - 0x0E8];
    signed char field2CC;               // +0x2CC
    signed char field2CD;               // +0x2CD
    unsigned char unknown2CE[0x2D8 - 0x2CE];
    float field2D8;                     // +0x2D8
    float field2DC;                     // +0x2DC
    float field2E0;                     // +0x2E0
    float field2E4;                     // +0x2E4
    Fighter* opponent;                  // +0x2E8 the other player
    void* field2EC;                     // +0x2EC
    unsigned char unknown2F0[0x2F1 - 0x2F0];
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
    float field314;                     // +0x314
    float field318;                     // +0x318
    float field31C;                     // +0x31C
    float field320;                     // +0x320
    short health;                       // +0x324 F999 and F1112 both read these as life
    short recoverableHealth;            // +0x326
    short field328;                     // +0x328
    unsigned char field32A[20];         // +0x32A per-entry arrays written by RecordRoundFields (0x32A-0x45F);
    short healthLimits[20];             // +0x33E array lengths follow from where the next array starts
    signed char field366;               // +0x366
    unsigned char unknown367[0x368 - 0x367];
    float field368;                     // +0x368
    float field36C;                     // +0x36C
    signed char field370[20];           // +0x370
    unsigned char field384[20];         // +0x384
    short field398[2];                  // +0x398 two mode words; AI policies and HUD name groups pick one
    unsigned char field39C;             // +0x39C
    signed char field39D;               // +0x39D highest entry index recorded so far
    signed char field39E;               // +0x39E
    unsigned char unknown39F[0x3A0 - 0x39F];
    short field3A0;                     // +0x3A0
    unsigned char unknown3A2[0x3A4 - 0x3A2];
    unsigned int field3A4;              // +0x3A4
    unsigned int field3A8;              // +0x3A8
    signed char field3AC;               // +0x3AC
    signed char field3AD;               // +0x3AD
    unsigned char field3AE;             // +0x3AE
    unsigned char unknown3AF[0x3B0 - 0x3AF];
    short meter;                        // +0x3B0
    short meterPrevious;                // +0x3B2
    short meterWait;                    // +0x3B4
    short meterCooldown;                // +0x3B6
    short field3B8;                     // +0x3B8
    short field3BA;                     // +0x3BA
    short field3BC;                     // +0x3BC
    unsigned char unknown3BE[0x3C0 - 0x3BE];
    float field3C0;                     // +0x3C0
    short comboCount;                   // +0x3C4
    short comboDamage;                  // +0x3C6
    short flashGauge;                   // +0x3C8
    short field3CA;                     // +0x3CA
    short field3CC;                     // +0x3CC
    unsigned char unknown3CE[0x3D0 - 0x3CE];
    unsigned int field3D0[12];          // +0x3D0
    unsigned int field400[12];          // +0x400
    unsigned int field430[12];          // +0x430
    int field460;                       // +0x460
    unsigned char unknown464[0x465 - 0x464];
    unsigned char field465;             // +0x465
    unsigned char unknown466[0x468 - 0x466];
    ActionSequenceSlots sequenceSlots;  // +0x468 action sequences, indexed by action id
    unsigned char unknown469[0x47C - 0x469];
    int field47C;                       // +0x47C
    void* field480;                     // +0x480
    signed char field484;               // +0x484
    unsigned char unknown485[0x488 - 0x485];
    float field488;                     // +0x488
    unsigned int field48C;              // +0x48C
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
    unsigned char field510;             // +0x510
    unsigned char aiCommand;            // +0x511 AI command chosen for the current decision
    short aiWaitTimer;                  // +0x512
    short aiStep;                       // +0x514
    short aiCardTimer;                  // +0x516
    unsigned char unknown518[0x52C - 0x518];
    unsigned char field52C;             // +0x52C
    unsigned char field52D;             // +0x52D
    unsigned char field52E;             // +0x52E
    signed char field52F;               // +0x52F
    unsigned char field530;             // +0x530
    unsigned char field531;             // +0x531
    signed char field532;               // +0x532
    unsigned char unknown533[0x534 - 0x533];
    TimelineDrawing438D00* field534;    // +0x534
    unsigned char fadeAlpha;            // +0x538
    unsigned char drawMode;             // +0x539
    unsigned char unknown53A[0x6E4 - 0x53A];
    signed char sequencePhase;          // +0x6E4
    unsigned char unknown6E5[0x6E6 - 0x6E5];
    signed char noticeState;            // +0x6E6
    signed char noticeBadge;            // +0x6E7
    unsigned char noticeFirst;          // +0x6E8
    unsigned char noticeColor;          // +0x6E9
    short noticeAxis;                   // +0x6EA
    short noticeExtent;                 // +0x6EC
    unsigned char noticeEnabled;        // +0x6EE
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
    unsigned char unknown715[0xEF8 - 0x715];
    short fieldEF8;                     // +0xEF8
    unsigned short fieldEFA;            // +0xEFA
    short sequenceTimer;                // +0xEFC
    unsigned short fieldEFE;            // +0xEFE
    unsigned short scriptCounterF00;    // +0xF00
    unsigned short scriptCounterF02;    // +0xF02
    short fieldF04;                     // +0xF04
    unsigned short fieldF06;            // +0xF06
    unsigned short fieldF08;            // +0xF08
    short fieldF0A;                     // +0xF0A
    short fieldF0C;                     // +0xF0C
    short fieldF0E;                     // +0xF0E
};

typedef char FighterLayoutCheck[(
    offsetof(Fighter, opponent) == 0x2E8 &&
    offsetof(Fighter, health) == 0x324 &&
    offsetof(Fighter, meter) == 0x3B0 &&
    offsetof(Fighter, inputBindings) == 0x494 &&
    offsetof(Fighter, inputX) == 0x4DC &&
    offsetof(Fighter, script) == 0x714 &&
    offsetof(Fighter, sequenceTimer) == 0xEFC &&
    sizeof(Fighter) == 0xF10) ? 1 : -1];

#endif
