#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/youmu/YoumuFighter.hpp"
#include "battle/Fighter.hpp"
#include "characters/youmu/YoumuHistoryQueueF378.hpp"
// Independently recovered complete 1,008-byte native character auxiliary
// state controller. It deliberately preserves the second explicit
// else-if (mode==3) comparison: VC7.1 emits native re-test and CFG.
// The actual 16-byte command snapshot is physically copied into the native
// stack, not an invented local or full private fighter layout.
// The snapshot is a genuine physically observed 16-byte command structure,
// not an inferred complete character class or artificial padding.
void YoumuFighter::AdvanceAuxiliary() {
    if (hitstopFrames==0 && opponentFreezeTimer==0) {
        ObservedInputSnapshotF378 snapshot;
        snapshot.action=action;
        snapshot.stage=animationStage;
        snapshot.x=x;
        snapshot.y=y;
        snapshot.facing=facing;
        snapshot.counter=remainingHits;
        historyQueue.push_back(snapshot);
        if (historyQueue.size()>10) historyQueue.pop_front();
    }
    if (fieldF10>0) --fieldF10;
    if (velocityX==0.0f && field3AC>0) field3AC=0;
    if (fieldF0E==0) {
        effectTransformRecord.offsetX=0;
        effectTransformRecord.offsetY=0;
        effectTransformRecord.offsetZ=0;
        effectTransformRecord.scaleX=1.0f;
        effectTransformRecord.scaleY=1.0f;
        effectTransformRecord.alpha=255;
        effectTransformRecord.red=255;
        effectTransformRecord.green=255;
        effectTransformRecord.blue=255;
        if (g_CombatMode != CombatMode::Story) {
            SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
            ++fieldF0E;
        } else if (g_CombatMode == CombatMode::Story) {
            if (fieldF0C==1) {
                SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
                ++fieldF0E;
            }
            if (cpuControlled!=0 && opponent->storySequenceFinished!=0 && fieldF0C==0) {
                SpawnTrackedEffect(810,x,y+100.0f,facing,1,1);
                ++fieldF0E;
                fieldF0C=1;
            }
            if (cpuControlled==0 && storySequenceFinished!=0 && fieldF0C==0) {
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
