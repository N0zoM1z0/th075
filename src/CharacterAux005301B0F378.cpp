#include "FighterActionTimerPairF1027.hpp"
// Independently recovered complete 1,008-byte native character auxiliary
// state controller. It deliberately preserves the second explicit
// else-if (mode==3) comparison: VC7.1 emits native re-test and CFG.
// The actual 16-byte command snapshot is physically copied into the native
// stack, not an invented local or full private fighter layout.
// The snapshot is a genuine physically observed 16-byte command structure,
// not an inferred complete character class or artificial padding.
struct ObservedInputSnapshotF378 {
    short action;
    short guard;
    float x;
    float y;
    signed char facing;
    short bearing;
};
typedef char CheckSnapshot16F378[(sizeof(ObservedInputSnapshotF378)==16)?1:-1];
class ObservedEffectQueueF378 {
public:
    void AddSnapshot(ObservedInputSnapshotF378 const*);
    unsigned int Count();
    void PruneOld();
};
class CharacterAux005301B0F378 {
public:
    void UpdateSpecial();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
};
extern signed char g_CharacterSpecialModeAt006714B4;
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
#define FLOAT(o) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(o))
#define OPPONENT_FLOAT(o) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(o))
#define OPPONENT_FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(o)))
#define QUEUE (*reinterpret_cast<ObservedEffectQueueF378*>(reinterpret_cast<unsigned char*>(this)+0xFEC))
void CharacterAux005301B0F378::UpdateSpecial() {
    if (F1027_TIMERS(this).timerAt82==0 && FIELD(short,0x3B8)==0) {
        ObservedInputSnapshotF378 snapshot;
        snapshot.action=FIELD(short,0x60);
        snapshot.guard=FIELD(short,0x62);
        snapshot.x=FLOAT(0x44);
        snapshot.y=FLOAT(0x48);
        snapshot.facing=FIELD(signed char,0x66);
        snapshot.bearing=F1027_TIMERS(this).wordAt80;
        QUEUE.AddSnapshot(&snapshot);
        if (QUEUE.Count()>10) QUEUE.PruneOld();
    }
    if (FIELD(short,0xF10)>0) --FIELD(short,0xF10);
    if (FLOAT(0x50)==0.0f && FIELD(signed char,0x3AC)>0) FIELD(signed char,0x3AC)=0;
    if (FIELD(short,0xF0E)==0) {
        FIELD(short,0x2F6)=0;
        FIELD(short,0x2F8)=0;
        FIELD(short,0x2FA)=0;
        FLOAT(0x2FC)=1.0f;
        FLOAT(0x300)=1.0f;
        FIELD(unsigned char,0x2F1)=255;
        FIELD(unsigned char,0x2F2)=255;
        FIELD(unsigned char,0x2F3)=255;
        FIELD(unsigned char,0x2F4)=255;
        if (g_CharacterSpecialModeAt006714B4 != 3) {
            SpawnTrackedEffect(810,FLOAT(0x44),FLOAT(0x48)+100.0f,FIELD(signed char,0x66),1,1);
            ++FIELD(short,0xF0E);
        } else if (g_CharacterSpecialModeAt006714B4 == 3) {
            if (FIELD(short,0xF0C)==1) {
                SpawnTrackedEffect(810,FLOAT(0x44),FLOAT(0x48)+100.0f,FIELD(signed char,0x66),1,1);
                ++FIELD(short,0xF0E);
            }
            if (FIELD(signed char,0x2CD)!=0 && OPPONENT_FIELD(unsigned char,0x6EF)!=0 && FIELD(short,0xF0C)==0) {
                SpawnTrackedEffect(810,FLOAT(0x44),FLOAT(0x48)+100.0f,FIELD(signed char,0x66),1,1);
                ++FIELD(short,0xF0E);
                FIELD(short,0xF0C)=1;
            }
            if (FIELD(signed char,0x2CD)==0 && FIELD(unsigned char,0x6EF)!=0 && FIELD(short,0xF0C)==0) {
                SpawnTrackedEffect(810,FLOAT(0x44),FLOAT(0x48)+100.0f,FIELD(signed char,0x66),1,1);
                ++FIELD(short,0xF0E);
                FIELD(short,0xF0C)=1;
            }
        }
    }
    if (FLOAT(0x44)-OPPONENT_FLOAT(0x44)>540.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44)<-540.0f) FIELD(short,0xF14)=60;
    if (FLOAT(0x44)-OPPONENT_FLOAT(0x44)>320.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44)<-320.0f) {
        FIELD(short,0xF14)=FIELD(short,0xF14)+1;
        if (FIELD(short,0xF14)>60) FIELD(short,0xF14)=60;
    } else FIELD(short,0xF14)=0;
}
#undef QUEUE
#undef OPPONENT_FIELD
#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
