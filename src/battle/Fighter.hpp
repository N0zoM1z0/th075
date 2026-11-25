#ifndef TH075_FIGHTER_HPP
#define TH075_FIGHTER_HPP
#include "battle/Actor.hpp"
#include <deque>
#include "battle/FighterOutcomeByteF992.hpp"
#include "assets/ScriptResource4205F0.hpp"
#include "battle/CameraResetF481.hpp"
#include "input/InputMapping4388D0.hpp"
#include "audio/SoundBank.hpp"

class EffectManagerLifetimeF161;
class CharacterObject;
class TimelineDrawing438D00;
class FighterTextureF282;
class TextureManagerF198;

typedef std::vector<FighterSequenceInfo*> ActionSequenceSlots;
typedef HeldInputBlock4388D0 InputState;

class CommandListF283;

class Fighter : public Actor {
public:
    // Helpers every character calls at one shared address.
    void ClearAuxiliaryWords();                                     // 00453A10
    int ChooseIntegerRange(int lower, int upper);                   // 00455610
    signed char MatchInputPattern(const char*, signed char, signed char);  // 00455800
    void PackDirectionBits();                                       // 00455B30
    void RecordRoundFields(signed char, short, signed char, signed char, signed char, int, int, int);  // 004574D0
    bool UpdateFacingFromOpponent();                                // 004550B0
    short CalculateDamage(Actor* attack);                           // 00455640 damage this fighter's attack deals
    void SetNoticeMode(unsigned char mode);                         // 0045CD50
    void LoadResources();                                           // 00456B60
    void ChoosePatternSequence();
    void LoadPattern();                                             // 00457660
    void SelectResourceParameters();                                // 00452B30
    void ApplyMode5Direction();                                      // 00454C20
    void SetCommandSelection(int selection, unsigned char mode, unsigned int mask);  // 00454BC0
    void ClearField47CAt00454C00();                                  // 00454C00
    void LoadStageResource();                                       // 004584D0
    void InitializeNotice(short notice);                            // 0045CDC0
    unsigned char ProcessAction();                                  // 0045CE10
    void ConfigureNoticeText(unsigned char enabled);                // 0045D650
    void BeginNoticeTransition(unsigned char notice, unsigned char direction);  // 0045D6A0
    void ClearNoticeTransition();                                   // 0045D6F0
    void AdvanceNoticeLevels();                                     // 0045D710

    // Base fighter methods (0x451EB0-0x45D710).
    void SetBindings(const void* source);
    void UpdateControls();                                     // 00452F10
    void BindAnimation();
    void Render();                        // slot 2 override for every fighter, 00453F70
    void SetNoticeFields(signed char value,unsigned char enabled,unsigned char alpha);
    void RenderNotice(void* text,unsigned char red,unsigned char green,unsigned char blue,unsigned char highlighted);
    void BindOpponent(void* other);
    void RecordRoundFields(signed char index, short value, unsigned char first, unsigned char second, unsigned char third, unsigned int payloadA, unsigned int payloadB, unsigned int payloadC);
    void AdjustCameraOffset(signed char alternate);
    void SpawnBattleEffect(short effect, float x, float y, signed char facing, signed char layer);
    void SpawnTrackedEffect(short effect, float x, float y, signed char facing, signed char layer, unsigned char linked);
    void SpawnTrackedEffect(short effect, float x, float y, signed char facing, signed char layer, unsigned char linked, unsigned char mode);
    void SpawnAuxEffect(short effect, float x, float y, signed char facing, signed char layer);
    void PlaySound(short sound);
    void PlaySharedSound(short sound);
    void ClearMotionFields();            // 00453E20: clear four motion fields
    void UpdateGaugeTimer(int amount);  // 0046D000 shared spirit timer
    void SetCameraShake(float amount); // 00453E60 native shared camera update
    bool IsState150To199();
    bool IsState95To99();
    unsigned char SelectHitResponse(unsigned int flags);
    void SetNonnegativeWord(short value);
    void BeginFadeParameters(unsigned char mode);
    void ApplyOpponentGaugeChange(short base, short multiplier, short count);
    void RenderSideEffect();
    void DrawFacingSprite(short sprite, float position, float y, unsigned long color);
    void RenderFadeOverlay();
    bool IsState50To149();
    bool IsGroundedStateWindow();
    void AdvanceGuardedState();
    void AdvancePosition();
    void UpdateCounters();
    void ChooseFrameAction();
    signed char CheckHorizontalLimits();

    // Fighter vtable slots 5-19. The base table (00658FE8) implements only
    // slots 6 and 8; the rest are _purecall and per character.
    Fighter();                            // 004567B0
    virtual ~Fighter() = 0;                   // slot 5: each character's deleting destructor
    virtual void ResetRound();            // slot 6, base 00457010
    virtual void CreateOwnedObject(CharacterObject** object) = 0;  // slot 7
    virtual void ForwardBaseAction();     // slot 8, base 00451EB0
    virtual void RenderChain() = 0;       // slot 9
    virtual void DispatchActions() = 0;   // slot 10
    virtual void ChooseAction() = 0;      // slot 11
    virtual void ChooseCardAction() = 0;  // slot 12
    virtual void PollCommands() = 0;      // slot 13
    virtual void SelectVariant() = 0;     // slot 14
    virtual void ConfigureStage() = 0;    // slot 15
    virtual void AdvanceSequence() = 0;   // slot 16
    virtual void RenderStage(signed char mode) = 0;  // slot 17
    virtual void NoOpSlot18() = 0;        // slot 18
    virtual void AdvanceAuxiliary() = 0;  // slot 19

    char name[0x104];                   // +0x0C4 character name, set by each constructor
    char tag[0x104];                    // +0x1C8 character tag, set by each constructor
    signed char field2CC;               // +0x2CC
    signed char field2CD;               // +0x2CD
    signed char field2CE;               // +0x2CE LoadResources loads field2CE + 1 texture pages
    unsigned char unknown2CF[0x2D0 - 0x2CF];
    int score;                          // +0x2D0 raised by 100-500 per hit
    CameraResetF481 cameraState;        // +0x2D4
    float field2DC;                     // +0x2DC
    float field2E0;                     // +0x2E0
    float field2E4;                     // +0x2E4
    Fighter* opponent;                  // +0x2E8 the other player
    EffectManagerLifetimeF161* field2EC; // +0x2EC owned effect-manager object
    // Linked effects copy this exact 36-byte fighter packet into Actor+0x10.
    // Retain all existing field names while exposing its shared transform type.
    union {
        struct {
            unsigned char field2F0;     // +0x2F0 transform enabled
            unsigned char field2F1;     // +0x2F1 alpha
            unsigned char field2F2;     // +0x2F2 red
            unsigned char field2F3;     // +0x2F3 green
            unsigned char field2F4;     // +0x2F4 blue
            unsigned char unknown2F5[0x2F6 - 0x2F5];
            short field2F6;             // +0x2F6
            short field2F8;             // +0x2F8
            short field2FA;             // +0x2FA
            float field2FC;             // +0x2FC
            float field300;             // +0x300
            unsigned char unknown304[0x308 - 0x304];
            float field308;             // +0x308
            float field30C;             // +0x30C
            float field310;             // +0x310
        };
        TransformRecordF136 effectTransformRecord;
    };
    union {
        struct {
            float field314;
            float field318;
            float field31C;
            float field320;
        };
        float effectParameters[4];     // +0x314
    };
    short health;                       // +0x324 F999 and F1112 both read these as life
    short recoverableHealth;            // +0x326
    short healthBeforeCollision;        // +0x328 health used for damage scaling during collision
    unsigned char field32A[20];         // +0x32A per-entry arrays written by RecordRoundFields (0x32A-0x45F);
    short healthLimits[20];             // +0x33E array lengths follow from where the next array starts
    signed char bombCount;              // +0x366 Spirit Strike stock
    unsigned char unknown367[0x368 - 0x367];
    float pendingSpellCharge;           // +0x368 accumulated gain that is converted into spell power
    float spellPower;                   // +0x36C 100 points per usable stock
    signed char field370[20];           // +0x370
    unsigned char field384[20];         // +0x384
    short selectedSpellCards[2];        // +0x398 zero-based choices for the first and second sets
    unsigned char spellDeclarationExpired; // +0x39C blocks another declaration until reset
    signed char field39D;               // +0x39D highest entry index recorded so far
    signed char field39E;               // +0x39E
    unsigned char unknown39F[0x3A0 - 0x39F];
    short spellTimer;                   // +0x3A0 positive while a spell is declared
    short field3A2;                     // +0x3A2
    int field3A4;                       // +0x3A4 signed card/knockout countdown
    int field3A8;                       // +0x3A8 signed card/knockout countdown
    signed char field3AC;               // +0x3AC
    signed char field3AD;               // +0x3AD
    unsigned char field3AE;             // +0x3AE
    unsigned char unknown3AF[0x3B0 - 0x3AF];
    short spirit;                       // +0x3B0 specials need it; guarding drains it, at 0 a guard crush
    short spiritPrevious;               // +0x3B2
    short spiritWait;                   // +0x3B4
    short spiritCooldown;               // +0x3B6
    short field3B8;                     // +0x3B8
    short field3BA;                     // +0x3BA
    short field3BC;                     // +0x3BC
    signed char field3BE;               // +0x3BE
    unsigned char unknown3BF[0x3C0 - 0x3BF];
    float comboRate;                    // +0x3C0 damage scale; each hit multiplies it
    short comboCount;                   // +0x3C4
    short comboDamage;                  // +0x3C6
    short flashGauge;                   // +0x3C8
    short field3CA;                     // +0x3CA
    short field3CC;                     // +0x3CC
    FighterOutcomeByteF992 field3CE;    // +0x3CE signed/unsigned round outcome (F992)
    unsigned char field3CF;             // +0x3CF unsigned continuation/status byte
    unsigned int field3D0[12];          // +0x3D0
    unsigned int field400[12];          // +0x400
    unsigned int field430[12];          // +0x430
    int field460;                       // +0x460
    unsigned char field464;             // +0x464 set while a knockout is being resolved
    unsigned char field465;             // +0x465
    unsigned char unknown466[0x468 - 0x466];
    ActionSequenceSlots sequenceSlots;  // +0x468 action sequences, indexed by action id
    short field478;                     // +0x478 signed texture slot count
    unsigned char unknown47A[0x47C - 0x47A];
    int field47C;                       // +0x47C
    CommandListF283* field480;                     // +0x480
    signed char field484;               // +0x484
    unsigned char unknown485[0x488 - 0x485];
    float field488;                     // +0x488
    unsigned int field48C;              // +0x48C
    float field490;                     // +0x490
    InputMapping4388D0 inputBindings;    // +0x494 controller binding block
    int inputX;                         // +0x4DC held input: direction -1/0/+1, buttons count held frames
    int inputY;                         // +0x4E0
    int field4E4;                       // +0x4E4
    int inputA;                         // +0x4E8
    int inputB;                         // +0x4EC
    int inputC;                         // +0x4F0
    unsigned long inputD;               // +0x4F4
    int bufferedX;                      // +0x4F8 buffered input, consulted when the held value is not fresh
    int bufferedY;                      // +0x4FC
    unsigned long bufferedA;            // +0x500
    unsigned long bufferedB;            // +0x504
    unsigned long bufferedC;            // +0x508
    unsigned long bufferedD;            // +0x50C
    signed char field510;               // +0x510
    unsigned char aiCommand;            // +0x511 AI command chosen for the current decision
    short aiWaitTimer;                  // +0x512
    short aiStep;                       // +0x514
    short aiCardTimer;                  // +0x516
    std::deque<unsigned char> inputHistory; // +0x518, native command history
    signed char field52C;             // +0x52C
    signed char field52D;             // +0x52D
    signed char field52E;             // +0x52E
    signed char field52F;               // +0x52F
    signed char field530;             // +0x530
    signed char field531;             // +0x531
    signed char field532;               // +0x532
    unsigned char unknown533[0x534 - 0x533];
    union {
        TimelineDrawing438D00* field534; // +0x534 renderer view
        FighterTextureF282* field534Texture; // secondary texture/resource view
    };
    unsigned char fadeAlpha;            // +0x538
    unsigned char drawMode;             // +0x539
    signed char quoteLineCount;         // +0x53A lines in the win quote
    char quoteLines[2][200];            // +0x53B win quote text, one line each
    signed char quoteBadges[2];         // +0x6CB notice badge shown with each line
    unsigned char unknown6CD[0x6D0 - 0x6CD];
    SoundBank soundBank;                // +0x6D0
    signed char sequencePhase;          // +0x6E4
    unsigned char field6E5;               // +0x6E5 byte written by SelectVariant
    signed char noticeState;            // +0x6E6
    signed char noticeBadge;            // +0x6E7
    signed char noticeFirst;            // +0x6E8 signed notice gate
    unsigned char noticeColor;          // +0x6E9
    short noticeAxis;                   // +0x6EA
    short noticeExtent;                 // +0x6EC
    unsigned char noticeEnabled;        // +0x6EE
    unsigned char field6EF;             // +0x6EF
    short scriptId;                     // +0x6F0
    short scriptBitMask;                // +0x6F2
    short scriptIndex;                  // +0x6F4
    short scriptStep;                   // +0x6F6
    signed char field6F8;               // +0x6F8 signed stage-render gate
    unsigned char unknown6F9[0x6FA - 0x6F9];
    short field6FA;                     // +0x6FA
    short field6FC;                     // +0x6FC
    unsigned char unknown6FE[0x700 - 0x6FE];
    TextureManagerF198* stageTexture;  // +0x700 stage texture resource
    unsigned char unknown704[0x705 - 0x704];
    signed char field705[10];           // +0x705 texture page counts for stages 1 through 10
    unsigned char unknown70F[0x713 - 0x70F];
    signed char field713;               // +0x713 signed character sequence state
    ScriptResource4205F0 script;       // +0x714 script indices and sequence deque
    unsigned short fieldEF8;            // +0xEF8 wrapping animation timer
    short fieldEFA;                     // +0xEFA signed per-owner projectile counter
    short sequenceTimer;                // +0xEFC
    short fieldEFE;                     // +0xEFE signed stage fade timer
    short scriptCounterF00;              // +0xF00 signed 16-bit script state
    short scriptCounterF02;              // +0xF02 signed 16-bit script state
    short fieldF04;                     // +0xF04
    short fieldF06;                     // +0xF06 signed third-boss phase/cadence value
    short fieldF08;                     // +0xF08 signed third-boss trajectory/cadence value
    short fieldF0A;                     // +0xF0A
    short fieldF0C;                     // +0xF0C
    short fieldF0E;                     // +0xF0E
};

typedef char FighterLayoutCheck[(
    offsetof(Fighter, cameraState) == 0x2D4 &&
    offsetof(Fighter, soundBank) == 0x6D0 &&
    offsetof(Fighter, opponent) == 0x2E8 &&
    offsetof(Fighter, effectTransformRecord) == 0x2F0 &&
    offsetof(Fighter, health) == 0x324 &&
    offsetof(Fighter, healthBeforeCollision) == 0x328 &&
    offsetof(Fighter, bombCount) == 0x366 &&
    offsetof(Fighter, pendingSpellCharge) == 0x368 &&
    offsetof(Fighter, spellPower) == 0x36C &&
    offsetof(Fighter, selectedSpellCards) == 0x398 &&
    offsetof(Fighter, spellDeclarationExpired) == 0x39C &&
    offsetof(Fighter, spellTimer) == 0x3A0 &&
    offsetof(Fighter, spirit) == 0x3B0 &&
    offsetof(Fighter, sequenceSlots) == 0x468 &&
    offsetof(Fighter, field478) == 0x478 &&
    offsetof(Fighter, inputBindings) == 0x494 &&
    offsetof(Fighter, inputHistory) == 0x518 &&
    sizeof(std::deque<unsigned char>) == 0x14 &&
    offsetof(Fighter, inputX) == 0x4DC &&
    offsetof(Fighter, script) == 0x714 &&
    offsetof(Fighter, sequenceTimer) == 0xEFC &&
    sizeof(Fighter) == 0xF10) ? 1 : -1];

#endif
