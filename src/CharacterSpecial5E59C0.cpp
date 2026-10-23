#include "CharacterSpecial5E59C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset)))
#define OPPONENT_ACTOR reinterpret_cast<StageOpponent5E59C0*>(FIELD(void*, 0x2E8))

void CharacterSpecial5E59C0::InitializeStage() {
    switch (g_NoticeSelection) {
    case 1:
        OPPONENT(int, 0x460) = 50000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        FIELD(unsigned char, 0x6E4) = 0;
        g_SequenceStageAt0067161D = 1;
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0, 0, g_StateRepeatLevelAt006714D0 * 25000 + 50000, 2400, (g_StateRepeatLevelAt006714D0 * 25000 + 50000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 4, 1, g_StateRepeatLevelAt006714D0 * 25000 + 50000, 2400, (g_StateRepeatLevelAt006714D0 * 25000 + 50000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 2:
        OPPONENT(int, 0x460) = 100000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        FIELD(unsigned char, 0x6E4) = 10;
        g_SequenceStageAt0067161D = 13;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 8, 0, g_StateRepeatLevelAt006714D0 * 50000 + 100000, 2400, (g_StateRepeatLevelAt006714D0 * 50000 + 100000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 12, 1, g_StateRepeatLevelAt006714D0 * 50000 + 100000, 2400, (g_StateRepeatLevelAt006714D0 * 50000 + 100000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 3:
        OPPONENT(int, 0x460) = 200000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        FIELD(unsigned char, 0x6E4) = 20;
        g_SequenceStageAt0067161D = 0;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 16, 0, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        RecordRoundFields(3, 5000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 20, 1, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 24, 2, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 4:
        OPPONENT(int, 0x460) = 400000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        FIELD(unsigned char, 0x6E4) = 30;
        g_SequenceStageAt0067161D = 6;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 28, 0, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 32, 1, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 36, 2, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 5:
        OPPONENT(int, 0x460) = 600000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        FIELD(unsigned char, 0x6E4) = 40;
        g_SequenceStageAt0067161D = 6;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(6, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(5, 5000, 1, g_StateRepeatLevelAt006714D0 + 40, 0, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(4, 5000, 2, g_StateRepeatLevelAt006714D0 + 44, 1, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 48, 2, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 52, 3, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 6:
        OPPONENT(int, 0x460) = 800000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        FIELD(unsigned char, 0x6E4) = 50;
        g_SequenceStageAt0067161D = 20;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 0.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(7, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(6, 5000, 1, g_StateRepeatLevelAt006714D0 + 56, 0, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(5, 5000, 2, g_StateRepeatLevelAt006714D0 + 60, 1, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(4, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(3, 5000, 1, g_StateRepeatLevelAt006714D0 + 64, 2, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(2, 5000, 2, g_StateRepeatLevelAt006714D0 + 68, 3, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 72, 4, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        OPPONENT(float, 0x44) = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 7:
        OPPONENT(int, 0x460) = 1000000;
        FIELD(unsigned char, 0x6E4) = 60;
        g_SequenceStageAt0067161D = 9;
        SetCameraOverrideAt00412CC0(1, 0.0f, 320.0f, 320.0f);
        SnapCameraAt00412CF0();
        FLOAT(0x44) = 480.0f;
        FLOAT(0x48) = 0.0f;
        FIELD(unsigned char, 0xFF4) = 0;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        RecordRoundFields(8, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(7, 5000, 1, g_StateRepeatLevelAt006714D0 + 76, 0, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(6, 2500, 2, g_StateRepeatLevelAt006714D0 + 80, 1, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(5, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 84, 2, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(3, 5000, 2, g_StateRepeatLevelAt006714D0 + 88, 3, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(2, 5000, 2, g_StateRepeatLevelAt006714D0 + 92, 4, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(1, 10000, 2, g_StateRepeatLevelAt006714D0 + 96, 5, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 4800, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 4800);
        OPPONENT(float, 0x44) = 800.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 8:
        FIELD(unsigned char, 0x6E4) = 70;
        FIELD(unsigned char, 0xFF4) = 255;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        break;
    case 9:
        FIELD(unsigned char, 0x6E4) = 80;
        FIELD(unsigned char, 0xFF4) = 255;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
        break;
    case 10:
        FIELD(unsigned char, 0x6E4) = 90;
        FIELD(unsigned char, 0xFF4) = 255;
        FIELD(unsigned char, 0xFF5) = 0;
        FIELD(unsigned char, 0xFF6) = 0;
        FIELD(unsigned char, 0xFF7) = 0;
    }
}

#undef OPPONENT_ACTOR
#undef OPPONENT
#undef FLOAT
#undef FIELD
