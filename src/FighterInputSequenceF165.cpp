#include "FighterInputSequenceF165.hpp"
#include <deque>

// A complete vendor byte-compatible container view, not a private owner layout
// or proof of the original nominal element declaration.
#define HISTORY (*reinterpret_cast<std::deque<unsigned char>*>(reinterpret_cast<unsigned char*>(this) + 0x518))
#define FACING (*reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x66))

unsigned char FighterInputSequenceF165::MatchSequence(const char* text, signed char count, signed char historyOffset) {
    std::deque<unsigned char>::iterator current = HISTORY.end() + historyOffset;
    int index;
    {
        std::deque<unsigned char>::iterator last = HISTORY.end();
        unsigned char commands[20];

        for (index = 0; index < count; index++) {
            switch (text[index]) {
            case '1': commands[index] = 9; break;
            case '2': commands[index] = 8; break;
            case '3': commands[index] = 10; break;
            case '4': commands[index] = 1; break;
            case 'L':
                if (FACING > 0) commands[index] = 1;
                else commands[index] = 2;
                break;
            case '5':
            case 'N': commands[index] = 0; break;
            case '6': commands[index] = 2; break;
            case 'R':
                if (FACING > 0) commands[index] = 2;
                else commands[index] = 1;
                break;
            case '7': commands[index] = 5; break;
            case '8': commands[index] = 4; break;
            case '9': commands[index] = 6; break;
            case 'A': commands[index] = 0x10; break;
            case 'B': commands[index] = 0x20; break;
            case 'C': commands[index] = 0x40; break;
            case 'D': commands[index] = 0x80; break;
            case 'X': commands[index] = 0xF0; break;
            }
        }

        index = 0;
        for (; current != last; current++) {
            if (commands[index] < 0x10) {
                if ((*current & 0x0F) == commands[index] && ++index == count) return 1;
            } else if (commands[index] != 0xF0) {
                if ((*current & 0xF0) == commands[index] && ++index == count) return 1;
            } else {
                if ((*current & 0xF0) != 0 && ++index == count) {
                    if (*current & 0x10) return 1;
                    if (*current & 0x20) return 2;
                    if (*current & 0x40) return 3;
                    if (*current & 0x80) return 4;
                }
            }
        }
    }
    return 0;
}

#undef FACING
#undef HISTORY
