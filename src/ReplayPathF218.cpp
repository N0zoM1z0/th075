#include <stdio.h>
#include <io.h>
// The output path and original static format are referenced only; no
// complete ReplayRecords owner or runtime data is allocated.
extern const char g_ReplayPathFormatAt00657918[];
class ReplayPathF218 {
public:
    int FindAvailablePath(char* path);
};
int ReplayPathF218::FindAvailablePath(char* path)
{
    int candidate;
    for (candidate=0; candidate<1000; ++candidate) {
        sprintf(path,g_ReplayPathFormatAt00657918,candidate);
        if (_access(path,0)==-1)
            break;
    }
    return candidate;
}
