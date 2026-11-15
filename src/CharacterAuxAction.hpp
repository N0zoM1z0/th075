#ifndef TH075_CHARACTER_AUX_ACTION_HPP
#define TH075_CHARACTER_AUX_ACTION_HPP
#include "Actor.hpp"
// Auxiliary effect object; its vtable (0065A0E0) puts Advance at slot 1.
class CharacterAuxObject : public Actor {
public:
    void Advance();
    short AdvanceNestedFrame();
    void ResetSecondaryCounters(short frame);
    void SetPolarVelocity(float angle, float speed);
    void EnableTransform(float x, float y, float z);
    int ChooseIntegerRange(int lower, int upper);
    void SpawnPeer(short effect, float x, float y, signed char facing, signed char layer);
    void ClearField8();
};
// Observed cdecl / two floats / ST0 caller view. Origin remains unknown.
float AngleAt00483300(float first, float second);
extern "C" int __cdecl rand(void);
#endif
