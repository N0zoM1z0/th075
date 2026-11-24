#include "ScriptResource4205F0.hpp"
#include <deque>
#include <new>
#include <stddef.h>
#include <string.h>

void ScriptResource4205F0::Parse(char* data, unsigned int size) {
    unsigned int iByte = 0;
    unsigned int nOffset = 0;
    signed char mode = 0;
    short value16;
    while (iByte < size) {
        switch (mode) {
        case 0:
            if (data[iByte] == '#') {
                mode = 99;
                value16 = 0;
            } else if (data[iByte] == 'B') {
                value16 = 0;
                mode = 1;
            } else if (data[iByte] == 'P') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 0;
            } else if (data[iByte] == 'E') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 1;
            } else if (data[iByte] == 'N') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 2;
            } else if (data[iByte] == 'F') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 10;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'M') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 11;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'W') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 12;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'V') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 13;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'R') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().kind = 14;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == '(') {
                mode = 2;
                groups.back().records.back().value = -1;
            } else if (data[iByte] == '"') {
                mode = 3;
            }
            iByte++;
            nOffset = iByte;
            break;
        case 1:
            if (data[iByte] < '0' || data[iByte] > '9') {
                ScriptSequence421250 sequence;
                groups.push_back(sequence);
                groupIndex[value16] = static_cast<short>(groups.size() - 1);
                mode = 0;
                nOffset = iByte;
            } else {
                value16 = value16 * 10 + data[iByte] - '0';
                iByte++;
                nOffset = iByte;
            }
            break;
        case 2:
            if (data[iByte] == ')') {
                mode = 0;
            }
            else if (strncmp(data + iByte, "\x95\x81", 2) == 0) {
                groups.back().records.back().value = 0;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8c\x88", 2) == 0) {
                groups.back().records.back().value = 1;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xf0", 2) == 0) {
                groups.back().records.back().value = 2;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x97\x5d", 2) == 0) {
                groups.back().records.back().value = 3;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\x7b", 2) == 0) {
                groups.back().records.back().value = 4;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xbe", 2) == 0) {
                groups.back().records.back().value = 5;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x98\x66", 2) == 0) {
                groups.back().records.back().value = 6;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8b\xc1", 2) == 0) {
                groups.back().records.back().value = 7;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x95\x89", 2) == 0) {
                groups.back().records.back().value = 8;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x88\xea", 2) == 0) {
                groups.back().records.back().value = 9;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\xf1", 2) == 0) {
                groups.back().records.back().value = 10;
                iByte++;
            }
            iByte++;
            break;
        case 3:
            if (data[iByte] == '"') {
                groups.back().records.back().text = new char[iByte - nOffset + 1];
                char* text = groups.back().records.back().text;
                memcpy(text, data + nOffset, iByte - nOffset);
                text[iByte - nOffset] = 0;
                nOffset = iByte;
                mode = 0;
            }
            iByte++;
            break;
        case 4:
            if (data[iByte] < '0' || data[iByte] > '9') {
                groups.back().records.back().value = value16;
                mode = 0;
                nOffset = iByte;
            } else {
                value16 = value16 * 10 + data[iByte] - '0';
                iByte++;
                nOffset = iByte;
            }
            break;
        case 99:
            if (data[iByte] == '\n')
                mode = 0;
            iByte++;
            break;
        }
    }
}

ScriptRecord421200::ScriptRecord421200() {
    text = 0;
}

ScriptRecord421200::~ScriptRecord421200() {
    if (text)
        delete[] text;
}

ScriptSequence421250::ScriptSequence421250() {
    records.clear();
}

ScriptSequence421250::~ScriptSequence421250() {
    records.clear();
}
