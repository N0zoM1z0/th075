#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

extern signed char soundBankVolume;
extern signed char masterVolume;
namespace AudioVolume4073B0 {
void __cdecl SetSoundBankVolume(signed char volume) {
    soundBankVolume = volume;
}
void __cdecl SetStreamVolume(signed char volume) {
    masterVolume = volume;
}
}

// Separate pointer-only interfaces preserve accepted source declarations.
// Neither owner has a complete layout here; never instantiate or embed it.
class SoundBankPlay4079C0 {
public:
    void Play(int);
    unsigned int Size();
    IDirectSoundBuffer8*& Unchecked(unsigned int);
    IDirectSoundBuffer8*& At(unsigned int);
};
void SoundBankPlay4079C0::Play(int index) {
    if (index < 0 || index >= static_cast<int>(Size()))
        return;
    if (Unchecked(index) == 0)
        return;
    IDirectSoundBuffer8* buffer = At(index);
    buffer->Stop();
    buffer->SetCurrentPosition(0);
    buffer->SetVolume((soundBankVolume - 100) * 50);
    buffer->Play(0, 0, 0);
}

class AudioRecordLifecycle409290 {
public:
    AudioRecordLifecycle409290();
    ~AudioRecordLifecycle409290();
};
#define RECORD_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset))
#define RECORD_BUFFER RECORD_FIELD(IDirectSoundBuffer8*, 0)
#define RECORD_FILE RECORD_FIELD(HANDLE, 60)
AudioRecordLifecycle409290::AudioRecordLifecycle409290() {
    RECORD_BUFFER = 0;
    RECORD_FIELD(DWORD, 32) = 0;
    RECORD_FIELD(DWORD, 36) = 0;
    RECORD_FIELD(DWORD, 40) = 0;
    RECORD_FIELD(LONG, 44) = 0;
    RECORD_FILE = 0;
    RECORD_FIELD(DWORD, 8) = 0;
}
AudioRecordLifecycle409290::~AudioRecordLifecycle409290() {
    if (!RECORD_FIELD(BYTE, 58) && RECORD_FILE) {
        CloseHandle(RECORD_FILE);
        RECORD_FILE = 0;
    }
    if (RECORD_BUFFER) {
        RECORD_BUFFER->Release();
        RECORD_BUFFER = 0;
    }
}
