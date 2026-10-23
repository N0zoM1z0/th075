#include "CharacterAICardPolicy.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + offset)
#define OPPONENT(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset)
#define OPPONENT_GUARD reinterpret_cast<FighterState *>(FIELD(void *, 0x2E8))->IsState50To149()
#define FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == 1))
#define AIR_FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == -1))
#define AIR_BACK_COMMAND (1 + (FIELD(signed char, 0x66) == -1))

#define CARD_TYPE FIELD(signed char, 0x370 + FIELD(signed char, 0x39D))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AICardSeparation { float x, y; };

template<class Policy> void CharacterAICardPolicy<Policy>::ChooseAction()
{
    AICardSeparation distance;
    distance.x = AbsFloatAt00412D90(OPPONENT_FLOAT(0x44) - FLOAT(0x44));
    distance.y = AbsFloatAt00412D90(OPPONENT_FLOAT(0x48) - FLOAT(0x48));
    --FIELD(short, 0x512);
    if (FIELD(short, 0x60) > 49 &&
        FIELD(short, 0x60) < 150) {
        if (FIELD(short, 0x516) < 0) FIELD(short, 0x516) = ChooseIntegerRange(30, 90);
        FIELD(short, 0x514) = 0;
        FIELD(short, 0x512) = 0;
        if (ChooseIntegerRange(0, 100) < 50) FIELD(int, 0x4DC) = 1;
        else FIELD(int, 0x4DC) = -1;
        if (ChooseIntegerRange(0, 100) < 5) FIELD(int, 0x4E8) = 1;
        return;
    }
    if (CARD_TYPE == 4 && FIELD(short, 0x3A0) > 0) {
        --FIELD(short, 0x516);
        if (ChooseIntegerRange(0, 100) < 10) {
            FIELD(u8, 0x511) = ChooseIntegerRange(0, 2) + 205;
            if (FLOAT(0x44) < 320.0f) {
                FIELD(u8, 0x511) = 205 + (FIELD(signed char, 0x66) == -1);
            }
            if (FLOAT(0x44) > 960.0f) {
                FIELD(u8, 0x511) = 206 - (FIELD(signed char, 0x66) == -1);
            }
            return;
        }
        return;
    }
    if (CARD_TYPE == 3 && FIELD(short, 0x3A0) > 0 && --FIELD(short, 0x516) <= 0) {
        FIELD(u8, 0x511) = 230;
    }
    if (CARD_TYPE == 2 && FIELD(short, 0x3A0) > 0) {
        --FIELD(short, 0x516);
        if (FIELD(short, 0x516) <= 0 && FLOAT(0x48) == 0.0f) {
            FIELD(u8, 0x511) = 210;
            return;
        }
        if (ChooseIntegerRange(0, 100) < 10) {
            FIELD(u8, 0x511) = (ChooseIntegerRange(0, 100) > 50) + 207;
            return;
        }
        FIELD(u8, 0x511) = (ChooseIntegerRange(0, 100) > 50) + 205;
        if (FLOAT(0x44) < 320.0f) {
            FIELD(u8, 0x511) = 205 + (FIELD(signed char, 0x66) == -1);
        }
        if (FLOAT(0x44) > 960.0f) {
            FIELD(u8, 0x511) = 206 - (FIELD(signed char, 0x66) == -1);
        }
        return;
    }
    if (CARD_TYPE == 1 && FIELD(short, 0x3A0) > 0 && --FIELD(short, 0x516) <= 0) {
        FIELD(u8, 0x511) = 220;
    }
    if (CARD_TYPE == 0 && FIELD(short, 0x3A0) > 0) {
        --FIELD(short, 0x516);
        if (FIELD(short, 0x516) <= 0) FIELD(u8, 0x511) = 200;
        if (ChooseIntegerRange(0, 100) < 2) {
            FIELD(u8, 0x511) = ChooseIntegerRange(0, 2) + 205;
            if (FLOAT(0x44) < 320.0f) {
                FIELD(u8, 0x511) = 205 + (FIELD(signed char, 0x66) == -1);
            }
            if (FLOAT(0x44) > 960.0f) {
                FIELD(u8, 0x511) = 206 - (FIELD(signed char, 0x66) == -1);
            }
            return;
        }
    }
    if (FIELD(short, 0x514) == 1) {
        if (FIELD(short, 0x512) > 0) {
            FIELD(int, 0x4F0) = 5;
        } else {
            FIELD(short, 0x514) = 0;
        }
        return;
    }
    if (FIELD(short, 0x514) == 2) {
        if (FIELD(short, 0x60) == 391) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 3) {
        if (FIELD(short, 0x60) == 390) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 4) {
        if (FIELD(short, 0x60) == 392) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 5) {
        if (FIELD(short, 0x60) == 393) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 6) {
        if (FIELD(short, 0x512) > 0) {
            FIELD(int, 0x4E8) = 5;
        } else {
            FIELD(short, 0x514) = 0;
        }
        return;
    }
    if ((FIELD(short, 0x60) > 399 && FIELD(short, 0x60) < 500) ||
        (FIELD(short, 0x60) > 599 && FIELD(short, 0x60) < 700)) {
        if (distance.x > 0.0f) {
            if (FLOAT(0x48) == 0.0f) {
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 3;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 4;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 5;
                    return;
                }
            }
            if (FLOAT(0x48) > 0.0f) {
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = AIR_BACK_COMMAND;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
                    return;
                }
            }
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 300.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 600.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            FIELD(u8, 0x511) = 21;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 300.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            FIELD(u8, 0x511) = 10;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 600.0f &&
            FIELD(short, 0x3B0) > 500 &&
            rand() < 100) {
            FIELD(u8, 0x511) = 11;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 450.0f &&
            rand() < 200) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 300.0f &&
            distance.x < 700.0f &&
            rand() < 100) {
            FIELD(u8, 0x511) = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if (FIELD(short, 0x60) == 307 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 250) {
            FIELD(short, 0x512) = ChooseIntegerRange(0, 45);
            FIELD(short, 0x514) = 6;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 1000 &&
            FIELD(short, 0x3B0) > 500) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 500) {
            FIELD(u8, 0x511) = 40;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 200) {
            FIELD(u8, 0x511) = 41;
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 307 &&
            rand() < 5000 &&
            FIELD(short, 0x3B0) > 300) {
            FIELD(short, 0x512) = ChooseIntegerRange(0, 30);
            FIELD(short, 0x514) = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (distance.x < 200.0f &&
            (FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308) &&
            rand() < 20000) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (distance.x < 100.0f &&
            (FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308) &&
            rand() < 5000 &&
            FIELD(int, 0x7C) == 1) {
            FIELD(u8, 0x511) = 31;
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
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 300) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (distance.x < 100.0f &&
            FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            FIELD(u8, 0x511) = 30;
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 200) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 200) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            FIELD(short, 0x514) = 3;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 1000) {
            FIELD(short, 0x514) = 5;
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
            FIELD(short, 0x514) = 3;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 1000) {
            FIELD(short, 0x514) = 5;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 1000) {
            FIELD(short, 0x514) = 4;
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
            FIELD(short, 0x512) = ChooseIntegerRange(0, 30);
            FIELD(short, 0x514) = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 300) {
            FIELD(short, 0x512) = ChooseIntegerRange(0, 30);
            FIELD(short, 0x514) = 1;
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 300) {
            FIELD(u8, 0x511) = 10;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 200) {
            FIELD(u8, 0x511) = 20;
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
        FIELD(short, 0x512) = ChooseIntegerRange(0, 45);
        FIELD(short, 0x514) = 1;
        FIELD(int, 0x4F0) = 1;
        if (rand() < 1000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 1000) FIELD(int, 0x4E0) = 1;
        return;
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 1.0f + 0.0f &&
        distance.x > 560.0f &&
        FIELD(short, 0x3B0) > 250 &&
        distance.y < 100.0f) {
        FIELD(short, 0x514) = 6;
        FIELD(short, 0x512) = ChooseIntegerRange(0, 45);
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
            FIELD(u8, 0x511) = 3;
            return;
        }
        if (rand() < 1000) {
            FIELD(u8, 0x511) = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 1000) {
            FIELD(u8, 0x511) = 5;
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f) {
        if (rand() < 1100) {
            FIELD(u8, 0x511) = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1100) {
            FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
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
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 350.0f &&
        FLOAT(0x48) == 0.0f &&
        rand() < 50) {
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 400.0f &&
        rand() < 100) {
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
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
            FIELD(short, 0x514) = 3;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 500.0f &&
            rand() < 100) {
            FIELD(short, 0x514) = 2;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 500.0f &&
            rand() < 600) {
            FIELD(short, 0x514) = 4;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 500.0f &&
            rand() < 250) {
            FIELD(short, 0x514) = 5;
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
    if (distance.y < 150.0f &&
        distance.x < 100.0f &&
        rand() < 600 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        FIELD(u8, 0x511) = 30;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 300.0f &&
        rand() < 200) {
        FIELD(u8, 0x511) = 100;
        return;
    }
    if (distance.x > 400.0f &&
        distance.x < 500.0f &&
        OPPONENT_FLOAT(0x48) == 0.0f &&
        rand() < 200) {
        FIELD(u8, 0x511) = 101;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        FIELD(short, 0x3B0) > 350) {
        FIELD(u8, 0x511) = 10;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        FIELD(short, 0x3B0) > 350) {
        FIELD(u8, 0x511) = 11;
        return;
    }
    if (rand() < 250 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        FIELD(u8, 0x511) = 40;
        return;
    }
    if (rand() < 100 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        FIELD(u8, 0x511) = 41;
        return;
    }
    if (distance.y < 250.0f &&
        distance.y > 100.0f &&
        distance.x < 200.0f &&
        rand() < 100 &&
        OPPONENT(short, 0x60) != 93 &&
        OPPONENT(short, 0x60) != 94) {
        FIELD(u8, 0x511) = 31;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 200.0f &&
        static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.1f) {
        FIELD(u8, 0x511) = 20;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 400.0f &&
        static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.1f) {
        FIELD(u8, 0x511) = 21;
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

template void CharacterAICardPolicy<AI474B40CardPolicy>::ChooseAction();
template void CharacterAICardPolicy<AI5E9620CardPolicy>::ChooseAction();
