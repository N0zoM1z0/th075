#ifndef TH075_BATTLE_SCENE_HPP
#define TH075_BATTLE_SCENE_HPP
#include "GameSharedState.hpp"
#include <windows.h>
#include "Fighter.hpp"
#include "SceneBase.hpp"

struct IDirect3DTexture8;


// The combo counter shown for each side; the battle scene allocates 20 bytes.
class ComboDisplay {
public:
    ComboDisplay(IDirect3DTexture8* texture, signed char side);    // 0043D490
    void UpdateCounter(short count, short damage, short rate);     // 0043D4D0
    void Render();                                                 // 0043D570

    IDirect3DTexture8* texture;         // +0x00
    short count;                        // +0x04 hits in the combo
    short damage;                       // +0x06
    short rate;                         // +0x08 combo rate x1000
    unsigned char alpha;                // +0x0A
    signed char side;                   // +0x0B 1 on the left, -1 on the right
    short hold;                         // +0x0C frames left before it fades
    short phase;                        // +0x0E slide-in angle in degrees
    float slide;                        // +0x10
};
typedef char ComboDisplaySize[sizeof(ComboDisplay) == 20 ? 1 : -1];

// The digit atlas the HUD draws numbers with (a one-byte allocation).
class DigitAtlas {
public:
    DigitAtlas(IDirect3DTexture8* digits, IDirect3DTexture8* small, IDirect3DTexture8* large);
};
class CombatEffects { public: void Spawn(short, float, float, unsigned char, signed char, unsigned char, unsigned char); };

// The battle scene (vtable 00658334, constructor 0043AD10, destructor
// 0043B0B0). Its methods run from 0043AD10 to 00449310. The full extent
// is unknown, so the scene is only reached through the game's pointer.
class BattleScene : public SceneBase {
public:
    BattleScene();                                                  // 0043AD10
    virtual ~BattleScene();                                         // slot 0, 0043B0B0
    virtual unsigned short Update();                                         // slot 1, 0043B1B0
    virtual void Render();                                          // slot 2, 0043D9D0

    // Frame and round flow.
    void UpdatePlayerCounters();                                    // 0043B510
    void Present();                                                 // 0043B5D0
    short AdvanceState();                                           // 0043B610
    void ResolveRoundEndMode();                                     // 0043C8F0
    void ResolveKnockout();                                         // 0043C930
    void EnterRoundEnd();                                           // 0043CDB0
    void UpdateTransition();                                        // 0043D010
    void PollPauseShortcut();                                       // 004456F0
    void UpdatePlayerEffects();                                     // 00445830
    void ApplySequence();                                           // 00445A00
    void HandlePauseMenu();                                         // 004461D0
    void ProcessDebugKeys();                                        // 004480D0
    void HandleMode5Options();                                      // 004483F0
    void SetNotice(unsigned char state);                            // 00446D60
    void AdvanceOverlay();                                          // 00446D80
    void ResolveBodySeparation();                                   // 00449310

    // Drawing.
    void RenderHud();                                               // 0043E040
    void RenderDamageFlash();                                       // 004406C0
    void DrawSelectedNotice();                                      // 00440B00
    void RenderStatus();                                            // 00440B50
    void RenderEndOverlay();                                        // 00441910
    void RenderRoundBanner();                                       // 00441EA0
    void RenderOverlayTimeline();                                   // 00447340
    void RenderModeFive();                                          // 00448710

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

    void* textures;                     // +0x008 the scene's texture manager
    unsigned long field00C;             // +0x00C frame timer
    int field010;                       // +0x010 signed timeline frame offset
    int field014;                       // +0x014
    signed char field018;               // +0x018 1 in a normal match
    unsigned char unknown019[0x01A - 0x019];
    short field01A;                     // +0x01A
    unsigned char field01C;             // +0x01C
    unsigned char unknown01D[0x020 - 0x01D];
    int field020;                       // +0x020
    int field024;                       // +0x024
    unsigned long field028;             // +0x028
    unsigned char unknown02C[0x034 - 0x02C];
    RECT hitBounds;                     // +0x034 overlap of the boxes that just hit
    Fighter* fighters[2];               // +0x044 the two fighters
    DigitAtlas* digitAtlas;             // +0x04C
    ComboDisplay* comboDisplays[2];     // +0x050 each side's combo counter
    ComboDisplay* activeComboDisplay;   // +0x058 the attacker's counter while hits resolve
    signed char field05C;               // +0x05C
    signed char field05D;               // +0x05D winner of the round
    signed char field05E;               // +0x05E line of the winner's quote
    unsigned char unknown05F[0x060 - 0x05F];
    int field060;                       // +0x060
    unsigned char field064;             // +0x064
    unsigned char unknown065[0x068 - 0x065];
    int field068;                       // +0x068
    int field06C;                       // +0x06C
    float field070;                     // +0x070 +0x70-0x88 overlay transition values
    float field074;                     // +0x074
    float field078;                     // +0x078
    float field07C;                     // +0x07C
    float field080;                     // +0x080
    float field084;                     // +0x084
    float field088;                     // +0x088
    float field08C;                     // +0x08C
    float field090;                     // +0x090
    unsigned long field094;             // +0x094
    unsigned char field098;             // +0x098
    unsigned char field099;             // +0x099
    unsigned char unknown09A[0x09C - 0x09A];
    float field09C;                     // +0x09C
    unsigned char field0A0;             // +0x0A0
    unsigned char field0A1;             // +0x0A1
    unsigned char unknown0A2[0x0A4 - 0x0A2];
    InputState inputSnapshots[2];       // +0x0A4 each side's input state, saved for replays
    unsigned char field0DC[2];          // +0x0DC per side; RenderStatus alphas (+0xDC, +0xDE, +0xE0)
    unsigned char field0DE[2];          // +0x0DE
    unsigned char field0E0[2];          // +0x0E0
    unsigned char unknown0E2[0x0EC - 0x0E2];
    int field0EC[2];                    // +0x0EC per side; RenderStatus draws it as a number
    unsigned char unknown0F4[0x10C - 0x0F4];
    unsigned long field10C;             // +0x10C
    int field110;                       // +0x110
    int field114;                       // +0x114
    signed char field118;               // +0x118 pause/Mode 5 menu selection
};

extern short g_MaxComboCount;
extern unsigned long g_MaxCombatScore;
extern CombatEffects g_CombatEffects;
// Existing float wrapper; original declaration and ownership remain unresolved.
float __cdecl CeilCollisionCoordinate(float value);
#endif
