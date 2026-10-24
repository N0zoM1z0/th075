#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <vector>

// Complete physical sourceFile-backed packedValue. The two vector element declarations
// remain opaque; this function only constructs the externally defined owner.
struct PatternBox16;
struct PatternPrefix16 {
    short field0, field2, field4, field6;
    void* extension;
    BYTE simple;
    void ResetExtension();
};
class PatternFrame116 : public PatternPrefix16 {
public:
    PatternFrame116();
    ~PatternFrame116();
    short field16;
    float angle;
    short field24, field26, field28, field30, field32;
    short field34, field36, field38, field40, field42;
    float scale44, scale48;
    short field52, field54, field56;
    DWORD field60, field64;
    BYTE serialized68[16];
    std::vector<PatternBox16> firstBoxes, secondBoxes;
};
class PatternSequence20 {
public:
    PatternSequence20();
    ~PatternSequence20();
    void Clear();
    void Assign(unsigned int, const PatternFrame116&);
    PatternFrame116& At(unsigned int);
    std::vector<PatternFrame116> frames;
    short field16, field18;
};
typedef char PrefixSize[(sizeof(PatternPrefix16) == 16) ? 1 : -1];
typedef char FrameSize[(sizeof(PatternFrame116) == 116) ? 1 : -1];
typedef char SequenceSize[(sizeof(PatternSequence20) == 20) ? 1 : -1];
typedef char FrameFirst[(offsetof(PatternFrame116, firstBoxes) == 84) ? 1 : -1];
typedef char FrameSecond[(offsetof(PatternFrame116, secondBoxes) == 100) ? 1 : -1];
// Pointer-only interfaces; these are never instantiated.
class PatternSlots457660 {
public:
    unsigned int Size();
    PatternSequence20*& At(unsigned int);
    void Clear();
    void Assign(unsigned int, PatternSequence20* const&);
};
class PatternBoxWriter458A10 { public: void Append(const BYTE*); };
class ArchiveContext41D750 { public: HANDLE SeekNamedEntry(const char*); };
namespace ArchiveLookup41CF00 { ArchiveContext41D750* __cdecl Find(const char*); }
class FighterPattern457660 { public: void Load(); };
#define NAME (reinterpret_cast<const char*>(this) + 196)
#define SLOTS reinterpret_cast<PatternSlots457660*>(reinterpret_cast<char*>(this) + 1128)
#define FRAME (SLOTS->At(patternId)->At(index))
#define EXT_BYTE(off) (*reinterpret_cast<BYTE*>(reinterpret_cast<char*>(FRAME.extension) + (off)))
#define EXT_SHORT(off) (*reinterpret_cast<short*>(reinterpret_cast<char*>(FRAME.extension) + (off)))
#define EXT_FLOAT(off) (*reinterpret_cast<float*>(reinterpret_cast<char*>(FRAME.extension) + (off)))

void FighterPattern457660::Load() {
    unsigned int nRectangles;
    BYTE boxData[16];
    PatternFrame116 defaultFrame;
    unsigned int nBox;
    short packedValue;
    char szFilename[MAX_PATH];
    int frameTotal;
    char frameType;
    int index;
    unsigned int patternId;
    int count;
    HANDLE sourceFile;
    DWORD nRead;
    int iItem;

    sprintf(szFilename, "data\\character\\%s\\%s.pat", NAME, NAME);
    sourceFile = ArchiveLookup41CF00::Find("datab")->SeekNamedEntry(szFilename);
    for (patternId = 0; patternId < SLOTS->Size(); patternId++) {
        if (SLOTS->At(patternId)) {
            SLOTS->At(patternId)->Clear();
            delete SLOTS->At(patternId);
        }
    }
    SLOTS->Clear();
    ReadFile(sourceFile, &patternId, 4, &nRead, 0);
    SLOTS->Assign(patternId, 0);
    ReadFile(sourceFile, &count, 4, &nRead, 0);
    for (iItem = 0; iItem < count; iItem++) {
        ReadFile(sourceFile, &patternId, 4, &nRead, 0);
        if (!SLOTS->At(patternId))
            SLOTS->At(patternId) = new PatternSequence20;
        ReadFile(sourceFile, &SLOTS->At(patternId)->field16, 2, &nRead, 0);
        ReadFile(sourceFile, &SLOTS->At(patternId)->field18, 2, &nRead, 0);
        ReadFile(sourceFile, &frameTotal, 4, &nRead, 0);
        SLOTS->At(patternId)->Assign(frameTotal, defaultFrame);
        for (index = 0; index < frameTotal; index++) {
            ReadFile(sourceFile, &FRAME.field6, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field0, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field2, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field4, 2, &nRead, 0);
            ReadFile(sourceFile, &frameType, 1, &nRead, 0);
            if (frameType == 0) {
                FRAME.simple = 1;
            } else if (frameType == 1) {
                FRAME.simple = 0;
            } else if (frameType == 2) {
                FRAME.ResetExtension();
                ReadFile(sourceFile, &EXT_SHORT(0), 2, &nRead, 0);
                ReadFile(sourceFile, &EXT_BYTE(1), 1, &nRead, 0);
                ReadFile(sourceFile, &EXT_BYTE(2), 1, &nRead, 0);
                ReadFile(sourceFile, &EXT_BYTE(3), 1, &nRead, 0);
                ReadFile(sourceFile, &EXT_BYTE(4), 1, &nRead, 0);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXT_FLOAT(12) = packedValue * 0.01f;
                EXT_FLOAT(16) = packedValue * 0.01f;
                EXT_FLOAT(20) = packedValue * 0.01f;
                ReadFile(sourceFile, &EXT_SHORT(6), 2, &nRead, 0);
                ReadFile(sourceFile, &EXT_SHORT(8), 2, &nRead, 0);
                ReadFile(sourceFile, &EXT_SHORT(10), 2, &nRead, 0);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXT_FLOAT(24) = static_cast<float>(packedValue);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXT_FLOAT(28) = static_cast<float>(packedValue);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXT_FLOAT(32) = static_cast<float>(packedValue);
            }
            ReadFile(sourceFile, &FRAME.field16, 2, &nRead, 0);
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.angle = packedValue * 0.001f;
            ReadFile(sourceFile, &FRAME.field24, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field26, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field28, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field30, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field32, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field34, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field36, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field38, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field40, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field42, 2, &nRead, 0);
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.scale44 = packedValue * 0.01f;
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.scale48 = packedValue * 0.01f;
            ReadFile(sourceFile, &FRAME.field52, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field54, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field56, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field60, 4, &nRead, 0);
            ReadFile(sourceFile, &FRAME.field64, 4, &nRead, 0);
            ReadFile(sourceFile, FRAME.serialized68, 16, &nRead, 0);
            ReadFile(sourceFile, &nRectangles, 4, &nRead, 0);
            for (nBox = 0; nBox < nRectangles; nBox++) {
                ReadFile(sourceFile, boxData, 16, &nRead, 0);
                reinterpret_cast<PatternBoxWriter458A10*>(&FRAME.firstBoxes)->Append(boxData);
            }
            ReadFile(sourceFile, &nRectangles, 4, &nRead, 0);
            for (nBox = 0; nBox < nRectangles; nBox++) {
                ReadFile(sourceFile, boxData, 16, &nRead, 0);
                reinterpret_cast<PatternBoxWriter458A10*>(&FRAME.secondBoxes)->Append(boxData);
            }
        }
    }
}

#undef EXT_FLOAT
#undef EXT_SHORT
#undef EXT_BYTE
#undef FRAME
#undef SLOTS
#undef NAME
