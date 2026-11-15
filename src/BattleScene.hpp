#ifndef TH075_BATTLE_SCENE_HPP
#define TH075_BATTLE_SCENE_HPP
#include <windows.h>
#include "Fighter.hpp"

// The combo counter shown for each side (allocated by the battle scene).
class ComboDisplay {
public:
    void UpdateCounter(short count, short damage, short rate);
};
class BattleRecords {
public:
    int GetComboDamage();
    int GetComboCount();
    void SetComboDamage(int value);
    void SetComboCount(int value);
};
class CombatResponseActor { public: signed char ClassifyResponse(unsigned long flags); };
class CombatEffects { public: void Spawn(short, float, float, unsigned char, signed char, unsigned char, unsigned char); };

// The battle scene (vtable 00658334, constructor 0043AD10, destructor
// 0043B0B0). Its methods run from 0043AD10 to 00445A00. This declaration
// covers the members the combat and collision methods use; the extent is
// unknown, so the scene is only reached through the game's pointer.
class BattleScene {
public:
    // Combat (00442400-004450E0).
    void IncludePair(const RECT *first, const RECT *second);       // 00442400
    void SpawnMidpointEffect(short effect, unsigned char direction); // 004424E0
    void ClearBounds();                                             // 00442540
    void ResolveActiveCollisions();                                 // 00442580
    void ResolveAttackHitboxes(Actor *attack, Fighter *attacker, Fighter *defender);  // 00442A70
    void ResolveBodyContact(Actor *first, Actor *second);           // 00442E40
    void ApplyHit(Actor *attack, Fighter *attacker, Fighter *defender);                // 004431D0
    bool ApplyHitResponse(Actor *attack, Fighter *attacker, Fighter *defender);        // 004439A0
    void ApplyImpact(Actor *attack, Fighter *attacker, Fighter *defender);             // 00443E90
    void StartHitSequence(Fighter *fighter, short value);           // 00443FC0
    bool ApplyAttackHit(Actor *attack, Fighter *attacker, Fighter *defender);          // 00444020
    void ApplyGuardHit(Actor *attack, Fighter *attacker, Fighter *defender);           // 004443B0
    void ApplyReactionMode(Actor *attack, Fighter *attacker, Fighter *defender);       // 00444650
    bool ResolveGuard(Actor *attack, Fighter *attacker, Fighter *defender);            // 00444770
    bool ApplyConditionalHit(Actor *attack, Fighter *attacker, Fighter *defender);     // 00444850
    bool ResolveSpecialHit(Actor *attack, Fighter *attacker, Fighter *defender);       // 00444FC0
    bool ResolveContact(Actor *attack, Fighter *attacker, Fighter *defender);          // 004450E0
    void TransformBounds(RECT *destination, const RECT *source, Actor *actor);
    int TestOverlap(const RECT *first, const RECT *second);

    void* vtable;                       // +0x000
    unsigned int field004;              // +0x004
    void* textures;                     // +0x008 the scene's texture manager
    int field00C;                       // +0x00C
    unsigned char unknown010[0x018 - 0x010];
    signed char field018;               // +0x018 1 in a normal match (a knockout ends it)
    unsigned char unknown019[0x034 - 0x019];
    RECT hitBounds;                     // +0x034 overlap of the boxes that just hit
    Fighter* fighters[2];               // +0x044
    void* digitAtlas;                   // +0x04C
    ComboDisplay* comboDisplays[2];     // +0x050
    ComboDisplay* activeComboDisplay;   // +0x058 the attacker's counter while hits resolve
};

extern signed char g_CombatMode;
extern short g_MaxComboCount;
extern unsigned long g_MaxCombatScore;
extern BattleRecords g_BattleRecords;
extern CombatEffects g_CombatEffects;
// Existing float wrapper; original declaration and ownership remain unresolved.
float __cdecl CeilCollisionCoordinate(float value);
#endif
