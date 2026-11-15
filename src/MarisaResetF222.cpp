#include "MarisaFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
// Physical script-defined field view only: no complete owner allocation.
// R050 original x87: FILD dword stack signed index; FDIV dword [0x659308].
extern const float g_MarisaSequenceScaleAt00659308;
struct MarisaRecordF222 {
    unsigned int x,y,z;
    float alpha;
    unsigned int flags;
    float phase;
    float tail;
};
typedef char VerifyMarisaRecord28F222[(sizeof(MarisaRecordF222)==28)?1:-1];
#define REC(index) (reinterpret_cast<MarisaRecordF222*>(reinterpret_cast<unsigned char*>(this)+0x1018)[index])
void MarisaFighter::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldF08=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
    fieldEFA=0;
    fieldF32=0;
    reinterpret_cast<unsigned short&>(fieldF0C)=0;
    reinterpret_cast<unsigned short&>(fieldF0E)=0;
    fieldF10=0;
    fieldF12=0;
    fieldF14=0;
    fieldF16=0;
    fieldF18=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    fieldF1A=0;
    fieldF1C=0;
    fieldF1E=0;
    fieldF20=0;
    fieldF22=0;
    fieldF24=0;
    fieldF26=0;
    fieldF28=0;
    fieldF2A=0;
    fieldF2C=0;
    fieldF2E=0;
    fieldF30=0;
    field1006=0;
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
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}
#undef REC
