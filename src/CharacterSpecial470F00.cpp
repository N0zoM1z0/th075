#include "ReimuFighter.hpp"
#include "GameLeafHelpers.hpp"

namespace CameraStage470F00 {
    void __cdecl SetOverride(unsigned char, float, float, float);
    void __cdecl Snap();
}
extern signed char specialStage;
extern signed char stageDifficulty;
extern int stageTransitionCounter;
extern signed char stageTransitionMode;
extern signed char stageIntroCharacter;

void ReimuFighter::ConfigureStage() {
    switch (specialStage) {
    case 1:
        opponent->field460 = 50000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        sequencePhase = 0;
        stageIntroCharacter = 1;
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty, 0, stageDifficulty * 25000 + 50000, 2400, (stageDifficulty * 25000 + 50000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 4, 1, stageDifficulty * 25000 + 50000, 2400, (stageDifficulty * 25000 + 50000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 2:
        opponent->field460 = 100000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        sequencePhase = 10;
        stageIntroCharacter = 13;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 8, 0, stageDifficulty * 50000 + 100000, 2400, (stageDifficulty * 50000 + 100000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 12, 1, stageDifficulty * 50000 + 100000, 2400, (stageDifficulty * 50000 + 100000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 3:
        opponent->field460 = 200000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        sequencePhase = 20;
        stageIntroCharacter = 0;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 16, 0, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        RecordRoundFields(3, 5000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 20, 1, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 24, 2, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 4:
        opponent->field460 = 400000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        sequencePhase = 30;
        stageIntroCharacter = 6;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 28, 0, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 32, 1, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 36, 2, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 5:
        opponent->field460 = 600000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        sequencePhase = 40;
        stageIntroCharacter = 6;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(6, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(5, 5000, 1, stageDifficulty + 40, 0, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(4, 5000, 2, stageDifficulty + 44, 1, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 48, 2, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 52, 3, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 6:
        opponent->field460 = 800000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        sequencePhase = 50;
        stageIntroCharacter = 20;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(7, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(6, 5000, 1, stageDifficulty + 56, 0, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(5, 5000, 2, stageDifficulty + 60, 1, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(4, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(3, 5000, 1, stageDifficulty + 64, 2, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(2, 5000, 2, stageDifficulty + 68, 3, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 72, 4, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        opponent->x = 1280.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 7:
        opponent->field460 = 1000000;
        sequencePhase = 60;
        stageIntroCharacter = 9;
        CameraStage470F00::SetOverride(1, 0.0f, 320.0f, 320.0f);
        CameraStage470F00::Snap();
        x = 480.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(8, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(7, 5000, 1, stageDifficulty + 76, 0, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(6, 2500, 2, stageDifficulty + 80, 1, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(5, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 84, 2, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(3, 5000, 2, stageDifficulty + 88, 3, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(2, 5000, 2, stageDifficulty + 92, 4, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(1, 10000, 2, stageDifficulty + 96, 5, stageDifficulty * 250000 + 500000, 4800, (stageDifficulty * 250000 + 500000) / 4800);
        opponent->x = 800.0f;
        opponent->ResetPrimaryCounters(0);
        break;
    case 8:
        sequencePhase = 70;
        fieldFF4 = -1;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        break;
    case 9:
        sequencePhase = 80;
        fieldFF4 = -1;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        break;
    case 10:
        sequencePhase = 90;
        fieldFF4 = -1;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        break;
    }
}
