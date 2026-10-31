#include "FighterScriptCounterWindowF1022.hpp"
#include "FighterVirtualActionsF159.hpp"
// Physical script-defined field view only: no complete owner allocation.
// R050 original x87: FILD dword stack signed index; FDIV dword [0x659308].
extern const float g_MarisaSequenceScaleAt00659308;
class MarisaRoundF222 {public: void ResetRound();};
#define W(off) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define B(off) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+(off)))
struct MarisaRecordF222 {
    unsigned int x,y,z;
    float alpha;
    unsigned int flags;
    float phase;
    float tail;
};
typedef char VerifyMarisaRecord28F222[(sizeof(MarisaRecordF222)==28)?1:-1];
#define REC(index) (reinterpret_cast<MarisaRecordF222*>(reinterpret_cast<unsigned char*>(this)+0x1018)[index])
void MarisaRoundF222::ResetRound()
{
    F1022_SCRIPT(this).counterAtF00=0;
    F1022_SCRIPT(this).counterAtF02=0;
    W(0xf04)=0;
    W(0xf06)=0;
    W(0xf08)=0;
    W(0xf0a)=0;
    W(0xefc)=0;
    W(0xefe)=0;
    W(0xefa)=0;
    W(0xf32)=0;
    W(0xf0c)=0;
    W(0xf0e)=0;
    W(0xf10)=0;
    W(0xf12)=0;
    W(0xf14)=0;
    W(0xf16)=0;
    W(0xf18)=0;
    W(0x512)=0;
    W(0x514)=0;
    W(0x516)=0;
    W(0xf1a)=0;
    W(0xf1c)=0;
    W(0xf1e)=0;
    W(0xf20)=0;
    W(0xf22)=0;
    W(0xf24)=0;
    W(0xf26)=0;
    W(0xf28)=0;
    W(0xf2a)=0;
    W(0xf2c)=0;
    W(0xf2e)=0;
    W(0xf30)=0;
    B(0x1006)=0;
    for (int i=0;i<=36;++i) {
       REC(i*2).x=0;
       REC(i*2).y=0;
       REC(i*2).z=0;
       REC(i*2).alpha=1.0f;
       REC(i*2).flags=0xffffffffu;
       REC(i*2).phase=static_cast<float>(i)/g_MarisaSequenceScaleAt00659308;
       REC(i*2).tail=0;
       REC(i*2+1).x=0;
       REC(i*2+1).y=0;
       REC(i*2+1).z=0;
       REC(i*2+1).alpha=1.0f;
       REC(i*2+1).flags=0xffffffffu;
       REC(i*2+1).phase=static_cast<float>(i)/g_MarisaSequenceScaleAt00659308;
       REC(i*2+1).tail=1.0f;
    }
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
}
#undef REC
#undef B
#undef W
