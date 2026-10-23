#include "CharacterSequence4F44D0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset)
#define OPPONENT(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(FIELD(void *, 0x2E8)) + offset))
#define OPPONENT_ACTOR reinterpret_cast<CharacterSequence4F44D0 *>(FIELD(void *, 0x2E8))

void CharacterSequence4F44D0::AdvanceSequence()
{
    switch (FIELD(signed char, 0x6E4)) {
    case 0:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(100);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) == 230) {
            ResetPrimaryCounters(9);
            FLOAT(0x50) = 7.75f;
            FLOAT(0x54) = 18.0f;
            FLOAT(0x5C) = 0.6f;
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0x60) != 9 && FIELD(short, 0xEFC) > 230) FLOAT(0x44) = 480.0f;
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(1);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 1:
        InitializeNotice(0);
        SetNoticeMode(2);
        break;
    case 2:
        if (ProcessNotice()) SetNoticeMode(3);
        break;
    case 3:
        if (FIELD(short, 0xEFC) == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            OPPONENT(float, 0x50) = 7.75f;
            OPPONENT(float, 0x54) = 18.0f;
            OPPONENT(float, 0x5C) = 0.6f;
        }
        if (OPPONENT(short, 0x60) != 9) {
            OPPONENT(float, 0x44) = 800.0f;
            SetNoticeMode(4);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 4:
        InitializeNotice(1);
        SetNoticeMode(5);
        break;
    case 5:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(6);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 6:
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(2);
            SetNoticeMode(7);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 7:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(10);
            FIELD(unsigned char, 0x713) = 2;
        }
        break;
    case 10:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(101);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) == 230) {
            ResetPrimaryCounters(9);
            FLOAT(0x50) = 7.75f;
            FLOAT(0x54) = 18.0f;
            FLOAT(0x5C) = 0.6f;
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0x60) != 9 && FIELD(short, 0xEFC) > 230) FLOAT(0x44) = 480.0f;
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(11);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 11:
        InitializeNotice(3);
        SetNoticeMode(12);
        break;
    case 12:
        if (ProcessNotice()) SetNoticeMode(13);
        break;
    case 13:
        if (FIELD(short, 0xEFC) == 0) {
            OPPONENT_ACTOR->ResetPrimaryCounters(9);
            OPPONENT(float, 0x50) = 7.75f;
            OPPONENT(float, 0x54) = 18.0f;
            OPPONENT(float, 0x5C) = 0.6f;
        }
        if (OPPONENT(short, 0x60) != 9) {
            OPPONENT(float, 0x44) = 800.0f;
            SetNoticeMode(14);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 14:
        InitializeNotice(4);
        SetNoticeMode(15);
        break;
    case 15:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(16);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 16:
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(0, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(5);
            SetNoticeMode(17);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 17:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(20);
            FIELD(unsigned char, 0x713) = 3;
        }
        break;
    case 20:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(102);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(24);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 24:
        InitializeNotice(6);
        SetNoticeMode(25);
        break;
    case 25:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(26);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 26:
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(1, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(7);
            SetNoticeMode(27);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 27:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(30);
            FIELD(unsigned char, 0x713) = 4;
            ++g_SequenceCounterAt00671622;
        }
        break;
    case 30:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(103);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(34);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 34:
        InitializeNotice(8);
        SetNoticeMode(35);
        break;
    case 35:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(36);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 36:
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(9);
            SetNoticeMode(37);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 37:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(40);
            FIELD(unsigned char, 0x713) = 5;
        }
        break;
    case 40:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(104);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(44);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 44:
        InitializeNotice(10);
        SetNoticeMode(45);
        break;
    case 45:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(46);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 46:
        if (g_StateContinueCount < 3) {
            if (FIELD(short, 0xEFC) < 120) {
                ++FIELD(short, 0xEFC);
                break;
            }
            SetNoticeMode(70);
            FIELD(unsigned char, 0x713) = 8;
            FIELD(unsigned char, 0x6EF) = 1;
            break;
        }
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(2, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(11);
            SetNoticeMode(47);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 47:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(50);
            FIELD(unsigned char, 0x713) = 6;
        }
        break;
    case 50:
        SequenceCamera::SetOverride(1, 0.0f,
            (120.0f - (FIELD(short, 0xEFC) - 50) * 0.5f) * (FIELD(short, 0xEFC) < 291), 320.0f);
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            InitializeNotice(105);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 50) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
            if (g_StateFadeAlpha >= 5) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
        }
        if (FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 50 && FIELD(short, 0xEFC) <= 300) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) == 230) {
            ResetPrimaryCounters(9);
            FLOAT(0x50) = 7.75f;
            FLOAT(0x54) = 18.0f;
            FLOAT(0x5C) = 0.6f;
        }
        if (FIELD(short, 0xEFC) > 300) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0x60) != 9 && FIELD(short, 0xEFC) > 230) FLOAT(0x44) = 480.0f;
        if (FIELD(short, 0xEFC) > 360) {
            SetNoticeMode(51);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 51:
        InitializeNotice(12);
        SetNoticeMode(52);
        break;
    case 52:
        if (ProcessNotice()) {
            SetNoticeMode(53);
            ClearNoticeTransition();
            OPPONENT_ACTOR->ClearNoticeTransition();
            FIELD(short, 0xEFC) = 0;
        }
        break;
    case 53:
        g_StateResetCounter = 0xFFFFFF;
        if (FIELD(short, 0xEFC) < 30) ++FIELD(short, 0xEFC);
        if (FIELD(short, 0xEFC) == 30) {
            if (g_StateFadeAlpha < 240) g_StateFadeAlpha += 15;
            else g_StateFadeAlpha = 255;
            if (g_StateFadeAlpha == 255) FIELD(short, 0xEFC) = 31;
        }
        if (FIELD(short, 0xEFC) > 30 && FIELD(short, 0xEFC) < 90) {
            if (FIELD(short, 0xEFC) == 60) {
                ConfigureNoticeText(0);
                g_SequenceStageAt0067161D = 8;
                SequenceStage::Load();
                OPPONENT(float, 0x44) = 800.0f;
                OPPONENT_ACTOR->ResetPrimaryCounters(0);
                FLOAT(0x44) = 480.0f;
            }
            ++FIELD(short, 0xEFC);
        }
        if (FIELD(short, 0xEFC) == 90) {
            if (g_StateFadeAlpha > 4) g_StateFadeAlpha -= 5;
            else g_StateFadeAlpha = 0;
            if (g_StateFadeAlpha == 0) {
                FIELD(short, 0xEFC) = 0;
                SetNoticeMode(54);
            }
        }
        break;
    case 54:
        InitializeNotice(13);
        SetNoticeMode(55);
        break;
    case 55:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 30) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(56);
                FIELD(short, 0xEFC) = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 56:
        if (g_StateContinueCount < 3) {
            if (FIELD(short, 0xEFC) < 120) {
                ++FIELD(short, 0xEFC);
                break;
            }
            SetNoticeMode(80);
            FIELD(unsigned char, 0x713) = 9;
            FIELD(unsigned char, 0x6EF) = 1;
            break;
        }
        if (FIELD(short, 0xEFC) == 0) {
            BeginNoticeTransition(4, 1);
            OPPONENT_ACTOR->BeginNoticeTransition(8, 0);
        }
        if (FIELD(short, 0xEFC) == 30) {
            InitializeNotice(14);
            SetNoticeMode(57);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 57:
        if (ProcessNotice()) {
            FIELD(unsigned char, 0x6EF) = 1;
            SetNoticeMode(60);
            FIELD(unsigned char, 0x713) = 7;
        }
        break;
    case 60:
        if (FIELD(short, 0xEFC) == 0) {
            FLOAT(0xF18) = -192.0f;
            FLOAT(0xF40) = 160.0f;
            FLOAT(0xF1C) = -192.0f;
            FLOAT(0xF44) = 336.0f;
            FLOAT(0xF20) = 0.0f;
            FLOAT(0xF48) = 176.0f;
            FLOAT(0xF24) = 320.0f;
            FLOAT(0xF4C) = 280.0f;
            FIELD(short, 0xEFC) += 60;
            InitializeNotice(106);
            ConfigureNoticeText(0);
            ProcessNotice();
            ProcessNotice();
        }
        if (FIELD(short, 0xEFC) >= 160) {
            FLOAT(0xF18) += 0.25f;
            FLOAT(0xF1C) -= 0.25f;
        }
        if (FIELD(short, 0xEFC) >= 120 && FIELD(short, 0xEFC) <= 360) {
            if (FIELD(unsigned char, 0xFE2) < 250) FIELD(unsigned char, 0xFE2) += 5;
            else FIELD(unsigned char, 0xFE2) = 255;
        }
        if (FIELD(short, 0xEFC) >= 160 && FIELD(short, 0xEFC) <= 360) {
            if (FIELD(unsigned char, 0xFE1) < 250) {
                FIELD(unsigned char, 0xFE0) += 5;
                FIELD(unsigned char, 0xFE1) += 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 255;
                FIELD(unsigned char, 0xFE1) = 255;
            }
        }
        if (FIELD(short, 0xEFC) > 360) {
            if (FIELD(unsigned char, 0xFE0) >= 5) {
                FIELD(unsigned char, 0xFE0) -= 5;
                FIELD(unsigned char, 0xFE1) -= 5;
                FIELD(unsigned char, 0xFE2) -= 5;
            } else {
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 0;
            }
        }
        if (FIELD(short, 0xEFC) == 450) {
            SetNoticeMode(61);
            FIELD(short, 0xEFC) = 0;
            break;
        }
        ++FIELD(short, 0xEFC);
        break;
    case 61:
        SequenceCamera::SetOverride(1, 0.0f, 320 - FIELD(short, 0xEFC), 320.0f);
        FIELD(short, 0xEFC) = FIELD(short, 0xEFC) + 1;
        if (FIELD(short, 0xEFC) >= 320) {
            SetNoticeMode(62);
            FIELD(short, 0xEFC) = 0;
        }
        break;
    case 62:
        SequenceCamera::SetOverride(1, 0.0f, 0.0f, 320.0f);
        InitializeNotice(15);
        SetNoticeMode(63);
        break;
    case 63:
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                ClearNoticeTransition();
                OPPONENT_ACTOR->ClearNoticeTransition();
            }
            if (FIELD(short, 0xEFC) > 120) {
                FIELD(unsigned char, 0xFE3) = 0;
                FIELD(unsigned char, 0x6F8) = 0;
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
                SequenceCamera::SetOverride(0, 0.0f, 0.0f, 0.0f);
                SetNoticeMode(64);
                FIELD(short, 0xEFC) = 0;
                g_StateFadeAlpha = 0;
                break;
            }
            ++FIELD(short, 0xEFC);
        }
        break;
    case 64:
        g_StateResetCounter = 0xFFFFFF;
        if (g_StateFadeAlpha < 255) ++g_StateFadeAlpha;
        else {
            FIELD(unsigned char, 0x713) = 10;
            FIELD(unsigned char, 0x6EF) = 1;
        }
        break;
    case 70:
        FLOAT(0xF18) = 0.0f;
        FLOAT(0xF40) = 0.0f;
        FLOAT(0xF1C) = 0.0f;
        FLOAT(0xF44) = 0.0f;
        FLOAT(0xF20) = 0.0f;
        FLOAT(0xF48) = 0.0f;
        FLOAT(0xF24) = 0.0f;
        FLOAT(0xF4C) = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(107);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(71);
        break;
    case 71:
        if (FIELD(unsigned char, 0xFE0) < 251) FIELD(unsigned char, 0xFE0) += 5;
        else FIELD(unsigned char, 0xFE0) = 255;
        if (FIELD(unsigned char, 0xFE0) == 255) {
            SetNoticeMode(72);
            FIELD(short, 0xEFC) = 0;
        }
        break;
    case 72:
        InitializeNotice(20);
        SetNoticeMode(73);
        break;
    case 73:
        if (ProcessNotice()) {
            if (FIELD(unsigned char, 0xFE0) > 5) FIELD(unsigned char, 0xFE0) -= 5;
            else FIELD(unsigned char, 0xFE0) = 0;
            if (FIELD(unsigned char, 0xFE0) == 0) {
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
            }
        }
        break;
    case 80:
        FLOAT(0xF18) = 0.0f;
        FLOAT(0xF40) = 0.0f;
        FLOAT(0xF1C) = 0.0f;
        FLOAT(0xF44) = 0.0f;
        FLOAT(0xF20) = 0.0f;
        FLOAT(0xF48) = 0.0f;
        FLOAT(0xF24) = 0.0f;
        FLOAT(0xF4C) = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(108);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(81);
        break;
    case 81:
        if (FIELD(unsigned char, 0xFE0) < 251) FIELD(unsigned char, 0xFE0) += 5;
        else FIELD(unsigned char, 0xFE0) = 255;
        if (FIELD(unsigned char, 0xFE0) == 255) {
            SetNoticeMode(82);
            FIELD(short, 0xEFC) = 0;
        }
        break;
    case 82:
        InitializeNotice(21);
        SetNoticeMode(83);
        break;
    case 83:
        if (ProcessNotice()) {
            if (FIELD(unsigned char, 0xFE0) > 5) FIELD(unsigned char, 0xFE0) -= 5;
            else FIELD(unsigned char, 0xFE0) = 0;
            if (FIELD(unsigned char, 0xFE0) == 0) {
                ConfigureNoticeText(0);
                FIELD(unsigned char, 0x6EF) = 1;
            }
        }
        break;
    case 90:
        FLOAT(0xF18) = 0.0f;
        FLOAT(0xF40) = 0.0f;
        FLOAT(0xF1C) = 0.0f;
        FLOAT(0xF44) = 0.0f;
        FLOAT(0xF20) = 0.0f;
        FLOAT(0xF48) = 0.0f;
        FLOAT(0xF24) = 0.0f;
        FLOAT(0xF4C) = 0.0f;
        g_StateFadeAlpha = 0;
        InitializeNotice(109);
        ConfigureNoticeText(0);
        ProcessNotice();
        ProcessNotice();
        SetNoticeMode(91);
        break;
    case 91:
        SetNoticeMode(92);
        FIELD(short, 0xEFC) = 0;
        break;
    case 92:
        InitializeNotice(22);
        SetNoticeMode(93);
        FIELD(short, 0xEFC) = 0;
        break;
    case 93:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    FIELD(short, 0xEFC) = 1;
                }
            }
            if (FIELD(short, 0xEFC) == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                FIELD(unsigned char, 0xFE0) = 0;
                FIELD(unsigned char, 0xFE1) = 255;
                FIELD(short, 0xEFC) = 2;
            }
            if (FIELD(short, 0xEFC) == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    FIELD(short, 0xEFC) = 0;
                    SetNoticeMode(94);
                }
            }
        }
        break;
    case 94:
        InitializeNotice(23);
        SetNoticeMode(95);
        FIELD(short, 0xEFC) = 0;
        break;
    case 95:
        g_StateResetCounter = 0;
        if (ProcessNotice()) {
            if (FIELD(short, 0xEFC) == 0) {
                if (g_StateFadeAlpha < 250) g_StateFadeAlpha += 5;
                else {
                    g_StateFadeAlpha = 255;
                    FIELD(short, 0xEFC) = 1;
                }
            }
            if (FIELD(short, 0xEFC) == 1) {
                ConfigureNoticeText(0);
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render("", 120, 120, 255, 16, 1, false);
                FIELD(unsigned char, 0xFE1) = 0;
                FIELD(unsigned char, 0xFE2) = 255;
                FIELD(short, 0xEFC) = 2;
            }
            if (FIELD(short, 0xEFC) == 2) {
                if (g_StateFadeAlpha > 5) g_StateFadeAlpha -= 5;
                else {
                    g_StateFadeAlpha = 0;
                    FIELD(short, 0xEFC) = 0;
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
                if (FIELD(short, 0xEFC) == 0) {
                    SequenceAudio::Stop();
                    if (g_StateFadeAlpha < 252) g_StateFadeAlpha += 3;
                    else {
                        g_StateFadeAlpha = 255;
                        FIELD(short, 0xEFC) = 1;
                    }
                }
                if (FIELD(short, 0xEFC) > 0) ++FIELD(short, 0xEFC);
                if (FIELD(short, 0xEFC) > 60) {
                    ConfigureNoticeText(0);
                    FIELD(unsigned char, 0x6EF) = 1;
                }
            }
        }
        break;
    }
    if (FIELD(short, 0x6FA) == 0) {
        StateAudio::PlayTrack(FIELD(short, 0x6FC));
        StateAudio::TransitionFade();
    }
    if (FIELD(short, 0x6FA) >= 0) --FIELD(short, 0x6FA);
    AdvanceNoticeLevels();
    OPPONENT_ACTOR->AdvanceNoticeLevels();
}
