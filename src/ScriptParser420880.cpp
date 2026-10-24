#include <deque>
#include <new>
#include <stddef.h>
#include <string.h>

// Complete source-compatible values from actual field widths, member lifetimes
// and container strides. Original names and grouping remain provisional.
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
    void Push(const ScriptRecord421200&);
    ScriptRecord421200& Back();
    std::deque<ScriptRecord421200> records;
};
typedef char RecordSize[(sizeof(ScriptRecord421200) == 8) ? 1 : -1];
typedef char RecordValueOffset[(offsetof(ScriptRecord421200, value) == 2) ? 1 : -1];
typedef char RecordTextOffset[(offsetof(ScriptRecord421200, text) == 4) ? 1 : -1];
typedef char SequenceSize[(sizeof(ScriptSequence421250) == 20) ? 1 : -1];
// Identical pointer-only owner interface to the accepted stream loaders.
class ScriptResource4205F0 {
public:
    void LoadArchive(const char*, const char*);
    void LoadFile(const char*, signed char, const char*);
    void Parse(char*, unsigned int);
};
class ScriptGroups4215F0 {
public:
    ScriptSequence421250& Back();
    void Push(const ScriptSequence421250&);
    unsigned int Size();
};
#define GROUPS reinterpret_cast<ScriptGroups4215F0*>(reinterpret_cast<char*>(this) + 2000)
#define LAST_RECORD (GROUPS->Back().Back())
#define GROUP_INDEX reinterpret_cast<short*>(this)

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
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 0;
            } else if (data[iByte] == 'E') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 1;
            } else if (data[iByte] == 'N') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 2;
            } else if (data[iByte] == 'F') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 10;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'M') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 11;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'W') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 12;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'V') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 13;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == 'R') {
                ScriptRecord421200 record;
                GROUPS->Back().Push(record);
                LAST_RECORD.kind = 14;
                value16 = 0;
                mode = 4;
            } else if (data[iByte] == '(') {
                mode = 2;
                LAST_RECORD.value = -1;
            } else if (data[iByte] == '"') {
                mode = 3;
            }
            iByte++;
            nOffset = iByte;
            break;
        case 1:
            if (data[iByte] < '0' || data[iByte] > '9') {
                ScriptSequence421250 sequence;
                GROUPS->Push(sequence);
                GROUP_INDEX[value16] = static_cast<short>(GROUPS->Size() - 1);
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
                LAST_RECORD.value = 0;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8c\x88", 2) == 0) {
                LAST_RECORD.value = 1;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xf0", 2) == 0) {
                LAST_RECORD.value = 2;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x97\x5d", 2) == 0) {
                LAST_RECORD.value = 3;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\x7b", 2) == 0) {
                LAST_RECORD.value = 4;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8a\xbe", 2) == 0) {
                LAST_RECORD.value = 5;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x98\x66", 2) == 0) {
                LAST_RECORD.value = 6;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x8b\xc1", 2) == 0) {
                LAST_RECORD.value = 7;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x95\x89", 2) == 0) {
                LAST_RECORD.value = 8;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x88\xea", 2) == 0) {
                LAST_RECORD.value = 9;
                iByte++;
            }
            else if (strncmp(data + iByte, "\x93\xf1", 2) == 0) {
                LAST_RECORD.value = 10;
                iByte++;
            }
            iByte++;
            break;
        case 3:
            if (data[iByte] == '"') {
                LAST_RECORD.text = new char[iByte - nOffset + 1];
                char* text = LAST_RECORD.text;
                memcpy(text, data + nOffset, iByte - nOffset);
                text[iByte - nOffset] = 0;
                nOffset = iByte;
                mode = 0;
            }
            iByte++;
            break;
        case 4:
            if (data[iByte] < '0' || data[iByte] > '9') {
                LAST_RECORD.value = value16;
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

#undef GROUP_INDEX
#undef LAST_RECORD
#undef GROUPS
