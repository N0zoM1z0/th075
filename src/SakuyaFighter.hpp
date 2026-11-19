#ifndef TH075_SAKUYA_FIGHTER_HPP
#define TH075_SAKUYA_FIGHTER_HPP
#include "Fighter.hpp"
class SakuyaOwnedObjectF469;

// Sakuya's fighter: vtable Sakuya ctor F309 at 0x006594A8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class SakuyaFighter : public Fighter {
public:
    SakuyaFighter();
    virtual ~SakuyaFighter();
    virtual void Advance(); // slot 1: nonexact giant at 004AC040

    // Native-call contracts carried by the complete fighter state machine.
    // Provisional helper spellings do not establish separate class ownership.
    void SpawnDirectedAt453A70(short,int,int,signed char,signed char);
    void SpawnFloatXYAt453A70(short,float,float,signed char,signed char);
    void SpawnWithFloatAt453A70(short,int,float,signed char,signed char);
    void SetMotionStateAt40FBB0(int,float,int);
    void ResetMotionAt40FC50();
    void InitTrajectoryAt453E60(float);
    void ApplyAt453E80(short);
    void BeginStateAt454A70(unsigned char);
    void RefreshStateAt452B30();
    void SetAngleAt40FB70(float,float);
    void SetAngleBitsAt40FB70(int,float);
    void PrepareActionAt453D60(short);
    void SpawnAt453C80(short,float,float,signed char,signed char);
    void SpawnMixedAt453C80(short,int,float,signed char,signed char);
    void ConfigureStormAt454BC0(int,unsigned char,unsigned int);
    void SpawnRawAt453C80(short,int,int,signed char,signed char);
    void SpawnSevenAt453B50(short,int,int,signed char,signed char,unsigned char,unsigned char);
    void SpawnSevenFloatAt453B50(short,float,float,signed char,signed char,unsigned char,unsigned char);
    void SpawnSevenRawXFloatYAt453B50(short,int,float,signed char,signed char,unsigned char,unsigned char);
    int RandAt455580(int,int);
    short GetNativeActionAt40FA30();
    void SetNativeActionAt40FAC0(short);
    signed char ContactAt454EE0();
    void SetAuxActionAt40FB40(short);

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
    void EnableRoundSound(int);
    void InterruptSpecial(int);
    void PollCommands();
    void AdvanceSequence();
    void ResetRound();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(SakuyaOwnedObjectF469** out);
    void SelectVariant();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    short fieldF16;
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
