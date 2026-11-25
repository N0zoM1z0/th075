#include <windows.h>
#include "audio/SoundBank.hpp"
#include <mmsystem.h>
#include <dsound.h>
#include <new>
#include <stdio.h>

namespace SharedWave406820 {
    bool __cdecl Load(const char*, IDirectSoundBuffer8**, DWORD);
}
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];
typedef char SoundCapsSize[(sizeof(DSBCAPS) == 20) ? 1 : -1];

void SoundBank::LoadWaveDirectory(const char* path, unsigned int count) {
    char filename[MAX_PATH];
    unsigned int i;
    HANDLE handle;
    bufferCount = count;
    for (i = 0; i < buffers.size(); i++) {
        if (buffers[i]) {
            buffers[i]->Release();
            buffers[i] = 0;
        }
    }
    buffers.clear();
    buffers.assign(bufferCount, 0);
    for (i = 0; i < count; i++) {
        sprintf(filename, "%s\\%03d.wav", path, static_cast<int>(i));
        handle = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
            SharedWave406820::Load(filename, &buffers.at(i), 0);
        }
    }
}
void SoundBank::LoadSerializedFile(const char* filename) {
    char* buffer;
    DWORD pcmBytes;
    BYTE entryPresent;
    WAVEFORMATEX format;
    int sampleCount = buffers.size();
    int sampleIndex;
    HANDLE file;
    DWORD inputBytesRead;
    file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    ReadFile(file, &sampleCount, 4, &inputBytesRead, 0);
    buffers.assign(sampleCount, 0);
    for (sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        ReadFile(file, &entryPresent, 1, &inputBytesRead, 0);
        if (entryPresent) {
            ReadFile(file, &pcmBytes, 4, &inputBytesRead, 0);
            ReadFile(file, &format, sizeof(format), &inputBytesRead, 0);
            buffer = new char[pcmBytes];
            ReadFile(file, buffer, pcmBytes, &inputBytesRead, 0);
            SoundCreation406A20::Create(&format, buffer, pcmBytes, &buffers[sampleIndex], 0);
            delete[] buffer;
        }
    }
    CloseHandle(file);
}

void SoundBank::SaveSerializedFile(const char* filename) {
    int sampleCount = buffers.size();
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
        if (buffers[sampleIndex]) {
            samplePresent = 1;
            WriteFile(file, &samplePresent, 1, &nWritten, 0);
            bufferCaps.dwSize = sizeof(bufferCaps);
            // Native code captures this SDK result without testing it.
            HRESULT result = buffers[sampleIndex]->GetCaps(&bufferCaps);
            WriteFile(file, &bufferCaps.dwBufferBytes, 4, &nWritten, 0);
            buffers[sampleIndex]->GetFormat(&format, sizeof(format), 0);
            WriteFile(file, &format, sizeof(format), &nWritten, 0);
            buffers[sampleIndex]->Lock(0, bufferCaps.dwBufferBytes, &firstBuffer, &size1,
                                         &pSecondRegion, &size2, DSBLOCK_ENTIREBUFFER);
            WriteFile(file, firstBuffer, bufferCaps.dwBufferBytes, &nWritten, 0);
            buffers[sampleIndex]->Unlock(firstBuffer, size1, pSecondRegion, size2);
        } else {
            samplePresent = 0;
            WriteFile(file, &samplePresent, 1, &nWritten, 0);
        }
    }
    CloseHandle(file);
}
