#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>

extern IDirectSound8* sharedSoundDevice;
namespace SharedSound4066C0 {
    void __cdecl ShowError(const char*);
}
namespace SharedPcm406B80 {
    bool __cdecl Read(const char*, char**, WAVEFORMATEX*, DWORD*);
}
namespace SharedWave406820 {
    // The caller supplies three words; the unused third formal's original type
    // and name are unknown. DWORD retains the observed compatible zero.
    bool __cdecl Load(const char*, IDirectSoundBuffer8**, DWORD);
}
typedef char ChunkInfoSize[(sizeof(MMCKINFO) == 20) ? 1 : -1];
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];
typedef char SoundDescriptionSize[(sizeof(DSBUFFERDESC) == 36) ? 1 : -1];

bool SharedWave406820::Load(const char* filename, IDirectSoundBuffer8** output, DWORD) {
    DSBUFFERDESC descriptor;
    void* buffer2;
    DWORD size;
    DWORD firstBytes;
    DWORD regionSize2;
    void* firstBuffer;
    WAVEFORMATEX waveFormat;
    HRESULT result;
    if (*output) {
        (*output)->Release();
        *output = 0;
    }
    IDirectSoundBuffer* pDSBuffer = 0;
    char* buffer = 0;
    if (!SharedPcm406B80::Read(filename, &buffer, &waveFormat, &size)) {
        SharedSound4066C0::ShowError("\x57\x41\x56\x45\x83\x74\x83\x40\x83\x43\x83\x8b\x82\xcc\x83\x66\x81\x5b\x83\x5e\x8e\xe6\x93\xbe\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    memset(&descriptor, 0, sizeof(descriptor));
    descriptor.dwSize = sizeof(descriptor);
    descriptor.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS |
        DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_LOCDEFER;
    descriptor.dwBufferBytes = size;
    descriptor.lpwfxFormat = &waveFormat;
    result = sharedSoundDevice->CreateSoundBuffer(&descriptor, &pDSBuffer, 0);
    if (FAILED(result)) {
        SharedSound4066C0::ShowError("\x83\x65\x83\x93\x83\x7c\x83\x89\x83\x8a\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xcc\x90\xb6\x90\xac\x82\xc9\x8e\xb8\x94\x73");
        if (buffer)
            delete[] buffer;
        return false;
    }
    result = pDSBuffer->QueryInterface(IID_IDirectSoundBuffer8,
                                      reinterpret_cast<void**>(output));
    pDSBuffer->Release();
    if (FAILED(result)) {
        SharedSound4066C0::ShowError("\x44\x69\x72\x65\x63\x74\x53\x6f\x75\x6e\x64\x42\x75\x66\x66\x65\x72\x38\x82\xcc\x8e\xe6\x93\xbe\x82\xc9\x8e\xb8\x94\x73");
        if (buffer)
            delete[] buffer;
        return false;
    }
    result = (*output)->Lock(0, size, &firstBuffer, &firstBytes,
                            &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
    if (FAILED(result)) {
        SharedSound4066C0::ShowError("\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xcc\x83\x8d\x83\x62\x83\x4e\x82\xc9\x8e\xb8\x94\x73");
        if (buffer)
            delete[] buffer;
        return false;
    }
    memcpy(firstBuffer, buffer, size);
    (*output)->Unlock(firstBuffer, firstBytes, buffer2, regionSize2);
    if (buffer)
        delete[] buffer;
    return true;
}

bool SharedPcm406B80::Read(const char* filename, char** output,
                         WAVEFORMATEX* format, DWORD* size) {
    HMMIO file = 0;
    MMCKINFO parent = {0, 0, 0, 0, 0};
    MMCKINFO chunkInfo = parent;
    file = mmioOpenA(const_cast<char*>(filename), 0, MMIO_READ | MMIO_ALLOCBUF);
    if (!file) {
        SharedSound4066C0::ShowError("\x83\x74\x83\x40\x83\x43\x83\x8b\x82\xcc\x83\x49\x81\x5b\x83\x76\x83\x93\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(file, &parent, 0, MMIO_FINDRIFF)) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x57\x41\x56\x45\x83\x74\x83\x40\x83\x43\x83\x8b\x82\xc5\x82\xcd\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
        return false;
    }
    chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(file, &chunkInfo, &parent, 0)) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x83\x74\x83\x40\x83\x43\x83\x8b\x82\xcc\x83\x49\x81\x5b\x83\x76\x83\x93\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    if (mmioRead(file, reinterpret_cast<HPSTR>(format), sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX)) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x66\x6d\x74\x83\x60\x83\x83\x83\x93\x83\x4e\x82\xcc\x93\xc7\x82\xdd\x8e\xe6\x82\xe8\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    if (format->wFormatTag != WAVE_FORMAT_PCM) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x50\x43\x4d\x83\x74\x83\x48\x81\x5b\x83\x7d\x83\x62\x83\x67\x82\xc5\x82\xcd\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
        return false;
    }
    if (mmioAscend(file, &chunkInfo, 0)) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x83\x41\x83\x5a\x83\x93\x83\x68\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(file, &chunkInfo, &parent, MMIO_FINDCHUNK)) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x64\x61\x74\x61\x83\x60\x83\x83\x83\x93\x83\x4e\x82\xcc\x8c\x9f\x8d\xf5\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    *output = new char[chunkInfo.cksize];
    if (mmioRead(file, *output, chunkInfo.cksize) != chunkInfo.cksize) {
        mmioClose(file, 0);
        SharedSound4066C0::ShowError("\x64\x61\x74\x61\x83\x60\x83\x83\x83\x93\x83\x4e\x82\xcc\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    mmioClose(file, 0);
    *size = chunkInfo.cksize;
    return true;
}
