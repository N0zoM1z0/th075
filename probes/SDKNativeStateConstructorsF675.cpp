// Provisional native SDK state constructor grammar, no original class identity.
// Raw offsets are genuine observed state members, not fake stack padding.
class SDKProbeA {
public:
    SDKProbeA();
    virtual void Virtual();
};
class SDKProbeB {
public:
    SDKProbeB();
    virtual void Virtual();
};
class SDKProbeC {
public:
    SDKProbeC();
    virtual void Virtual();
};
class SDKProbeD {
public:
    SDKProbeD();
    virtual void Virtual();
};
#define SDK_FIELD(off) (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this)+(off)))
SDKProbeA::SDKProbeA() {SDK_FIELD(4)=1;SDK_FIELD(8)=0;SDK_FIELD(0x48)=0;SDK_FIELD(0x4C)=0;}
SDKProbeB::SDKProbeB() {SDK_FIELD(4)=1;SDK_FIELD(8)=0;SDK_FIELD(0xC)=0;SDK_FIELD(0x10)=0;SDK_FIELD(0x14)=0;}
SDKProbeC::SDKProbeC() {SDK_FIELD(4)=1;SDK_FIELD(8)=0;SDK_FIELD(0x20)=0;SDK_FIELD(0x24)=0;SDK_FIELD(0x28)=0;SDK_FIELD(0x2C)=0;SDK_FIELD(0x30)=0;SDK_FIELD(0x38)=0;}
SDKProbeD::SDKProbeD() {SDK_FIELD(0xC)&=0;SDK_FIELD(8)&=0;SDK_FIELD(4)=1;}
#undef SDK_FIELD
