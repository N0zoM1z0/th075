#pragma once

// Call-only owner views. Original nominal types and complete indexed bounds
// remain unknown. Never instantiate, embed or measure these partial owners.
class SelectedProgressF174 {
public:
    unsigned int ReadSelectedWord268(signed char key);
    unsigned int ReadSelectedWord394(signed char key);
    void SetSelectedValue8(int value);
    void SetSelectedValue12(int value);
    int GetSelectedValue8();
    int GetSelectedValue12();
};
class BattleInputF174 {
public:
    void PollPauseShortcut();
    void UpdatePlayerEffects();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x018 - 0x000];
    signed char field018;
    unsigned char unknown019[0x0A0 - 0x019];
    unsigned char field0A0;
    unsigned char unknown0A1[0x10C - 0x0A1];
    int field10C;
    unsigned char unknown110[0x114 - 0x110];
    int field114;
    unsigned char field118;
};
class FighterControlCallsF174 {
public:
    void UpdateControls();
    void PackDirectionBits();
};
