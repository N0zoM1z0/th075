// Natural complete policy observations; no original game owner is instantiated.
#include <list>
#include <new>
#include <string.h>
extern "C" {
__declspec(dllimport) void* __stdcall CreateObservedFile(const char*, unsigned long, unsigned long, void*, unsigned long, unsigned long, void*);
__declspec(dllimport) unsigned long __stdcall GetObservedFileSize(void*, unsigned long*);
__declspec(dllimport) int __stdcall ReadObservedFile(void*, void*, unsigned long, unsigned long*, void*);
__declspec(dllimport) int __stdcall WriteObservedFile(void*, const void*, unsigned long, unsigned long*, void*);
__declspec(dllimport) int __stdcall CloseObservedFile(void*);
}
struct MusicFilePolicyObservation {
    void encode() {
        void* file = CreateObservedFile("musicroom.csv", 0x80000000UL, 0, 0, 3, 0x80, 0);
        if (file == reinterpret_cast<void*>(-1)) return;
        unsigned long size = GetObservedFileSize(file, 0);
        char* data = new char[size];
        unsigned long transferred;
        ReadObservedFile(file, data, size, &transferred, 0);
        CloseObservedFile(file);
        file = CreateObservedFile("musicroom.dat", 0x40000000UL, 0, 0, 2, 0x80, 0);
        if (file != reinterpret_cast<void*>(-1)) {
            unsigned char mask = 0x5c;
            unsigned char step = 0x5a;
            for (unsigned long index = 0; index < size; ++index) {
                data[index] ^= mask;
                mask += step;
                step += 0x3d;
            }
            WriteObservedFile(file, data, size, &transferred, 0);
            CloseObservedFile(file);
        }
        delete[] data;
    }
};
struct FileNamePolicyObservation {
    char value[100];
    unsigned long file_size;
    unsigned long initial_state;
};
struct ReadableFilePolicyObservation {
    std::list<FileNamePolicyObservation> names;
    void append(const char* path) {
        void* file = CreateObservedFile(path, 0x80000000UL, 0, 0, 3, 0x80, 0);
        if (file == reinterpret_cast<void*>(-1)) return;
        FileNamePolicyObservation name;
        name.initial_state = 0;
        name.file_size = GetObservedFileSize(file, 0);
        strcpy(name.value, path);
        CloseObservedFile(file);
        names.push_back(name);
    }
};
void ObserveMusicFilePolicy(MusicFilePolicyObservation& p) { p.encode(); }
void ObserveReadableFilePolicy(ReadableFilePolicyObservation& p, const char* path) { p.append(path); }
extern "C" const unsigned long FileResourcePolicyLayout[] = {
    sizeof(MusicFilePolicyObservation), sizeof(FileNamePolicyObservation),
    sizeof(std::list<FileNamePolicyObservation>), sizeof(ReadableFilePolicyObservation)
};
