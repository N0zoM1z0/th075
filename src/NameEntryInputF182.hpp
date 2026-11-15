#pragma once

// Call-only views of existing scenes; original complete owner layout is unknown.
// Never instantiate or embed this partial interface.
class NameEntryInputF182 {
public:
    void PollPlayerInput();
    void PollSharedInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x00E - 0x000];
    short field00E;
    short field010;
    short field012;
    short field014;
    short field016;
};
