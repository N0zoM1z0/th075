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
};
class FighterControlCallsF174 {
public:
    void UpdateControls();
    void PackDirectionBits();
};
