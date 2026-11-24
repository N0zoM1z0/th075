#pragma once

#include <vector>

struct IDirectSoundBuffer8;

class SoundBank {
    std::vector<IDirectSoundBuffer8*> buffers;
    unsigned int bufferCount;

public:
    SoundBank();
    ~SoundBank();
    void Play(int sound);
    void LoadWaveDirectory(const char* path, unsigned int count);
    void LoadSerializedFile(const char* filename);
    void SaveSerializedFile(const char* filename);
    void LoadArchive(const char* filename, const char* archive);
    void Configure();
};

typedef char SoundBankSize[(sizeof(SoundBank) == 0x14) ? 1 : -1];

extern SoundBank* g_SoundBank;
