#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>

// Partial lifetime interface only. Never instantiate or embed this owner.
class SharedSoundClient406610 {
public:
    SharedSoundClient406610();
    ~SharedSoundClient406610();
};
extern unsigned int sharedSoundClients;
extern HWND sharedSoundWindow;
extern IDirectSound8* sharedSoundDevice;
extern IDirectSoundBuffer* sharedSoundPrimary;
namespace SharedSound4066C0 {
    void __cdecl ShowError(const char*);
    bool __cdecl Initialize(HWND);
}
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
typedef char SoundDescriptorSize[(sizeof(DSBUFFERDESC) == 36) ? 1 : -1];

SharedSoundClient406610::SharedSoundClient406610() {
    if (sharedSoundClients == 0) {
        sharedSoundDevice = 0;
        sharedSoundPrimary = 0;
    }
    sharedSoundClients++;
}
SharedSoundClient406610::~SharedSoundClient406610() {
    if (--sharedSoundClients == 0) {
        if (sharedSoundPrimary) {
            sharedSoundPrimary->Release();
            sharedSoundPrimary = 0;
        }
        if (sharedSoundDevice) {
            sharedSoundDevice->Release();
            sharedSoundDevice = 0;
        }
    }
}
void SharedSound4066C0::ShowError(const char* message) {
    MessageBoxA(sharedSoundWindow, message, "DSound-Error", 0);
}
bool SharedSound4066C0::Initialize(HWND window) {
    DSBUFFERDESC description;
    HRESULT result;
    sharedSoundWindow = window;
    result = CoCreateInstance(CLSID_DirectSound8, 0,
        CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, IID_IDirectSound8,
        reinterpret_cast<void**>(&sharedSoundDevice));
    if (FAILED(result)) {
        ShowError("\x44\x69\x72\x65\x63\x74\x53\x6f\x75\x6e\x64\x83\x49\x83\x75\x83\x57\x83\x46\x83\x4e\x83\x67\x82\xcc\x8d\xec\x90\xac\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    result = sharedSoundDevice->Initialize(0);
    if (FAILED(result)) {
        ShowError("\x44\x69\x72\x65\x63\x74\x53\x6f\x75\x6e\x64\x83\x49\x83\x75\x83\x57\x83\x46\x83\x4e\x83\x67\x82\xcc\x8f\x89\x8a\xfa\x89\xbb\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    result = sharedSoundDevice->SetCooperativeLevel(sharedSoundWindow, DSSCL_PRIORITY);
    if (FAILED(result)) {
        result = sharedSoundDevice->SetCooperativeLevel(sharedSoundWindow, DSSCL_NORMAL);
        if (FAILED(result)) {
            ShowError("\x8b\xa6\x92\xb2\x83\x8c\x83\x78\x83\x8b\x82\xcc\x90\xdd\x92\xe8\x82\xc9\x8e\xb8\x94\x73");
            return false;
        }
    }
    memset(&description, 0, sizeof(description));
    description.dwSize = sizeof(description);
    description.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_LOCDEFER;
    result = sharedSoundDevice->CreateSoundBuffer(&description, &sharedSoundPrimary, 0);
    if (FAILED(result)) {
        ShowError("\x83\x76\x83\x89\x83\x43\x83\x7d\x83\x8a\x83\x54\x83\x45\x83\x93\x83\x68\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xcc\x90\xb6\x90\xac\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    return true;
}

// Five caller words are observed. The unused fifth formal's original type and
// name remain unknown; DWORD preserves the existing caller's compatible zero.
bool SoundCreation406A20::Create(const WAVEFORMATEX* format, const void* data,
    DWORD size, IDirectSoundBuffer8** output, DWORD) {
    DSBUFFERDESC descriptor;
    void* firstRegion;
    void* region2;
    HRESULT hres;
    DWORD firstBytes;
    DWORD regionSize2;
    if (*output) {
        (*output)->Release();
        *output = 0;
    }
    IDirectSoundBuffer* pDSBuffer = 0;
    memset(&descriptor, 0, sizeof(descriptor));
    descriptor.dwSize = sizeof(descriptor);
    descriptor.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS |
        DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_LOCDEFER;
    descriptor.dwBufferBytes = size;
    descriptor.lpwfxFormat = const_cast<WAVEFORMATEX*>(format);
    hres = sharedSoundDevice->CreateSoundBuffer(&descriptor, &pDSBuffer, 0);
    if (FAILED(hres)) {
        SharedSound4066C0::ShowError("\x83\x65\x83\x93\x83\x7c\x83\x89\x83\x8a\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xcc\x90\xb6\x90\xac\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    hres = pDSBuffer->QueryInterface(IID_IDirectSoundBuffer8,
                                      reinterpret_cast<void**>(output));
    pDSBuffer->Release();
    if (FAILED(hres)) {
        SharedSound4066C0::ShowError("\x44\x69\x72\x65\x63\x74\x53\x6f\x75\x6e\x64\x42\x75\x66\x66\x65\x72\x38\x82\xcc\x8e\xe6\x93\xbe\x82\xc9\x8e\xb8\x94\x73");
        return false;
    }
    if (data) {
        hres = (*output)->Lock(0, size, &firstRegion, &firstBytes,
                                &region2, &regionSize2, DSBLOCK_ENTIREBUFFER);
        if (FAILED(hres)) {
            SharedSound4066C0::ShowError("\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xcc\x83\x8d\x83\x62\x83\x4e\x82\xc9\x8e\xb8\x94\x73");
            return false;
        }
        memcpy(firstRegion, data, size);
        (*output)->Unlock(firstRegion, firstBytes, region2, regionSize2);
    }
    return true;
}
