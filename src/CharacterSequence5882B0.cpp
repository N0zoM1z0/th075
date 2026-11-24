#include "AudioControl.hpp"
#include "CharacterSequence5882B0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define OPPONENT_ACTOR static_cast<YuyukoFighter*>(opponent)

void YuyukoFighter::AdvanceSequence()
{
    switch (sequencePhase) {
    case 0:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(100);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer == 230) {
            ResetPrimaryCounters(9);
            velocityX = 7.75f;
            velocityY = 18.0f;
            field05C = 0.6f;
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (action != 9 && sequenceTimer > 230) x = 480.0f;
        if (sequenceTimer > 360) {
            SetNoticeMode(4);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 4:
        InitializeNotice(0);
        SetNoticeMode(5);
        break;
    case 5:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
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
            InitializeNotice(1);
            SetNoticeMode(7);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 7:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(10);
            field713 = 2;
        }
        break;
    case 10:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(101);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer == 230) {
            ResetPrimaryCounters(9);
            velocityX = 7.75f;
            velocityY = 18.0f;
            field05C = 0.6f;
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (action != 9 && sequenceTimer > 230) x = 480.0f;
        if (sequenceTimer > 360) {
            SetNoticeMode(14);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 14:
        InitializeNotice(2);
        SetNoticeMode(15);
        break;
    case 15:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(16);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 16:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(3, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(3);
            SetNoticeMode(17);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 17:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(20);
            field713 = 3;
        }
        break;
    case 20:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(102);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (sequenceTimer > 360) {
            SetNoticeMode(23);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 23:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.75f;
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
        InitializeNotice(4);
        SetNoticeMode(25);
        break;
    case 25:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(26);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 26:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(5);
            SetNoticeMode(27);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 27:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(30);
            field713 = 4;
            ++g_SequenceCounterAt00671622;
        }
        break;
    case 30:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(103);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer == 230) {
            ResetPrimaryCounters(9);
            velocityX = 7.75f;
            velocityY = 18.0f;
            field05C = 0.6f;
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (action != 9 && sequenceTimer > 230) x = 480.0f;
        if (sequenceTimer > 360) {
            SetNoticeMode(34);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 34:
        InitializeNotice(6);
        SetNoticeMode(35);
        break;
    case 35:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(36);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 36:
        if (sequenceTimer == 0) {
            BeginNoticeTransition(3, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(7);
            SetNoticeMode(37);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 37:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(40);
            field713 = 5;
        }
        break;
    case 40:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(104);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer == 230) {
            ResetPrimaryCounters(9);
            velocityX = 7.75f;
            velocityY = 18.0f;
            field05C = 0.6f;
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (action != 9 && sequenceTimer > 230) x = 480.0f;
        if (sequenceTimer > 360) {
            SetNoticeMode(43);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 43:
        if (sequenceTimer == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            opponent->velocityX = 7.8f;
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
        InitializeNotice(8);
        SetNoticeMode(45);
        break;
    case 45:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(46);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 46:
        if (g_StateContinueCount < 3) {
            if (sequenceTimer < 120) {
                ++sequenceTimer;
                break;
            }
            SetNoticeMode(70);
            field713 = 8;
            field6EF = 1;
            break;
        }
        if (sequenceTimer == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(9);
            SetNoticeMode(47);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 47:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(50);
            field713 = 6;
        }
        break;
    case 50:
        CameraMotionOverrideF484::SetOverride(1, 0.0f,
            (120.0f - (sequenceTimer - 50) * 0.5f) * (sequenceTimer < 291), 320.0f);
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            InitializeNotice(105);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 50) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (sequenceTimer <= 300) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 50 && sequenceTimer <= 300) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer == 230) {
            ResetPrimaryCounters(9);
            velocityX = 7.75f;
            velocityY = 18.0f;
            field05C = 0.6f;
        }
        if (sequenceTimer > 300) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
            }
        }
        if (action != 9 && sequenceTimer > 230) x = 480.0f;
        if (sequenceTimer > 360) {
            SetNoticeMode(51);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 51:
        InitializeNotice(10);
        SetNoticeMode(52);
        break;
    case 52:
        if (ProcessAction()) {
            SetNoticeMode(53);
            ClearNoticeTransition();
            OPPONENT_ACTOR->ClearNoticeTransition();
            sequenceTimer = 0;
        }
        break;
    case 53:
        g_StateResetCounter = 0xFFFFFF;
        if (sequenceTimer < 30) ++sequenceTimer;
        if (sequenceTimer == 30) {
            if (g_StateFadeAlpha < 240) g_StateFadeAlpha += 15;
            else g_StateFadeAlpha = 255;
            if (g_StateFadeAlpha == 255) sequenceTimer = 31;
        }
        if (sequenceTimer > 30 && sequenceTimer < 90) {
            if (sequenceTimer == 60) {
                ConfigureNoticeText(0);
                g_SequenceStageAt0067161D = 8;
                SequenceStage::Load();
                OPPONENT_ACTOR->ResetPrimaryCounters(0);
                opponent->x = 800.0f;
                x = 480.0f;
            }
            ++sequenceTimer;
        }
        if (sequenceTimer == 90) {
            if (g_StateFadeAlpha > 4) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
            if (g_StateFadeAlpha == 0) {
                sequenceTimer = 0;
                SetNoticeMode(54);
            }
        }
        break;
    case 54:
        InitializeNotice(11);
        SetNoticeMode(55);
        break;
    case 55:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 30) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(56);
                sequenceTimer = 0;
                break;
            }
            ++sequenceTimer;
        }
        break;
    case 56:
        if (g_StateContinueCount < 3) {
            if (sequenceTimer < 120) {
                ++sequenceTimer;
                break;
            }
            SetNoticeMode(80);
            field713 = 9;
            field6EF = 1;
            break;
        }
        if (sequenceTimer == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (sequenceTimer == 30) {
            InitializeNotice(12);
            SetNoticeMode(57);
            sequenceTimer = 0;
            break;
        }
        ++sequenceTimer;
        break;
    case 57:
        if (ProcessAction()) {
            field6EF = 1;
            SetNoticeMode(60);
            field713 = 7;
        }
        break;
    case 60:
        if (sequenceTimer == 0) {
            fieldF14 = -192.0f;
            fieldF3C = 160.0f;
            fieldF18 = -192.0f;
            fieldF40 = 336.0f;
            fieldF1C = 0.0f;
            fieldF44 = 176.0f;
            fieldF20 = 320.0f;
            fieldF48 = 280.0f;
            sequenceTimer += 60;
            InitializeNotice(106);
            ConfigureNoticeText(0);
            ProcessAction();
            ProcessAction();
        }
        if (sequenceTimer >= 160) {
            fieldF14 += 0.25f;
            fieldF18 -= 0.25f;
        }
        if (sequenceTimer >= 120 && sequenceTimer <= 360) {
            if (fieldFDE < 250) fieldFDE += 5;
            else fieldFDE = 255;
        }
        if (sequenceTimer >= 160 && sequenceTimer <= 360) {
            if (fieldFDD < 250) {
                fieldFDC += 5;
                fieldFDD += 5;
            } else {
                fieldFDC = 255;
                fieldFDD = 255;
            }
        }
        if (sequenceTimer > 360) {
            if (fieldFDC >= 5) {
                fieldFDC -= 5;
                fieldFDD -= 5;
                fieldFDE -= 5;
            } else {
                fieldFDC = 0;
                fieldFDD = 0;
                fieldFDE = 0;
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
        CameraMotionOverrideF484::SetOverride(1, 0.0f, 320 - sequenceTimer, 320.0f);
        sequenceTimer = sequenceTimer + 1;
        if (sequenceTimer >= 320) {
            SetNoticeMode(62);
            sequenceTimer = 0;
        }
        break;
    case 62:
        CameraMotionOverrideF484::SetOverride(1, 0.0f, 0.0f, 320.0f);
        InitializeNotice(13);
        SetNoticeMode(63);
        break;
    case 63:
        if (ProcessAction()) {
            if (sequenceTimer == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (sequenceTimer > 120) {
                fieldFDF = 0;
                field6F8 = 0;
                ConfigureNoticeText(0);
                field6EF = 1;
                CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
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
        fieldF14 = 0.0f;
        fieldF3C = 0.0f;
        fieldF18 = 0.0f;
        fieldF40 = 0.0f;
        fieldF1C = 0.0f;
        fieldF44 = 0.0f;
        fieldF20 = 0.0f;
        fieldF48 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(107);
        ConfigureNoticeText(0);
        ProcessAction();
        ProcessAction();
        SetNoticeMode(71);
        break;
    case 71:
        if (fieldFDC < 251) fieldFDC += 5;
        else fieldFDC = 255;
        if (fieldFDC == 255) {
            SetNoticeMode(72);
            sequenceTimer = 0;
        }
        break;
    case 72:
        InitializeNotice(20);
        SetNoticeMode(73);
        break;
    case 73:
        if (ProcessAction()) {
            if (fieldFDC > 5) fieldFDC -= 5;
            else fieldFDC = 0;
            if (fieldFDC == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 80:
        fieldF14 = 0.0f;
        fieldF3C = 0.0f;
        fieldF18 = 0.0f;
        fieldF40 = 0.0f;
        fieldF1C = 0.0f;
        fieldF44 = 0.0f;
        fieldF20 = 0.0f;
        fieldF48 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(108);
        ConfigureNoticeText(0);
        ProcessAction();
        ProcessAction();
        SetNoticeMode(81);
        break;
    case 81:
        if (fieldFDC < 251) fieldFDC += 5;
        else fieldFDC = 255;
        if (fieldFDC == 255) {
            SetNoticeMode(82);
            sequenceTimer = 0;
        }
        break;
    case 82:
        InitializeNotice(21);
        SetNoticeMode(83);
        break;
    case 83:
        if (ProcessAction()) {
            if (fieldFDC > 5) fieldFDC -= 5;
            else fieldFDC = 0;
            if (fieldFDC == 0) {
                ConfigureNoticeText(0);
                field6EF = 1;
            }
        }
        break;
    case 90:
        fieldF14 = 0.0f;
        fieldF3C = 0.0f;
        fieldF18 = 0.0f;
        fieldF40 = 0.0f;
        fieldF1C = 0.0f;
        fieldF44 = 0.0f;
        fieldF20 = 0.0f;
        fieldF48 = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(109);
        ConfigureNoticeText(0);
        ProcessAction();
        ProcessAction();
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
        if (ProcessAction()) {
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
                fieldFDC = 0;
                fieldFDD = 255;
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
        if (ProcessAction()) {
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
                fieldFDD = 0;
                fieldFDE = 255;
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
        if (ProcessAction()) {
            g_StateResetCounter = 0xFFFFFF;
            if (ProcessAction()) {
                if (sequenceTimer == 0) {
                    AudioControl407CA0::Stop();
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
        MusicF204::PlayTrackByIndex(field6FC);
        MusicF205::ScheduleTransitionFade();
    }
    if (field6FA >= 0) --field6FA;
    AdvanceNoticeLevels();
    OPPONENT_ACTOR->AdvanceNoticeLevels();
}
