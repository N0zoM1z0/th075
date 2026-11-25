#pragma once

#include <deque>
#include <stddef.h>

// Parsed command values used by the story and victory-quote tables.
namespace StoryCommand {
enum Value {
    PlayerLine = 0,
    OpponentLine = 1,
    NarrationLine = 2,
    SetStageBanner = 10,
    PlayTrack = 11,
    SetQueuedMusicDelay = 12,
    SetQueuedMusicTrack = 13,
    SetDialogueSteps = 14,
    QuoteGroupEnd = SetQueuedMusicTrack,
};
}

class ScriptRecord421200 {
public:
    ScriptRecord421200();
    ~ScriptRecord421200();
    unsigned char command;
    short argument;
    char* dialogue;
};
class ScriptSequence421250 {
public:
    ScriptSequence421250();
    ~ScriptSequence421250();
    std::deque<ScriptRecord421200> records;
};
typedef char RecordSize[(sizeof(ScriptRecord421200) == 8) ? 1 : -1];
typedef char RecordArgumentOffset[(offsetof(ScriptRecord421200, argument) == 2) ? 1 : -1];
typedef char RecordDialogueOffset[(offsetof(ScriptRecord421200, dialogue) == 4) ? 1 : -1];
typedef char SequenceSize[(sizeof(ScriptSequence421250) == 20) ? 1 : -1];
class ScriptResource4205F0 {
public:
    ScriptResource4205F0();
    ~ScriptResource4205F0();
    void LoadArchive(const char* filename, const char* archive);
    void LoadFile(const char* filename, signed char mode, const char* output);
    void Parse(char* data, unsigned int size);
    short CountCommands(short sequence);
    signed char GetCommand(short sequence, short entry);
    short GetArgument(short sequence, short entry);
    char* GetDialogueText(short sequence, short entry);

private:
    short groupIndex[1000];
    std::deque<ScriptSequence421250> groups;
};

typedef char ScriptResourceSizeCheck[(sizeof(ScriptResource4205F0) == 0x7E4) ? 1 : -1];
