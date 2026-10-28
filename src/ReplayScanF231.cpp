#include <windows.h>
#include <string.h>

// Borrowed call-only deque interfaces, not guessed original STL layouts.
// Two real separate string destinations contain the same native replay root.
extern const char g_ReplayFindPatternAt00657FD8[];
extern const char g_ReplayFirstRootAt00657FE8[];
extern const char g_ReplayNextRootAt00657FF0[];
class ReplayFilenameDequeF231 {
public:
    void push_back(char *const &filename);
    char **back();
    unsigned int size() const;
    char **operator[](unsigned int index);
};
class ReplayHeaderDequeF231 {public: void push_back(const void *header);};
class ReplayFlagsDequeF231 {public: void push_back(const unsigned char &flag);};
class ReplayBrowserScanF231 {public: void ScanFiles();};
#define OWN(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
void ReplayBrowserScanF231::ScanFiles()
{
    WIN32_FIND_DATAA findData;
    HANDLE file = FindFirstFileA(g_ReplayFindPatternAt00657FD8, &findData);
    // Keep the actual file-record, byte flag and loop-index lifetimes scoped.
    // VC7.1's corresponding physical offsets are observed, not padded.
    {
        DWORD readBytes;
        unsigned char header[60];
        {
            unsigned char flag;
            {
                unsigned int index;

                if (file != INVALID_HANDLE_VALUE) {
                    OWN(ReplayFilenameDequeF231, 0x0c).push_back(static_cast<char*>(0));
                    *OWN(ReplayFilenameDequeF231, 0x0c).back() = new char[260];
                    strcpy(*OWN(ReplayFilenameDequeF231, 0x0c).back(), g_ReplayFirstRootAt00657FE8);
                    strcat(*OWN(ReplayFilenameDequeF231, 0x0c).back(), findData.cFileName);
                    while (FindNextFileA(file, &findData)) {
                        OWN(ReplayFilenameDequeF231, 0x0c).push_back(static_cast<char*>(0));
                        *OWN(ReplayFilenameDequeF231, 0x0c).back() = new char[260];
                        strcpy(*OWN(ReplayFilenameDequeF231, 0x0c).back(), g_ReplayNextRootAt00657FF0);
                        strcat(*OWN(ReplayFilenameDequeF231, 0x0c).back(), findData.cFileName);
                    }
                    FindClose(file);
                }
                if (OWN(ReplayFilenameDequeF231, 0x0c).size() > 0) {
                    for (index = 0; index < OWN(ReplayFilenameDequeF231, 0x0c).size(); ++index) {
                        file = CreateFileA(*OWN(ReplayFilenameDequeF231, 0x0c)[index], GENERIC_READ,
                                           0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                        ReadFile(file, header, 60, &readBytes, 0);
                        OWN(ReplayHeaderDequeF231, 0x20).push_back(header);
                        ReadFile(file, &flag, 1, &readBytes, 0);
                        OWN(ReplayFlagsDequeF231, 0x34).push_back(flag);
                        CloseHandle(file);
                    }
                }
            }
        }
    }
}
#undef OWN
