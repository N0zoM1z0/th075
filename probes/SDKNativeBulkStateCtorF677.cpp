// F677: entire native optimized 104-byte SDK-like constructor grammar.
// Original class name/SDK provenance UNKNOWN. Member offsets and actual
// zeroing ranges were read independently from pinned native original PE.
// Genuine VC7.1 /O1 /Oi; no copied native bytes, assembly or fake locals.
class SDKProbeE { public: SDKProbeE(); virtual void V(); };
#define F(off) (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this)+(off)))
extern "C" void* __cdecl memset(void*,int,unsigned int);
SDKProbeE::SDKProbeE() {
    F(4)=1;
    F(8)=0;
    F(0x20)=0;F(0x24)=0;F(0x28)=0;F(0x2c)=0;
    F(0x34)=0;F(0x30)=0;
    for(int i=0;i<2;++i){F(0x38+4*i)=0;F(0x40+4*i)=0;}
    memset(reinterpret_cast<char*>(this)+0x50,0,0x410);
    F(0x460)=0;F(0x470)=0;F(0x48c)=0;F(0x490)=0;F(0x468)=0;
}
#undef F
