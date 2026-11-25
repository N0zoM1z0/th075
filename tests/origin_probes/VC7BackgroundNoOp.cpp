// Synthetic VC7.1 probe for a source-defined empty virtual member.
// Its class and vtable are unrelated to TH075's concrete class layout.

struct BackgroundNoOpProbe {
    virtual ~BackgroundNoOpProbe();
    virtual void NoOp();
};

BackgroundNoOpProbe::~BackgroundNoOpProbe() {}

void BackgroundNoOpProbe::NoOp() {}

extern "C" BackgroundNoOpProbe *CreateBackgroundNoOpProbe() {
    return new BackgroundNoOpProbe;
}
