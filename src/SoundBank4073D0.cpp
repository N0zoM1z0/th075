#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <new>
#include <stdio.h>

// Pointer-only partial interface. Never instantiate or embed this owner.
class SoundBank4073D0 {
public:
    void LoadWaveDirectory(const char*, unsigned int);
    void LoadSerializedFile(const char*);
    void SaveSerializedFile(const char*);
    unsigned int Size();
    IDirectSoundBuffer8*& At(unsigned int);
    IDirectSoundBuffer8*& Unchecked(unsigned int);
    void Assign(unsigned int, IDirectSoundBuffer8* const&);
    void AssignIntegral(int, int);
    void ClearStorage();
};
namespace SharedWave406820 {
    bool __cdecl Load(const char*, IDirectSoundBuffer8**, DWORD);
}
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
#define BANK_COUNT (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 16))
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];
typedef char SoundCapsSize[(sizeof(DSBCAPS) == 20) ? 1 : -1];

void SoundBank4073D0::LoadWaveDirectory(const char* path, unsigned int count) {
    char filename[MAX_PATH];
    unsigned int i;
    HANDLE handle;
    BANK_COUNT = count;
    for (i = 0; i < Size(); i++) {
        if (Unchecked(i)) {
            Unchecked(i)->Release();
            Unchecked(i) = 0;
        }
    }
    ClearStorage();
    Assign(BANK_COUNT, 0);
    for (i = 0; i < count; i++) {
        sprintf(filename, "%s\\%03d.wav", path, static_cast<int>(i));
        handle = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
            SharedWave406820::Load(filename, &At(i), 0);
        }
    }
}

void SoundBank4073D0::LoadSerializedFile(const char* filename) {
    char* buffer;
    DWORD pcmBytes;
    BYTE entryPresent;
    WAVEFORMATEX format;
    int sampleCount = Size();
    int sampleIndex;
    HANDLE file;
    DWORD inputBytesRead;
    file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    ReadFile(file, &sampleCount, 4, &inputBytesRead, 0);
    AssignIntegral(sampleCount, 0);
    for (sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        ReadFile(file, &entryPresent, 1, &inputBytesRead, 0);
        if (entryPresent) {
            ReadFile(file, &pcmBytes, 4, &inputBytesRead, 0);
            ReadFile(file, &format, sizeof(format), &inputBytesRead, 0);
            buffer = new char[pcmBytes];
            ReadFile(file, buffer, pcmBytes, &inputBytesRead, 0);
            SoundCreation406A20::Create(&format, buffer, pcmBytes, &Unchecked(sampleIndex), 0);
            delete[] buffer;
        }
    }
    CloseHandle(file);
}

void SoundBank4073D0::SaveSerializedFile(const char* filename) {
    int sampleCount = Size();
    int sampleIndex;
    HANDLE file;
    DWORD nWritten;
    WAVEFORMATEX format;
    DSBCAPS bufferCaps;
    void* firstBuffer;
    DWORD size1;
    DWORD size2;
    void* pSecondRegion;
    BYTE samplePresent;
    file = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    WriteFile(file, &sampleCount, 4, &nWritten, 0);
    for (sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        if (Unchecked(sampleIndex)) {
            samplePresent = 1;
            WriteFile(file, &samplePresent, 1, &nWritten, 0);
            bufferCaps.dwSize = sizeof(bufferCaps);
            // Native code captures this SDK result without testing it.
            HRESULT result = Unchecked(sampleIndex)->GetCaps(&bufferCaps);
            WriteFile(file, &bufferCaps.dwBufferBytes, 4, &nWritten, 0);
            Unchecked(sampleIndex)->GetFormat(&format, sizeof(format), 0);
            WriteFile(file, &format, sizeof(format), &nWritten, 0);
            Unchecked(sampleIndex)->Lock(0, bufferCaps.dwBufferBytes, &firstBuffer, &size1,
                                         &pSecondRegion, &size2, DSBLOCK_ENTIREBUFFER);
            WriteFile(file, firstBuffer, bufferCaps.dwBufferBytes, &nWritten, 0);
            Unchecked(sampleIndex)->Unlock(firstBuffer, size1, pSecondRegion, size2);
        } else {
            samplePresent = 0;
            WriteFile(file, &samplePresent, 1, &nWritten, 0);
        }
    }
    CloseHandle(file);
}

#undef BANK_COUNT
