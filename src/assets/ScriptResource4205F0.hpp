#pragma once

#include <deque>
#include <stddef.h>

class ScriptRecord421200 {
public:
    ScriptRecord421200();
    ~ScriptRecord421200();
    unsigned char kind;
    short value;
    char* text;
};
class ScriptSequence421250 {
public:
    ScriptSequence421250();
    ~ScriptSequence421250();
    std::deque<ScriptRecord421200> records;
};
typedef char RecordSize[(sizeof(ScriptRecord421200) == 8) ? 1 : -1];
typedef char RecordValueOffset[(offsetof(ScriptRecord421200, value) == 2) ? 1 : -1];
typedef char RecordTextOffset[(offsetof(ScriptRecord421200, text) == 4) ? 1 : -1];
typedef char SequenceSize[(sizeof(ScriptSequence421250) == 20) ? 1 : -1];
class ScriptResource4205F0 {
public:
    ScriptResource4205F0();
    ~ScriptResource4205F0();
    void LoadArchive(const char* filename, const char* archive);
    void LoadFile(const char* filename, signed char mode, const char* output);
    void Parse(char* data, unsigned int size);
    short CountPatternEntries(short sequence);
    signed char GetByteField(short sequence, short entry);
    short GetWordField(short sequence, short entry);
    void* GetDwordField(short sequence, short entry);

private:
    short groupIndex[1000];
    std::deque<ScriptSequence421250> groups;
};

typedef char ScriptResourceSizeCheck[(sizeof(ScriptResource4205F0) == 0x7E4) ? 1 : -1];
