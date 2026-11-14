#include "CharacterSequence5AC250.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define OPPONENT_ACTOR static_cast<YukariFighter*>(opponent)

void YukariFighter::AdvanceSequence()
{
    switch (sequencePhase) {
    case 0:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(100);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(1);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 1:
        InitializeNotice(0);
        SetNoticeMode(2);
        break;
    case 2:
        if (ProcessNotice()) SetNoticeMode(3);
        break;
    case 3:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(4);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 4:
        InitializeNotice(1);
        SetNoticeMode(5);
        break;
    case 5:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(6);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 6:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(2);
            SetNoticeMode(7);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
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
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(101);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(11);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 11:
        InitializeNotice(3);
        SetNoticeMode(12);
        break;
    case 12:
        if (ProcessNotice()) SetNoticeMode(13);
        break;
    case 13:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(14);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 14:
        InitializeNotice(4);
        SetNoticeMode(15);
        break;
    case 15:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(16);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 16:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(2, 0);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 1);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(5);
            SetNoticeMode(17);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
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
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(102);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(21);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 21:
        InitializeNotice(6);
        SetNoticeMode(22);
        break;
    case 22:
        if (ProcessNotice()) SetNoticeMode(23);
        break;
    case 23:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.8f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(24);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 24:
        InitializeNotice(7);
        SetNoticeMode(25);
        break;
    case 25:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(26);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 26:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(8);
            SetNoticeMode(27);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
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
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(103);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(31);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 31:
        InitializeNotice(9);
        SetNoticeMode(32);
        break;
    case 32:
        if (ProcessNotice()) SetNoticeMode(33);
        break;
    case 33:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(34);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 34:
        InitializeNotice(10);
        SetNoticeMode(35);
        break;
    case 35:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(36);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 36:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(11);
            SetNoticeMode(37);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
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
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(104);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(41);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 41:
        InitializeNotice(12);
        SetNoticeMode(42);
        break;
    case 42:
        if (ProcessNotice()) {
            SetNoticeMode(43);
            OPPONENT_ACTOR->ClearNoticeTransition();
        }
        break;
    case 43:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(44);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 44:
        InitializeNotice(13);
        SetNoticeMode(45);
        break;
    case 45:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(46);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 46:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 1);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(14);
            SetNoticeMode(47);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
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
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            InitializeNotice(105);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 50) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(51);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 51:
        InitializeNotice(15);
        SetNoticeMode(52);
        break;
    case 52:
        if (ProcessNotice()) {
            SetNoticeMode(53);
        }
        break;
    case 53:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
            opponent->velocityY = 18.0f;
            opponent->field05C = 0.6f;
        }
        if (opponent->action != 9) {
            opponent->x = 800.0f;
            SetNoticeMode(54);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 54:
        InitializeNotice(16);
        SetNoticeMode(55);
        break;
    case 55:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(56);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 56:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(3, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(17);
            SetNoticeMode(57);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 57:
        if (ProcessNotice()) {
            field6EF = 1;
            field713 = 7;
        }
        break;
    case 60:
        if (sequenceTimer == 0) {
            fieldF34 = -192.0f;
            fieldF5C = 160.0f;
            fieldF38 = -192.0f;
            fieldF60 = 336.0f;
            fieldF3C = 0.0f;
            fieldF64 = 176.0f;
            fieldF40 = 320.0f;
            fieldF68 = 280.0f;
            sequenceTimer += 60;
            InitializeNotice(106);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (sequenceTimer >= 160) {
            fieldF34 += 0.25f;
            fieldF38 -= 0.25f;
        }
        if (sequenceTimer >= 120 && sequenceTimer <= 360) {
            if (fieldFFE < 250) fieldFFE += 5;
            else fieldFFE = 255;
        }
        if (sequenceTimer >= 160 && sequenceTimer <= 360) {
            if (fieldFFD < 250) {
                fieldFFC += 5;
                fieldFFD += 5;
            } else {
                fieldFFC = 255;
                fieldFFD = 255;
            }
        }
        if (sequenceTimer > 360) {
            if (fieldFFC >= 5) {
                fieldFFC -= 5;
                fieldFFD -= 5;
                fieldFFE -= 5;
            } else {
                fieldFFC = 0;
                fieldFFD = 0;
                fieldFFE = 0;
            }
        }
        if (sequenceTimer == 450) {
            SetNoticeMode(61);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 61:
        SequenceCamera::SetOverride(1, 0.0f, 320 - sequenceTimer, 320.0f);
        sequenceTimer = sequenceTimer + 1;
        if (sequenceTimer >= 320) {
            SetNoticeMode(62);
            sequenceTimer = 0;
        }
        break;
    case 62:
        SequenceCamera::SetOverride(1, 0.0f, 0.0f, 320.0f);
        InitializeNotice(18);
        SetNoticeMode(63);
        break;
    case 63:
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 120) {
                fieldFFF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(64);
                sequenceTimer = 0;
                g_StateFadeAlpha = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 64:
        g_StateResetCounter = 0xFFFFFF;
        if (g_StateFadeAlpha < 255) ++g_StateFadeAlpha;
        else {
            field713 = 10;
            field6EF = 1;
        }
        break;
    case 70:
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        fieldF3C = 0.0f;
        fieldF64 = 0.0f;
        fieldF40 = 0.0f;
        fieldF68 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(107);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(71);
        break;
    case 71:
        if (fieldFFC < 251) fieldFFC += 5;
        else fieldFFC = 255;
        if (fieldFFC == 255) {
            SetNoticeMode(72);
            sequenceTimer = 0;
        }
        break;
    case 72:
        InitializeNotice(20);
        SetNoticeMode(73);
        break;
    case 73:
        if (ProcessNotice()) {
            if (fieldFFC > 5) fieldFFC -= 5;
            else fieldFFC = 0;
            if (fieldFFC == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 80:
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        fieldF3C = 0.0f;
        fieldF64 = 0.0f;
        fieldF40 = 0.0f;
        fieldF68 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(108);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(81);
        break;
    case 81:
        if (fieldFFC < 251) fieldFFC += 5;
        else fieldFFC = 255;
        if (fieldFFC == 255) {
            SetNoticeMode(82);
            sequenceTimer = 0;
        }
        break;
    case 82:
        InitializeNotice(21);
        SetNoticeMode(83);
        break;
    case 83:
        if (ProcessNotice()) {
            if (fieldFFC > 5) fieldFFC -= 5;
            else fieldFFC = 0;
            if (fieldFFC == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 90:
        fieldF34 = 0.0f;
        fieldF5C = 0.0f;
        fieldF38 = 0.0f;
        fieldF60 = 0.0f;
        fieldF3C = 0.0f;
        fieldF64 = 0.0f;
        fieldF40 = 0.0f;
        fieldF68 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(109);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(91);
        break;
    case 91:
        SetNoticeMode(92);
        sequenceTimer = 0;
        break;
    case 92:
        InitializeNotice(22);
        SetNoticeMode(93);
        sequenceTimer = 0;
        break;
    case 93:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    sequenceTimer = 1;
                }
            }
            if (sequenceTimer == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                fieldFFC = 0;
                fieldFFD = 255;
                sequenceTimer = 2;
            }
            if (sequenceTimer == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    sequenceTimer = 0;
                    SetNoticeMode(94);
                }
            }
        }
        break;
    case 94:
        InitializeNotice(23);
        SetNoticeMode(95);
        sequenceTimer = 0;
        break;
    case 95:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (sequenceTimer == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    sequenceTimer = 1;
                }
            }
            if (sequenceTimer == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                fieldFFD = 0;
                fieldFFE = 255;
                sequenceTimer = 2;
            }
            if (sequenceTimer == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    sequenceTimer = 0;
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
                if (sequenceTimer == 0) {
                    SequenceAudio::Stop();
                    if (g_StateFadeAlpha < 252) g_StateFadeAlpha += 3;
                    else {
                        g_StateFadeAlpha = 255;
                        sequenceTimer = 1;
                    }
                }
                if (sequenceTimer > 0) ++sequenceTimer;
                if (sequenceTimer > 60) {
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
