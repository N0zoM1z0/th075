#pragma once

// Call-only views of existing storage. Original identities, complete layouts
// and indexed extents remain unknown. Never instantiate or embed these owners.
class CardProgressF172 {
public:
    void MarkCardFlag(signed char key);
    void IncrementCardCounter(signed char key);
    int GetCardValue(signed char key);
    void SetCardValue(signed char key, int value);
};

class KnockoutResolutionF172 {
public:
    void ResolveKnockout();
};
