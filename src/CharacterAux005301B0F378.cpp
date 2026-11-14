#include "Fighter.hpp"
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
class CharacterAux005301B0F378 : public Fighter {
public:
    void UpdateSpecial();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
public:
    // Character-specific fields after the shared Fighter layout.
    short fieldF10;
    unsigned char unknownF12[0xF14 - 0xF12];
    short fieldF14;
};
extern signed char g_CharacterSpecialModeAt006714B4;
#define QUEUE (*reinterpret_cast<ObservedEffectQueueF378*>(reinterpret_cast<unsigned char*>(this)+0xFEC))
void CharacterAux005301B0F378::UpdateSpecial() {
    if (F1027_TIMERS(this).timerAt82==0 && field3B8==0) {
        ObservedInputSnapshotF378 snapshot;
        snapshot.action=action;
        snapshot.guard=field062;
        snapshot.x=x;
        snapshot.y=y;
        snapshot.facing=facing;
        snapshot.bearing=F1027_TIMERS(this).wordAt80;
        QUEUE.AddSnapshot(&snapshot);
        if (QUEUE.Count()>10) QUEUE.PruneOld();
    }
    if (fieldF10>0) --fieldF10;
    if (velocityX==0.0f && field3AC>0) field3AC=0;
    if (fieldF0E==0) {
        field2F6=0;
        field2F8=0;
        field2FA=0;
        field2FC=1.0f;
        field300=1.0f;
        field2F1=255;
        field2F2=255;
        field2F3=255;
        field2F4=255;
        if (g_CharacterSpecialModeAt006714B4 != 3) {
            SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
            ++fieldF0E;
        } else if (g_CharacterSpecialModeAt006714B4 == 3) {
            if (fieldF0C==1) {
                SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
                ++fieldF0E;
            }
            if (field2CD!=0 && opponent->field6EF!=0 && fieldF0C==0) {
                SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
                ++fieldF0E;
                fieldF0C=1;
            }
            if (field2CD==0 && field6EF!=0 && fieldF0C==0) {
                SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
                ++fieldF0E;
                fieldF0C=1;
            }
        }
    }
    if (x-opponent->x>540.0f || x-opponent->x<-540.0f) fieldF14=60;
    if (x-opponent->x>320.0f || x-opponent->x<-320.0f) {
        fieldF14=fieldF14+1;
        if (fieldF14>60) fieldF14=60;
    } else fieldF14=0;
}
#undef QUEUE
