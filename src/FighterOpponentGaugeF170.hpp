#pragma once

// Call-only receiver. The used parameters are signed low-word carriers;
// original nominal types, method name and complete owner layout are unknown.
// Never instantiate, allocate or embed this private owner.
class FighterOpponentGaugeF170 {
public:
    void ApplyOpponentGaugeChange(short base, short multiplier, short count);
};
