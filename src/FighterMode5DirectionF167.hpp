#pragma once

// Call-only physical vtable prefix. Uncalled slots establish indices only,
// not original signatures. The slot11 call passes this and no arguments and
// ignores its result. Never instantiate or embed this incomplete receiver.
class FighterMode5DirectionF167 {
public:
    virtual void UnknownSlot0();
    virtual void UnknownSlot1();
    virtual void UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
    virtual void UnknownSlot7();
    virtual void UnknownSlot8();
    virtual void UnknownSlot9();
    virtual void UnknownSlot10();
    virtual void OnDirectionPolicy();
    void ApplyMode5Direction();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x044 - 0x004];
    float field044;
    unsigned char unknown048[0x4DC - 0x048];
    int field4DC;
    int field4E0;
    unsigned char unknown4E4[0x530 - 0x4E4];
    signed char field530;
    signed char field531;
};
