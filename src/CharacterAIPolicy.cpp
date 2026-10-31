#include "FighterCommandByteF940.hpp"
#include "FighterAIShortFieldsF946.hpp"
#include "CharacterAIPolicy.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + offset)
#define OPPONENT(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset)
#define OPPONENT_GUARD reinterpret_cast<FighterState *>(FIELD(void *, 0x2E8))->IsState50To149()
#define FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == 1))
#define AIR_FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == -1))
#define AIR_BACK_COMMAND (1 + (FIELD(signed char, 0x66) == -1))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation { float x, y; };

template<class Policy> void CharacterAIPolicy<Policy>::ChooseAction()
{
    AISeparation distance;
    distance.x = AbsFloatAt00412D90(OPPONENT_FLOAT(0x44) - FLOAT(0x44));
    distance.y = AbsFloatAt00412D90(OPPONENT_FLOAT(0x48) - FLOAT(0x48));
    --F946_AI_FIELDS_AT512(this).countdownAt512;
    if (FIELD(short, 0x60) > 49 && FIELD(short, 0x60) < 150) {
        F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        F946_AI_FIELDS_AT512(this).countdownAt512 = 0;
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 1) {
        if (F946_AI_FIELDS_AT512(this).countdownAt512 > 0) {
            FIELD(int, 0x4F0) = 5;
        } else {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        }
        return;
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 2) {
        if (FIELD(short, 0x60) == 391) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 3) {
        if (FIELD(short, 0x60) == 390) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 4) {
        if (FIELD(short, 0x60) == 392) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 5) {
        if (FIELD(short, 0x60) == 393) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 6) {
        if (F946_AI_FIELDS_AT512(this).countdownAt512 > 0) {
            FIELD(int, 0x4E8) = 5;
        } else {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        }
        return;
    }
    if (FLOAT(0x36C) > 300.0f) {
        if (distance.x > 560.0f &&
            rand() < 3 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (OPPONENT(short, 0x60) == 98 &&
            rand() < 20 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
    }
    if (FLOAT(0x36C) > 100.0f) {
        if (FIELD(short, 0x324) < 4000 &&
            distance.x > 560.0f &&
            rand() < 50 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (FIELD(short, 0x324) < 4000 &&
            rand() < 5 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (OPPONENT_GUARD &&
            FIELD(short, 0x324) < 3000 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
    }
    if ((FIELD(short, 0x60) > 399 && FIELD(short, 0x60) < 500) ||
        (FIELD(short, 0x60) > 599 && FIELD(short, 0x60) < 700)) {
        if (distance.x > 0.0f) {
            if (FLOAT(0x48) == 0.0f) {
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 3;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 4;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 5;
                    return;
                }
            }
            if (FLOAT(0x48) > 0.0f) {
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
                    return;
                }
            }
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 300.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 600.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 21;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 300.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 10;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 600.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 11;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 450.0f &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 300.0f &&
            distance.x < 700.0f &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if ((FIELD(short, 0x60) == 501 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 393) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, Policy::firstSelector) == 1 &&
            FIELD(signed char, 0x39D) == Policy::firstMode) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 500 || FIELD(short, 0x60) == 501 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 308 || FIELD(short, 0x60) == 307 || FIELD(short, 0x60) == 390 || FIELD(short, 0x60) == 392 || FIELD(short, 0x60) == 393) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, Policy::secondSelector) == 1 &&
            FIELD(signed char, 0x39D) == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 500 || FIELD(short, 0x60) == 501 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 310 || FIELD(short, 0x60) == 390 || FIELD(short, 0x60) == 393) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 2 &&
            FIELD(signed char, 0x39D) == 1) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 393 || FIELD(short, 0x60) == 392 || FIELD(short, 0x60) == 506 || FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308 || FIELD(short, 0x60) == 307) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, Policy::cancelSelector) == 2 &&
            FIELD(signed char, 0x39D) == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 393 || FIELD(short, 0x60) == 392 || FIELD(short, 0x60) == 506 || FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 303) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 0 &&
            FIELD(signed char, 0x39D) == 1) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 393 || FIELD(short, 0x60) == 392 || FIELD(short, 0x60) == 506 || FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 303) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, Policy::cancelSelector) == 0 &&
            FIELD(signed char, 0x39D) == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 250) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
            F946_AI_FIELDS_AT512(this).modeAt514 = 6;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 1000 &&
            FIELD(short, 0x3B0) > 500) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 40;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 41;
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 307 &&
            rand() < 5000 &&
            FIELD(short, 0x3B0) > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (distance.x < 200.0f &&
            (FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308) &&
            rand() < 20000) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (distance.x < 100.0f &&
            (FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308) &&
            rand() < 5000 &&
            FIELD(int, 0x7C) == 1) {
            F940_COMMAND_AT511(this) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 100) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 10000) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 15000) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 550) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 300) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            F940_COMMAND_AT511(this) = 30;
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 15000) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 4;
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 15000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 5000 &&
            FIELD(short, 0x3B0) > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 300) {
            F940_COMMAND_AT511(this) = 10;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.8f + 0.0f &&
        distance.x > 320.0f &&
        FIELD(short, 0x3B0) > 350) {
        F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
        F946_AI_FIELDS_AT512(this).modeAt514 = 1;
        FIELD(int, 0x4F0) = 1;
        if (rand() < 1000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 1000) FIELD(int, 0x4E0) = 1;
        return;
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 1.0f + 0.0f &&
        distance.x > 560.0f &&
        FIELD(short, 0x3B0) > 250 &&
        distance.y < 100.0f) {
        F946_AI_FIELDS_AT512(this).modeAt514 = 6;
        F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
        FIELD(int, 0x4E8) = 1;
        if (rand() < 2000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 2000) FIELD(int, 0x4E0) = 1;
        return;
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        FIELD(short, 0x3B0) > 250) {
        FIELD(int, 0x4EC) = 1;
        return;
    }
    if (rand() < 50) FIELD(int, 0x4E0) = -1;
    if (FLOAT(0x48) == 0.0f) {
        if (rand() < 1000) {
            F940_COMMAND_AT511(this) = 3;
            return;
        }
        if (rand() < 1000) {
            F940_COMMAND_AT511(this) = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 1000) {
            F940_COMMAND_AT511(this) = 5;
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f) {
        if (rand() < 1100) {
            F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1100) {
            F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
            return;
        }
    }
    if (distance.x > 120.0f &&
        rand() < 100) {
        FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 18000) FIELD(int, 0x4DC) = 0;
        FIELD(int, 0x4E0) = -1;
        return;
    }
    if (distance.x > 200.0f &&
        FLOAT(0x48) > 0.0f &&
        rand() < 80) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 350.0f &&
        FLOAT(0x48) == 0.0f &&
        rand() < 50) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 400.0f &&
        rand() < 100) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
        return;
    }
    if (FLOAT(0x48) == 0.0f && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if (distance.x < 80.0f &&
            rand() < 5000) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4E0) = rand() > 20000;
            if (OPPONENT_FLOAT(0x48) > 0.0f) FIELD(int, 0x4E0) = 0;
            return;
        }
        if (distance.x < 120.0f &&
            rand() < 2000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 0;
            return;
        }
        if (distance.x < 140.0f) {
            if (rand() < (distance.x > 0.0f && distance.x < 200.0f ? 1 : 0) * 900 + 100) {
                FIELD(int, 0x4EC) = 1;
                FIELD(int, 0x4E0) = 1;
                return;
            }
        }
        if (distance.x < 120.0f &&
            distance.x > 60.0f &&
            OPPONENT_FLOAT(0x48) == 0.0f &&
            rand() < 100) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x > 60.0f &&
            distance.x < 300.0f &&
            rand() < 400) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 600) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 500.0f &&
            rand() < 100) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 2;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 500.0f &&
            rand() < 600) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 4;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 500.0f &&
            rand() < 250) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if (distance.x < 300.0f &&
            rand() < 6000 &&
            distance.y < 200.0f &&
            distance.y > 0.0f) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (distance.x < 200.0f &&
            rand() < 4000 &&
            distance.y < 250.0f &&
            distance.y > 80.0f) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 0;
            return;
        }
    }
    if (rand() < 1500 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 2 &&
        FIELD(signed char, 0x39D) == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 1500 + 1000 &&
        distance.x < 350.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 1 &&
        FIELD(signed char, 0x39D) == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 1500 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 0 &&
        FIELD(signed char, 0x39D) == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 500 &&
        distance.x < 300.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, Policy::lateSelector) == 2 &&
        FIELD(signed char, 0x39D) == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 1500 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x398) == 0 &&
        FIELD(signed char, 0x39D) == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 1500 + 500 &&
        distance.x < 200.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x398) == 1 &&
        FIELD(signed char, 0x39D) == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x < 100.0f &&
        rand() < 600 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        F940_COMMAND_AT511(this) = 30;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 300.0f &&
        rand() < 200) {
        F940_COMMAND_AT511(this) = 100;
        return;
    }
    if (distance.x > 400.0f &&
        distance.x < 500.0f &&
        OPPONENT_FLOAT(0x48) == 0.0f &&
        rand() < 200) {
        F940_COMMAND_AT511(this) = 101;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        FIELD(short, 0x3B0) > 350) {
        F940_COMMAND_AT511(this) = 10;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        FIELD(short, 0x3B0) > 350) {
        F940_COMMAND_AT511(this) = 11;
        return;
    }
    if (rand() < 250 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        F940_COMMAND_AT511(this) = 40;
        return;
    }
    if (rand() < 100 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        F940_COMMAND_AT511(this) = 41;
        return;
    }
    if (distance.y < 250.0f &&
        distance.y > 100.0f &&
        distance.x < 200.0f &&
        rand() < 100 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        F940_COMMAND_AT511(this) = 31;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 200.0f &&
        static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.1f) {
        F940_COMMAND_AT511(this) = 20;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 400.0f &&
        static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.1f) {
        F940_COMMAND_AT511(this) = 21;
        return;
    }
    if (Policy::countdown > 0) {
        FIELD(int, 0x4DC) = 1;
        --Policy::countdown;
    } else if (Policy::countdown < 0) {
        FIELD(int, 0x4DC) = -1;
        ++Policy::countdown;
    } else {
        Policy::countdown = (rand() % 90 + 10) * (1 - 2 * (rand() % 2));
    }
}

template void CharacterAIPolicy<AI472890Policy>::ChooseAction();
template void CharacterAIPolicy<AI4E7DE0Policy>::ChooseAction();
template void CharacterAIPolicy<AI579650Policy>::ChooseAction();
template void CharacterAIPolicy<AI59D240Policy>::ChooseAction();
template void CharacterAIPolicy<AI5C5D10Policy>::ChooseAction();
template void CharacterAIPolicy<AI5E7370Policy>::ChooseAction();

