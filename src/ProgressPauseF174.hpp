#pragma once

// Call-only owner views. Original nominal types and complete indexed bounds
// remain unknown. Never instantiate, embed or measure these partial owners.
class FighterControlCallsF174 {
public:
    void UpdateControls();
    void PackDirectionBits();
};
