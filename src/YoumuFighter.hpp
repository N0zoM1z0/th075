#ifndef TH075_YOUMU_FIGHTER_HPP
#define TH075_YOUMU_FIGHTER_HPP
#include "Fighter.hpp"
class YoumuGeneratedF224;

// Youmu's fighter: vtable Youmu ctor F223 at 0x006598D0.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YoumuFighter : public Fighter {
public:
    YoumuFighter();
    virtual ~YoumuFighter();
    virtual void Advance(); // slot 1: nonexact giant at 005214B0

    // Provisional native-call ABI declarations from the complete giant
    // research parent; do not infer separate helper implementations.
    void SpawnDirectedAt453A70(int,int,int,char,int);
    void SpawnFloatXRawYAt453A70(int,float,int,char,int);
    void SpawnFloatXYAt453A70(int,float,float,char,int);
    void SpawnWithFloatAt453A70(int,int,float,char,int);
    void SetMotionStateAt40FBB0(int,float,int);
    int RandomBoundaryAt455580(int,int);
    void SetFloatMotionAt40FBB0(float,float,int);
    void AnimatePushAt453E80(int);
    void SpawnExtraAt453B50(int,int,float,char,int,int,int);
    void SpawnExtraRawYAt453B50(int,int,int,char,int,int,int);
    void ResetMotionAt40FC50();
    void ApplyStateAt454A70(int);
    void EmitStateAt452B30();
    void InitTrajectoryAt453E60(float);
    void SetupCollisionAt454BC0(int,int,int);
    void SpawnRawAt453C80(int,int,int,char,int);
    void SpawnFloatXRawYAt453C80(int,float,int,char,int);
    void NativeGameEffectAt455B30();
    void ConfigureStormAt454BC0(int,int,int);
    void SpawnMixedAt453C80(int,int,float,char,int);
    void SpawnAt453C80(int,float,float,char,int);
    short GetNativeActionAt40FA30();
    void SetNativeActionAt40FAC0(int);
    signed char ContactAt454EE0();
    void SetAuxActionAt40FB40(int);

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    int ChooseRecordedIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
    void PollCommands();
    signed char CheckPattern(const char*, int, int);
    void AdvanceSequence();
    void CreateOwnedObject(YoumuGeneratedF224** output);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    unsigned char unknownF16[0xF18 - 0xF16];
    float fieldF18;
    float fieldF1C;
    float fieldF20;
    float fieldF24;
    unsigned char unknownF28[0xF40 - 0xF28];
    float fieldF40;
    float fieldF44;
    float fieldF48;
    float fieldF4C;
    unsigned char unknownF50[0xFE0 - 0xF50];
    unsigned char fieldFE0;
    unsigned char fieldFE1;
    unsigned char fieldFE2;
    unsigned char fieldFE3;
};

#endif
