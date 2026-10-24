#include <windows.h>
#include <mmsystem.h>
#include <new>

struct IDirectSoundBuffer8;
class ArchiveContextWithSize41D800 {
public:
    HANDLE Seek(const char*, DWORD*);
};
class ArchiveContextWithoutSize41D750 {
public:
    HANDLE Seek(const char*);
};
namespace SizedArchiveLookup41CF00 {
    ArchiveContextWithSize41D800* __cdecl Find(const char*);
}
namespace SoundArchiveLookup41CF00 {
    ArchiveContextWithoutSize41D750* __cdecl Find(const char*);
}
// Pointer-only owner interfaces; never instantiate or embed these incomplete
// owners. The only local structured value is the complete SDK WAVEFORMATEX.
class ScriptResource4205F0 {
public:
    void LoadArchive(const char*, const char*);
    void LoadFile(const char*, signed char, const char*);
    void Parse(char*, unsigned int);
};
class SoundArchive4076A0 {
public:
    void Load(const char*, const char*);
    unsigned int Size();
    void Assign(int, int);
    IDirectSoundBuffer8*& At(unsigned int);
};
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];

void ScriptResource4205F0::LoadArchive(const char* filename, const char* archive) {
    unsigned int iByte;
    BYTE decodeKey;
    char* data;
    DWORD size;
    DWORD readBytes;
    BYTE step;
    HANDLE sourceFile;
    sourceFile = SizedArchiveLookup41CF00::Find(archive)->Seek(filename, &size);
    if (sourceFile == INVALID_HANDLE_VALUE)
        return;
    data = new char[size];
    ReadFile(sourceFile, data, size, &readBytes, 0);
    decodeKey = 0x63;
    step = 0x62;
    for (iByte = 0; iByte < size; iByte++) {
        data[iByte] = data[iByte] ^ decodeKey;
        decodeKey += step;
        step += 0x42;
    }
    Parse(data, size);
    delete[] data;
}

void ScriptResource4205F0::LoadFile(const char* filename, signed char mode, const char* output) {
    DWORD size, actualBytes;
    HANDLE file;
    char* data;
    file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    size = GetFileSize(file, 0);
    data = new char[size];
    ReadFile(file, data, size, &actualBytes, 0);
    if (mode == 2) {
        BYTE key = 0x63;
        BYTE step = 0x62;
        for (unsigned int index = 0; index < size; index++) {
            data[index] = data[index] ^ key;
            key += step;
            step += 0x42;
        }
    }
    Parse(data, size);
    CloseHandle(file);
    if (mode == 1) {
        file = CreateFileA(output, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (file != INVALID_HANDLE_VALUE) {
            BYTE key = 0x63;
            BYTE step = 0x62;
            for (unsigned int index = 0; index < size; index++) {
                data[index] = data[index] ^ key;
                key += step;
                step += 0x42;
            }
            WriteFile(file, data, size, &actualBytes, 0);
            CloseHandle(file);
        }
    }
    delete[] data;
}

void SoundArchive4076A0::Load(const char* filename, const char* archive) {
    char* buffer;
    DWORD pcmBytes;
    BYTE entryPresent;
    WAVEFORMATEX format;
    int sampleCount = Size();
    int sampleIndex;
    HANDLE file;
    DWORD inputBytesRead;
    file = SoundArchiveLookup41CF00::Find(archive)->Seek(filename);
    if (file == INVALID_HANDLE_VALUE)
        return;
    ReadFile(file, &sampleCount, 4, &inputBytesRead, 0);
    Assign(sampleCount, 0);
    for (sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        ReadFile(file, &entryPresent, 1, &inputBytesRead, 0);
        if (entryPresent) {
            ReadFile(file, &pcmBytes, 4, &inputBytesRead, 0);
            ReadFile(file, &format, sizeof(format), &inputBytesRead, 0);
            buffer = new char[pcmBytes];
            ReadFile(file, buffer, pcmBytes, &inputBytesRead, 0);
            SoundCreation406A20::Create(&format, buffer, pcmBytes, &At(sampleIndex), 0);
            delete[] buffer;
        }
    }
}
