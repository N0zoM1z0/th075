// Synthetic VC7.1 source probe for two explicitly defined virtual methods.
// These classes establish emitted code shapes, not TH075 layouts or names.

struct FighterBaseProbe {
    virtual ~FighterBaseProbe();
    virtual void Action();
    virtual void Idle();
};

FighterBaseProbe::~FighterBaseProbe() {}
void FighterBaseProbe::Action() {}
void FighterBaseProbe::Idle() {}

struct FighterDerivedProbe : FighterBaseProbe {
    virtual void Action();
    virtual void Idle();
};

void FighterDerivedProbe::Action() {
    FighterBaseProbe::Action();
}

void FighterDerivedProbe::Idle() {}

extern "C" FighterBaseProbe *CreateFighterDerivedProbe() {
    return new FighterDerivedProbe;
}
