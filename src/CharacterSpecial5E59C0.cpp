#include "CharacterSpecial5E59C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define OPPONENT_ACTOR reinterpret_cast<StageOpponent5E59C0*>(opponent)

void CharacterSpecial5E59C0::InitializeStage() {
    switch (g_NoticeSelection) {
    case 1:
        opponent->field460 = 50000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        reinterpret_cast<unsigned char&>(sequencePhase) = 0;
        g_SequenceStageAt0067161D = 1;
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0, 0, g_StateRepeatLevelAt006714D0 * 25000 + 50000, 2400, (g_StateRepeatLevelAt006714D0 * 25000 + 50000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 4, 1, g_StateRepeatLevelAt006714D0 * 25000 + 50000, 2400, (g_StateRepeatLevelAt006714D0 * 25000 + 50000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 2:
        opponent->field460 = 100000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        reinterpret_cast<unsigned char&>(sequencePhase) = 10;
        g_SequenceStageAt0067161D = 13;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(3, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 8, 0, g_StateRepeatLevelAt006714D0 * 50000 + 100000, 2400, (g_StateRepeatLevelAt006714D0 * 50000 + 100000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 12, 1, g_StateRepeatLevelAt006714D0 * 50000 + 100000, 2400, (g_StateRepeatLevelAt006714D0 * 50000 + 100000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 3:
        opponent->field460 = 200000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        reinterpret_cast<unsigned char&>(sequencePhase) = 20;
        g_SequenceStageAt0067161D = 0;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 16, 0, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        RecordRoundFields(3, 5000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 20, 1, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 24, 2, g_StateRepeatLevelAt006714D0 * 75000 + 150000, 2400, (g_StateRepeatLevelAt006714D0 * 75000 + 150000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 4:
        opponent->field460 = 400000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        reinterpret_cast<unsigned char&>(sequencePhase) = 30;
        g_SequenceStageAt0067161D = 6;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(5, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 28, 0, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 32, 1, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 36, 2, g_StateRepeatLevelAt006714D0 * 100000 + 200000, 2400, (g_StateRepeatLevelAt006714D0 * 100000 + 200000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 5:
        opponent->field460 = 600000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        reinterpret_cast<unsigned char&>(sequencePhase) = 40;
        g_SequenceStageAt0067161D = 6;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(6, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(5, 5000, 1, g_StateRepeatLevelAt006714D0 + 40, 0, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(4, 5000, 2, g_StateRepeatLevelAt006714D0 + 44, 1, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(3, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(2, 5000, 1, g_StateRepeatLevelAt006714D0 + 48, 2, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 52, 3, g_StateRepeatLevelAt006714D0 * 150000 + 300000, 2400, (g_StateRepeatLevelAt006714D0 * 150000 + 300000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 6:
        opponent->field460 = 800000;
        g_StateResetCounter = 0;
        g_StateFadeAlpha = 255;
        reinterpret_cast<unsigned char&>(sequencePhase) = 50;
        g_SequenceStageAt0067161D = 20;
        SetCameraOverrideAt00412CC0(1, 0.0f, 120.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 0.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(7, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(6, 5000, 1, g_StateRepeatLevelAt006714D0 + 56, 0, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(5, 5000, 2, g_StateRepeatLevelAt006714D0 + 60, 1, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(4, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(3, 5000, 1, g_StateRepeatLevelAt006714D0 + 64, 2, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(2, 5000, 2, g_StateRepeatLevelAt006714D0 + 68, 3, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        RecordRoundFields(1, 5000, 2, g_StateRepeatLevelAt006714D0 + 72, 4, g_StateRepeatLevelAt006714D0 * 200000 + 400000, 2400, (g_StateRepeatLevelAt006714D0 * 200000 + 400000) / 2400);
        opponent->x = 1280.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 7:
        opponent->field460 = 1000000;
        reinterpret_cast<unsigned char&>(sequencePhase) = 60;
        g_SequenceStageAt0067161D = 9;
        SetCameraOverrideAt00412CC0(1, 0.0f, 320.0f, 320.0f);
        SnapCameraAt00412CF0();
        x = 480.0f;
        y = 0.0f;
        fieldFF4 = 0;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        RecordRoundFields(8, 4000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(7, 5000, 1, g_StateRepeatLevelAt006714D0 + 76, 0, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(6, 2500, 2, g_StateRepeatLevelAt006714D0 + 80, 1, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(5, 6000, 0, 0, 0, 0, 0, 0);
        RecordRoundFields(4, 5000, 1, g_StateRepeatLevelAt006714D0 + 84, 2, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(3, 5000, 2, g_StateRepeatLevelAt006714D0 + 88, 3, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(2, 5000, 2, g_StateRepeatLevelAt006714D0 + 92, 4, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 2400, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 2400);
        RecordRoundFields(1, 10000, 2, g_StateRepeatLevelAt006714D0 + 96, 5, g_StateRepeatLevelAt006714D0 * 250000 + 500000, 4800, (g_StateRepeatLevelAt006714D0 * 250000 + 500000) / 4800);
        opponent->x = 800.0f;
        OPPONENT_ACTOR->ResetPrimaryCounters(0);
        break;
    case 8:
        reinterpret_cast<unsigned char&>(sequencePhase) = 70;
        fieldFF4 = 255;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        break;
    case 9:
        reinterpret_cast<unsigned char&>(sequencePhase) = 80;
        fieldFF4 = 255;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
        break;
    case 10:
        reinterpret_cast<unsigned char&>(sequencePhase) = 90;
        fieldFF4 = 255;
        fieldFF5 = 0;
        fieldFF6 = 0;
        fieldFF7 = 0;
    }
}

#undef OPPONENT_ACTOR
#undef FIELD
