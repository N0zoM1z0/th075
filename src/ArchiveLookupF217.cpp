#include <string.h>
// Original deque-based archive registry is borrowed. This file creates no
// original collection, iterator or data storage and counts only this body.
class ArchiveNameRegistryF217 {
public:
    unsigned int Size();
    const char** At(unsigned int index);
};
class ArchiveObjectRegistryF217 {
public:
    void** At(unsigned int index);
};
extern ArchiveNameRegistryF217 g_ArchiveNamesAt0068BE1C;
extern ArchiveObjectRegistryF217 g_ArchiveObjectsAt0068BE08;
namespace ResourceLookupF217 {
void* FindByName(const char* name)
{
    unsigned int index;
    for (index=0; index < g_ArchiveNamesAt0068BE1C.Size(); ++index) {
        if (!strcmp(*g_ArchiveNamesAt0068BE1C.At(index), name))
            break;
    }
    if (index >= g_ArchiveNamesAt0068BE1C.Size())
        return 0;
    return *g_ArchiveObjectsAt0068BE08.At(index);
}
}
