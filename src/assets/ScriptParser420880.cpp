#include "assets/ScriptResource4205F0.hpp"
#include <deque>
#include <new>
#include <stddef.h>
#include <string.h>

namespace {
enum ParserState {
    ReadCommand = 0,
    ReadGroupNumber = 1,
    ReadPortrait = 2,
    ReadDialogue = 3,
    ReadArgument = 4,
    SkipComment = 99,
};
}

void ScriptResource4205F0::Parse(char* data, unsigned int size) {
    unsigned int iByte = 0;
    unsigned int nOffset = 0;
    signed char mode = ReadCommand;
    short value16;
    while (iByte < size) {
        switch (mode) {
        case ReadCommand:
            if (data[iByte] == '#') {
                mode = SkipComment;
                value16 = 0;
            } else if (data[iByte] == 'B') {
                value16 = 0;
                mode = ReadGroupNumber;
            } else if (data[iByte] == 'P') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::PlayerLine;
            } else if (data[iByte] == 'E') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::OpponentLine;
            } else if (data[iByte] == 'N') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::NarrationLine;
            } else if (data[iByte] == 'F') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::SetStageBanner;
                value16 = 0;
                mode = ReadArgument;
            } else if (data[iByte] == 'M') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::PlayTrack;
                value16 = 0;
                mode = ReadArgument;
            } else if (data[iByte] == 'W') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::SetQueuedMusicDelay;
                value16 = 0;
                mode = ReadArgument;
            } else if (data[iByte] == 'V') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::SetQueuedMusicTrack;
                value16 = 0;
                mode = ReadArgument;
            } else if (data[iByte] == 'R') {
                ScriptRecord421200 record;
                groups.back().records.push_back(record);
                groups.back().records.back().command = StoryCommand::SetDialogueSteps;
                value16 = 0;
                mode = ReadArgument;
            } else if (data[iByte] == '(') {
                mode = ReadPortrait;
                groups.back().records.back().argument = -1;
            } else if (data[iByte] == '"') {
                mode = ReadDialogue;
            }
            iByte++;
            nOffset = iByte;
            break;
        case ReadGroupNumber:
            if (data[iByte] < '0' || data[iByte] > '9') {
                ScriptSequence421250 sequence;
                groups.push_back(sequence);
                groupIndex[value16] = static_cast<short>(groups.size() - 1);
                mode = ReadCommand;
                nOffset = iByte;
            } else {
                value16 = value16 * 10 + data[iByte] - '0';
                iByte++;
                nOffset = iByte;
            }
            break;
        case ReadPortrait:
            if (data[iByte] == ')') {
                mode = ReadCommand;
            }
            else if (strncmp(data + iByte, "\x95\x81", 2) == 0) {
                groups.back().records.back().argument = 0;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8c\x88", 2) == 0) {
                groups.back().records.back().argument = 1;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xf0", 2) == 0) {
                groups.back().records.back().argument = 2;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x97\x5d", 2) == 0) {
                groups.back().records.back().argument = 3;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\x7b", 2) == 0) {
                groups.back().records.back().argument = 4;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xbe", 2) == 0) {
                groups.back().records.back().argument = 5;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x98\x66", 2) == 0) {
                groups.back().records.back().argument = 6;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8b\xc1", 2) == 0) {
                groups.back().records.back().argument = 7;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x95\x89", 2) == 0) {
                groups.back().records.back().argument = 8;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x88\xea", 2) == 0) {
                groups.back().records.back().argument = 9;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\xf1", 2) == 0) {
                groups.back().records.back().argument = 10;
                iByte++;
            }
            iByte++;
            break;
        case ReadDialogue:
            if (data[iByte] == '"') {
                groups.back().records.back().dialogue = new char[iByte - nOffset + 1];
                char* text = groups.back().records.back().dialogue;
                memcpy(text, data + nOffset, iByte - nOffset);
                text[iByte - nOffset] = 0;
                nOffset = iByte;
                mode = ReadCommand;
            }
            iByte++;
            break;
        case ReadArgument:
            if (data[iByte] < '0' || data[iByte] > '9') {
                groups.back().records.back().argument = value16;
                mode = ReadCommand;
                nOffset = iByte;
            } else {
                value16 = value16 * 10 + data[iByte] - '0';
                iByte++;
                nOffset = iByte;
            }
            break;
        case SkipComment:
            if (data[iByte] == '\n')
                mode = ReadCommand;
            iByte++;
            break;
        }
    }
}

ScriptRecord421200::ScriptRecord421200() {
    dialogue = 0;
}

ScriptRecord421200::~ScriptRecord421200() {
    if (dialogue)
        delete[] dialogue;
}

ScriptSequence421250::ScriptSequence421250() {
    records.clear();
}

ScriptSequence421250::~ScriptSequence421250() {
    records.clear();
}
