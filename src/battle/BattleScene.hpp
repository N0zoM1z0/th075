#ifndef TH075_BATTLE_SCENE_HPP
#define TH075_BATTLE_SCENE_HPP
#include "engine/GameSharedState.hpp"
#include <windows.h>
#include "battle/Fighter.hpp"
#include "battle/BattlePhase.hpp"
#include "engine/SceneBase.hpp"
#include "graphics/DigitAtlasesF177.hpp"

struct IDirect3DTexture8;


// The combo counter shown for each side; the battle scene allocates 20 bytes.
class ComboDisplay {
public:
    ComboDisplay(IDirect3DTexture8* texture, signed char side);    // 0043D490
    void UpdateCounter(short count, short damage, short rate);     // 0043D4D0
    void Render();                                                 // 0043D570

    IDirect3DTexture8* texture;           // +0x00
    short count;                          // +0x04 hits in the combo
    short damage;                         // +0x06
    short rate;                           // +0x08 combo rate x1000
    unsigned char alpha;                  // +0x0A
    signed char side;                     // +0x0B 1 on the left, -1 on the right
    short hold;                           // +0x0C frames left before it fades
    short phase;                          // +0x0E slide-in angle in degrees
    float slide;                          // +0x10
};
typedef char ComboDisplaySize[sizeof(ComboDisplay) == 20 ? 1 : -1];

class CombatEffects;
class TextureManagerF198;

// The battle scene (vtable 00658334, constructor 0043AD10, destructor
// 0043B0B0). The scene allocator reserves 0x11C bytes.
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

    TextureManagerF198* textureManager;  // +0x008
    unsigned long phaseFrames;            // +0x00C countdown for the current phase
    int elapsedBattleFrames;              // +0x010 unpaused updates, including freeze frames
    int replayFrame;                      // +0x014
    signed char battlePhase;              // +0x018 BattlePhase values
    unsigned char unknown019[0x01A - 0x019];
    short knockoutFreezeFrames;           // +0x01A
    unsigned char restoreResources;       // +0x01C
    unsigned char unknown01D[0x020 - 0x01D];
    int previousSecondRenderCount;        // +0x020
    int currentSecondRenderCount;         // +0x024
    unsigned long renderSampleStartMs;    // +0x028
    unsigned char unknown02C[0x034 - 0x02C];
    RECT hitBounds;                       // +0x034 overlap of the boxes that just hit
    Fighter* fighters[2];                 // +0x044 the two fighters
    DigitAtlasesF177* digitAtlas;         // +0x04C
    ComboDisplay* comboDisplays[2];       // +0x050 each side's combo counter
    ComboDisplay* activeComboDisplay;     // +0x058 the attacker's counter while hits resolve
    signed char storyDialogueEnds;        // +0x05C
    signed char matchWinnerSide;          // +0x05D winner of the match
    signed char victoryQuoteLine;         // +0x05E line of the winner's quote
    unsigned char unknown05F[0x060 - 0x05F];
    int noticeFrames;                     // +0x060
    unsigned char noticeKind;             // +0x064
    unsigned char unknown065[0x068 - 0x065];
    int awardedSpellBonus;                // +0x068
    int spellBonusBannerFrames;           // +0x06C
    float noticeVerticalEdgeOffset;       // +0x070
    float noticeHorizontalEdgeOffset;     // +0x074
    float noticeTitleMotion;              // +0x078
    float noticeSubtitleMotion;           // +0x07C
    float noticeFlashScale;               // +0x080
    float noticeFlashScaleStep;           // +0x084
    float noticePulseScale;               // +0x088
    float hudOffsetY;                     // +0x08C
    float victoryBadgeX;                       // +0x090
    unsigned long field094;               // +0x094
    unsigned char healthBarTint[2];       // +0x098 per-side brightness
    unsigned char unknown09A[0x09C - 0x09A];
    float spellBackgroundBrightness;      // +0x09C
    unsigned char pauseMenuOpen;          // +0x0A0
    unsigned char pauseOverlayAlpha;      // +0x0A1
    unsigned char unknown0A2[0x0A4 - 0x0A2];
    InputState inputSnapshots[2];         // +0x0A4 restored after unpausing
    unsigned char spellPanelAlpha[2];     // +0x0DC per-side spell overlay
    unsigned char spellTitleAlpha[2];     // +0x0DE
    unsigned char spellNumbersAlpha[2];   // +0x0E0
    unsigned char unknown0E2[0x0E4 - 0x0E2];
    float spellTitleScale[2];             // +0x0E4
    int initialSpellTimer[2];             // +0x0EC per-side declared timer
    float spellPanelY[2];                 // +0x0F4
    float spellPanelRiseSpeed[2];         // +0x0FC
    float spellNumbersOffsetY[2];         // +0x104
    unsigned long attractFrames;          // +0x10C
    int reduceRoundStockKeyHeldFrames;    // +0x110
    int escapeKeyHeldFrames;              // +0x114
    signed char pauseMenuRow;             // +0x118 pause or practice menu
};

typedef char BattleSceneStateOffsets[(offsetof(BattleScene, battlePhase) == 0x018 &&
                                     offsetof(BattleScene, pauseMenuOpen) == 0x0A0 &&
                                     offsetof(BattleScene, spellTitleScale) == 0x0E4 &&
                                     offsetof(BattleScene, spellPanelY) == 0x0F4 &&
                                     offsetof(BattleScene, spellNumbersOffsetY) == 0x104) ? 1 : -1];

extern short g_MaxComboCount;
extern unsigned long g_MaxCombatScore;
extern CombatEffects g_CombatEffects;
// Existing float wrapper; original declaration and ownership remain unresolved.
float __cdecl CeilCollisionCoordinate(float value);
#endif
