// Synthetic VC7.1 inheritance probe. It establishes an emitted destructor
// shape without claiming any TH075 class layout or original C++ names.

struct BackgroundBaseProbe {
    virtual ~BackgroundBaseProbe();
};

BackgroundBaseProbe::~BackgroundBaseProbe() {}

struct BackgroundDerivedProbe : BackgroundBaseProbe {
    virtual ~BackgroundDerivedProbe();
};

BackgroundDerivedProbe::~BackgroundDerivedProbe() {}

extern "C" BackgroundBaseProbe *CreateBackgroundDerivedProbe() {
    return new BackgroundDerivedProbe;
}

struct BackgroundImplicitProbe : BackgroundBaseProbe {};

extern "C" BackgroundBaseProbe *CreateBackgroundImplicitProbe() {
    return new BackgroundImplicitProbe;
}
