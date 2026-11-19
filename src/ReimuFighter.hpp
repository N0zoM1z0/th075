#ifndef TH075_REIMU_FIGHTER_HPP
#define TH075_REIMU_FIGHTER_HPP
#include "Fighter.hpp"
class ReimuGeneratedF227;

// Reimu's fighter: vtable Reimu ctor F311 at 0x006590D8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class ReimuFighter : public Fighter {
public:
    ReimuFighter();
    virtual ~ReimuFighter();
    virtual void Advance(); // slot 1, 0045DD70 (nonexact giant research parent)

    // Native-call ABI hypotheses used by the giant Advance research source.
    // These signatures preserve the VC7.1 argument passing seen in the PE;
    // the actual shared callees are owned by Actor/Fighter, not by Reimu.
    void SetMotionFloatAt40FBB0(float,float,float);
    void SpawnDirectedAt453A70(int,int,int,char,int);
    void SpawnWithFloatAt453A70(int,int,float,char,int);
    void SpawnFloatXYAt453A70(int,float,float,char,int);
    void InitTrajectoryAt453E60(float);
    void SpawnTrackedAt453B50(short,float,float,signed char,signed char,unsigned char,unsigned char);
    void SpawnFloatXAt453A70(int,float,int,char,int);
    int SelectRangeAt455580(int,int);
    void SpawnAt453C80(int,float,float,char,int);
    void SpawnMixedAt453C80(int,int,float,char,int);
    void SpawnRawXYAt453C80(int,int,int,char,int);

    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    void PollCommands();
    void AdvanceSequence();
    void ConfigureStage();
    void CreateOwnedObject(ReimuGeneratedF227** output);
    void DispatchActions();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF22 - 0xF10];
    short fieldF22;
    short fieldF24;
    short fieldF26;
    short fieldF28;
    short fieldF2A;
    float fieldF2C;
    float fieldF30;
    float fieldF34;
    float fieldF38;
    unsigned char unknownF3C[0xF54 - 0xF3C];
    float fieldF54;
    float fieldF58;
    float fieldF5C;
    float fieldF60;
    unsigned char unknownF64[0xFF4 - 0xF64];
    unsigned char fieldFF4;
    unsigned char fieldFF5;
    unsigned char fieldFF6;
    unsigned char fieldFF7;
};

#endif
