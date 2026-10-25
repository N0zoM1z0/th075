#pragma once

// Call-only views of existing storage. Complete owner identities and indexed
// extents remain unknown; never instantiate or embed these partial owners.
class RoundEndF173 {
public:
    void EnterRoundEnd();
};
class ModeCounterF173 {
public:
    void IncrementModeCounter(signed char category, signed char key);
};
class ComboCounterF173 {
public:
    // Native allocation callers forward the constructor receiver in EAX.
    ComboCounterF173(void* texture, signed char side);
    void UpdateComboCounter(short count, short value, short extra);
};
