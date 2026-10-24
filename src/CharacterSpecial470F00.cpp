#include "GameLeafHelpers.hpp"

// Pointer-only actor view; full layouts and original role names are unknown.
// Never instantiate or embed this owner or its borrowed AnimationState.
class CharacterSpecial470F00 {
public:
    void ConfigureStage();
    void RecordRoundFields(signed char, short, signed char, signed char,
                           signed char, int, int, int);
};
namespace CameraStage470F00 {
    void __cdecl SetOverride(unsigned char, float, float, float);
    void __cdecl Snap();
}
extern signed char specialStage;
extern signed char stageDifficulty;
extern int stageTransitionCounter;
extern signed char stageTransitionMode;
extern signed char stageIntroCharacter;
#define ACTOR_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset))
#define OTHER_ACTOR ACTOR_FIELD(AnimationState*, 0x2E8)
#define OTHER_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(OTHER_ACTOR) + offset))

void CharacterSpecial470F00::ConfigureStage() {
    switch (specialStage) {
    case 1:
        OTHER_FIELD(int, 0x460) = 50000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        ACTOR_FIELD(unsigned char, 0x6E4) = 0;
        stageIntroCharacter = 1;
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty, 0, stageDifficulty * 25000 + 50000, 2400, (stageDifficulty * 25000 + 50000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 4, 1, stageDifficulty * 25000 + 50000, 2400, (stageDifficulty * 25000 + 50000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 2:
        OTHER_FIELD(int, 0x460) = 100000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        ACTOR_FIELD(unsigned char, 0x6E4) = 10;
        stageIntroCharacter = 13;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 8, 0, stageDifficulty * 50000 + 100000, 2400, (stageDifficulty * 50000 + 100000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 12, 1, stageDifficulty * 50000 + 100000, 2400, (stageDifficulty * 50000 + 100000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 3:
        OTHER_FIELD(int, 0x460) = 200000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        ACTOR_FIELD(unsigned char, 0x6E4) = 20;
        stageIntroCharacter = 0;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 16, 0, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        RecordRoundFields(3, 5000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 20, 1, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 24, 2, stageDifficulty * 75000 + 150000, 2400, (stageDifficulty * 75000 + 150000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 4:
        OTHER_FIELD(int, 0x460) = 400000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        ACTOR_FIELD(unsigned char, 0x6E4) = 30;
        stageIntroCharacter = 6;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 28, 0, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 32, 1, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 36, 2, stageDifficulty * 100000 + 200000, 2400, (stageDifficulty * 100000 + 200000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 5:
        OTHER_FIELD(int, 0x460) = 600000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        ACTOR_FIELD(unsigned char, 0x6E4) = 40;
        stageIntroCharacter = 6;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(6, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(5, 5000, 1, stageDifficulty + 40, 0, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(4, 5000, 2, stageDifficulty + 44, 1, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, stageDifficulty + 48, 2, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 52, 3, stageDifficulty * 150000 + 300000, 2400, (stageDifficulty * 150000 + 300000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 6:
        OTHER_FIELD(int, 0x460) = 800000;
        stageTransitionCounter = 0;
        stageTransitionMode = -1;
        ACTOR_FIELD(unsigned char, 0x6E4) = 50;
        stageIntroCharacter = 20;
        CameraStage470F00::SetOverride(1, 0.0f, 120.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 0.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(7, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(6, 5000, 1, stageDifficulty + 56, 0, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(5, 5000, 2, stageDifficulty + 60, 1, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(4, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(3, 5000, 1, stageDifficulty + 64, 2, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(2, 5000, 2, stageDifficulty + 68, 3, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        RecordRoundFields(1, 5000, 2, stageDifficulty + 72, 4, stageDifficulty * 200000 + 400000, 2400, (stageDifficulty * 200000 + 400000) / 2400);
        OTHER_FIELD(float, 0x44) = 1280.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 7:
        OTHER_FIELD(int, 0x460) = 1000000;
        ACTOR_FIELD(unsigned char, 0x6E4) = 60;
        stageIntroCharacter = 9;
        CameraStage470F00::SetOverride(1, 0.0f, 320.0f, 320.0f);
        CameraStage470F00::Snap();
        ACTOR_FIELD(float, 0x44) = 480.0f;
        ACTOR_FIELD(float, 0x48) = 0.0f;
        ACTOR_FIELD(unsigned char, 0xFF4) = 0;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(8, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(7, 5000, 1, stageDifficulty + 76, 0, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(6, 2500, 2, stageDifficulty + 80, 1, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(5, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, stageDifficulty + 84, 2, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(3, 5000, 2, stageDifficulty + 88, 3, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(2, 5000, 2, stageDifficulty + 92, 4, stageDifficulty * 250000 + 500000, 2400, (stageDifficulty * 250000 + 500000) / 2400);
        RecordRoundFields(1, 10000, 2, stageDifficulty + 96, 5, stageDifficulty * 250000 + 500000, 4800, (stageDifficulty * 250000 + 500000) / 4800);
        OTHER_FIELD(float, 0x44) = 800.0f;
        OTHER_ACTOR->ResetPrimaryCounters(0);
        break;
    case 8:
        ACTOR_FIELD(unsigned char, 0x6E4) = 70;
        ACTOR_FIELD(signed char, 0xFF4) = -1;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        break;
    case 9:
        ACTOR_FIELD(unsigned char, 0x6E4) = 80;
        ACTOR_FIELD(signed char, 0xFF4) = -1;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        break;
    case 10:
        ACTOR_FIELD(unsigned char, 0x6E4) = 90;
        ACTOR_FIELD(signed char, 0xFF4) = -1;
        ACTOR_FIELD(unsigned char, 0xFF5) = 0;
        ACTOR_FIELD(unsigned char, 0xFF6) = 0;
        ACTOR_FIELD(unsigned char, 0xFF7) = 0;
        break;
    }
}
