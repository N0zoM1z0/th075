#include "CharacterSequence5D4890.hpp"

#define OPPONENT_ACTOR static_cast<CharacterSequence5D4890*>(opponent)

void CharacterSequence5D4890::AdvanceSequence()
{
    switch (sequencePhase) {
    case 0:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(100);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 == 230) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (opponent->action != 9 && fieldF28 > 230) opponent->x = 800.0f;
        if (fieldF28 > 360) {
            SetNoticeMode(4);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 4:
        InitializeNotice(0);
        SetNoticeMode(5);
        break;
    case 5:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(6);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 6:
        if (fieldF28 == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(1);
            SetNoticeMode(7);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 7:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(10);
            field713 = 2;
        }
        break;
    case 10:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(101);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 == 230) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (opponent->action != 9 && fieldF28 > 230) opponent->x = 800.0f;
        if (fieldF28 > 360) {
            SetNoticeMode(14);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 14:
        InitializeNotice(2);
        SetNoticeMode(15);
        break;
    case 15:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(16);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 16:
        if (fieldF28 == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(3);
            SetNoticeMode(17);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 17:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(20);
            field713 = 3;
        }
        break;
    case 20:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(102);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 == 230) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (opponent->action != 9 && fieldF28 > 230) opponent->x = 800.0f;
        if (fieldF28 > 360) {
            SetNoticeMode(24);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 24:
        InitializeNotice(4);
        SetNoticeMode(25);
        break;
    case 25:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(26);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 26:
        if (fieldF28 == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(5);
            SetNoticeMode(27);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 27:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(30);
            field713 = 4;
            ++g_SequenceCounterAt00671622;
        }
        break;
    case 30:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(103);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 == 230) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (opponent->action != 9 && fieldF28 > 230) opponent->x = 800.0f;
        if (fieldF28 > 360) {
            SetNoticeMode(34);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 34:
        InitializeNotice(6);
        SetNoticeMode(35);
        break;
    case 35:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(36);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 36:
        if (fieldF28 == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(7);
            SetNoticeMode(37);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 37:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(40);
            field713 = 5;
        }
        break;
    case 40:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(104);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (fieldF28 > 360) {
            SetNoticeMode(41);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 41:
        InitializeNotice(8);
        SetNoticeMode(42);
        break;
    case 42:
        if (ProcessNotice()) {
            SetNoticeMode(43);
            OPPONENT_ACTOR->ClearNoticeTransition();
        }
        break;
    case 43:
        if (fieldF28 == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(44);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 44:
        InitializeNotice(9);
        SetNoticeMode(45);
        break;
    case 45:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(46);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 46:
        if (fieldF28 == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(10);
            SetNoticeMode(47);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 47:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(50);
            field713 = 6;
        }
        break;
    case 50:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (fieldF28 - 50) * 0.5f) * (fieldF28 < 291), 320.0f);
        if (fieldF28 == 0) {
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            InitializeNotice(105);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (fieldF28 >= 50) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (fieldF28 <= 300) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 50 && fieldF28 <= 300) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 > 300) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (fieldF28 > 360) {
            SetNoticeMode(51);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 51:
        InitializeNotice(11);
        SetNoticeMode(52);
        break;
    case 52:
        if (ProcessNotice()) {
            SetNoticeMode(53);
            OPPONENT_ACTOR->ClearNoticeTransition();
        }
        break;
    case 53:
        if (fieldF28 == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(54);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 54:
        InitializeNotice(12);
        SetNoticeMode(55);
        break;
    case 55:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 30) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(56);
                fieldF28 = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 56:
        if (fieldF28 == 0) {
            BeginNoticeTransition(3, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (fieldF28 == 30) {
            InitializeNotice(13);
            SetNoticeMode(57);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 57:
        if (ProcessNotice()) {
            field6EF = 1;
            SetNoticeMode(60);
            field713 = 7;
        }
        break;
    case 60:
        if (fieldF28 == 0) {
            InitializeNotice(106);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
            fieldF2C = -192.0f;
            fieldF54 = 160.0f;
            fieldF30 = -192.0f;
            fieldF58 = 336.0f;
            fieldF34 = 0.0f;
            fieldF5C = 176.0f;
            fieldF38 = 320.0f;
            fieldF60 = 280.0f;
            fieldF28 += 60;
        }
        if (fieldF28 >= 160) {
            fieldF2C += 0.25f;
            fieldF30 -= 0.25f;
        }
        if (fieldF28 >= 120 && fieldF28 <= 360) {
            if (fieldFF6 < 250) fieldFF6 += 5;
            else fieldFF6 = 255;
        }
        if (fieldF28 >= 160 && fieldF28 <= 360) {
            if (fieldFF5 < 250) {
                fieldFF4 += 5;
                fieldFF5 += 5;
            } else {
                fieldFF4 = 255;
                fieldFF5 = 255;
            }
        }
        if (fieldF28 > 360) {
            if (fieldFF4 >= 5) {
                fieldFF4 -= 5;
                fieldFF5 -= 5;
                fieldFF6 -= 5;
            } else {
                fieldFF4 = 0;
                fieldFF5 = 0;
                fieldFF6 = 0;
            }
        }
        if (fieldF28 == 450) {
            SetNoticeMode(61);
            fieldF28 = 0;
            break;
        }
        ++fieldF28;
        break;
    case 61:
        SequenceCamera::SetOverride(1, 0.0f, 320 - fieldF28, 320.0f);
        fieldF28 = fieldF28 + 1;
        if (fieldF28 >= 320) {
            SetNoticeMode(62);
            fieldF28 = 0;
        }
        break;
    case 62:
        SequenceCamera::SetOverride(1, 0.0f, 0.0f, 320.0f);
        InitializeNotice(14);
        SetNoticeMode(63);
        break;
    case 63:
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (fieldF28 > 120) {
                fieldFF7 = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(64);
                fieldF28 = 0;
                g_StateFadeAlpha = 0;
                break;
            }
            ++fieldF28;
        }
        break;
    case 64:
        g_StateResetCounter = 0xFFFFFF;
        if (g_SequenceByteAt0066C239 > 0) --g_SequenceByteAt0066C239;
        if (g_SequenceByteAt0066C23A > 0) --g_SequenceByteAt0066C23A;
        if (g_StateFadeAlpha < 255) ++g_StateFadeAlpha;
        else {
            field713 = 10;
            field6EF = 1;
        }
        break;
    case 70:
        fieldF2C = 0.0f;
        fieldF54 = 0.0f;
        fieldF30 = 0.0f;
        fieldF58 = 0.0f;
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(107);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(71);
        break;
    case 71:
        if (fieldFF4 < 251) fieldFF4 += 5;
        else fieldFF4 = 255;
        if (fieldFF4 == 255) {
            SetNoticeMode(72);
            fieldF28 = 0;
        }
        break;
    case 72:
        InitializeNotice(20);
        SetNoticeMode(73);
        break;
    case 73:
        if (ProcessNotice()) {
            if (fieldFF4 > 5) fieldFF4 -= 5;
            else fieldFF4 = 0;
            if (fieldFF4 == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 80:
        fieldF2C = 0.0f;
        fieldF54 = 0.0f;
        fieldF30 = 0.0f;
        fieldF58 = 0.0f;
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(108);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(81);
        break;
    case 81:
        if (fieldFF4 < 251) fieldFF4 += 5;
        else fieldFF4 = 255;
        if (fieldFF4 == 255) {
            SetNoticeMode(82);
            fieldF28 = 0;
        }
        break;
    case 82:
        InitializeNotice(21);
        SetNoticeMode(83);
        break;
    case 83:
        if (ProcessNotice()) {
            if (fieldFF4 > 5) fieldFF4 -= 5;
            else fieldFF4 = 0;
            if (fieldFF4 == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 90:
        fieldF2C = 0.0f;
        fieldF54 = 0.0f;
        fieldF30 = 0.0f;
        fieldF58 = 0.0f;
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(109);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(91);
        break;
    case 91:
        SetNoticeMode(92);
        fieldF28 = 0;
        break;
    case 92:
        InitializeNotice(22);
        SetNoticeMode(93);
        fieldF28 = 0;
        break;
    case 93:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    fieldF28 = 1;
                }
            }
            if (fieldF28 == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                fieldFF4 = 0;
                fieldFF5 = 255;
                fieldF28 = 2;
            }
            if (fieldF28 == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    fieldF28 = 0;
                    SetNoticeMode(94);
                }
            }
        }
        break;
    case 94:
        InitializeNotice(23);
        SetNoticeMode(95);
        fieldF28 = 0;
        break;
    case 95:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (fieldF28 == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    fieldF28 = 1;
                }
            }
            if (fieldF28 == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                fieldFF5 = 0;
                fieldFF6 = 255;
                fieldF28 = 2;
            }
            if (fieldF28 == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    fieldF28 = 0;
                    SetNoticeMode(96);
                }
            }
        }
        break;
    case 96:
        InitializeNotice(24);
        SetNoticeMode(97);
        break;
    case 97:
        if (ProcessNotice()) {
            g_StateResetCounter = 0xFFFFFF;
            if (ProcessNotice()) {
                if (fieldF28 == 0) {
                    SequenceAudio::Stop();
                    if (g_StateFadeAlpha < 252) g_StateFadeAlpha += 3;
                    else {
                        g_StateFadeAlpha = 255;
                        fieldF28 = 1;
                    }
                }
                if (fieldF28 > 0) ++fieldF28;
                if (fieldF28 > 60) {
                    ConfigureNoticeText(0);
                    field6EF = 1;
                }
            }
        }
        break;
    }
    if (field6FA == 0) {
        StateAudio::PlayTrack(field6FC);
        StateAudio::TransitionFade();
    }
    if (field6FA >= 0) --field6FA;
    AdvanceNoticeLevels();
    OPPONENT_ACTOR->AdvanceNoticeLevels();
}
