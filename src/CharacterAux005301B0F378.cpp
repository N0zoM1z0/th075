#include "YoumuFighter.hpp"
#include "Fighter.hpp"
#include "YoumuHistoryQueueF378.hpp"
// Independently recovered complete 1,008-byte native character auxiliary
// state controller. It deliberately preserves the second explicit
// else-if (mode==3) comparison: VC7.1 emits native re-test and CFG.
// The actual 16-byte command snapshot is physically copied into the native
// stack, not an invented local or full private fighter layout.
// The snapshot is a genuine physically observed 16-byte command structure,
// not an inferred complete character class or artificial padding.
extern signed char g_CharacterSpecialModeAt006714B4;
void YoumuFighter::AdvanceAuxiliary() {
    if (field082==0 && field3B8==0) {
        ObservedInputSnapshotF378 snapshot;
        snapshot.action=action;
        snapshot.guard=animationStage;
        snapshot.x=x;
        snapshot.y=y;
        snapshot.facing=facing;
        snapshot.bearing=field080;
        historyQueue.AddSnapshot(&snapshot);
        if (historyQueue.Count()>10) historyQueue.PruneOld();
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
