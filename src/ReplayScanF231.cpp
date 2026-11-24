#include "ReplayBrowserScene.hpp"
#include <windows.h>
#include <string.h>

extern const char g_ReplayFindPatternAt00657FD8[] = "replay\\*.rep";
extern const char g_ReplayFirstRootAt00657FE8[] = "replay\\";
extern const char g_ReplayNextRootAt00657FF0[] = "replay\\";
void ReplayBrowserScene::ScanFiles()
{
    WIN32_FIND_DATAA findData;
    HANDLE file = FindFirstFileA(g_ReplayFindPatternAt00657FD8, &findData);
    // Keep the actual file-record, byte flag and loop-index lifetimes scoped.
    // VC7.1's corresponding physical offsets are observed, not padded.
    {
        DWORD readBytes;
        ReplayFileHeaderF219 header;
        {
            unsigned char flag;
            {
                unsigned int index;

                if (file != INVALID_HANDLE_VALUE) {
                    filenames.push_back(static_cast<char*>(0));
                    filenames.back() = new char[260];
                    strcpy(filenames.back(), g_ReplayFirstRootAt00657FE8);
                    strcat(filenames.back(), findData.cFileName);
                    while (FindNextFileA(file, &findData)) {
                        filenames.push_back(static_cast<char*>(0));
                        filenames.back() = new char[260];
                        strcpy(filenames.back(), g_ReplayNextRootAt00657FF0);
                        strcat(filenames.back(), findData.cFileName);
                    }
                    FindClose(file);
                }
                if (filenames.size() > 0) {
                    for (index = 0; index < filenames.size(); ++index) {
                        file = CreateFileA(filenames[index], GENERIC_READ,
                                           0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                        ReadFile(file, &header, sizeof(header), &readBytes, 0);
                        headers.push_back(header);
                        ReadFile(file, &flag, 1, &readBytes, 0);
                        secondaryModes.push_back(flag);
                        CloseHandle(file);
                    }
                }
            }
        }
    }
}
