#include <windows.h>
#include <string.h>
// Borrowed 8-byte VC7 deque iterators and two global registries. This file
// does not claim the original full deque, value or resource class layouts.
// BeginInto/EndInto are caller-side hidden-sret aliases of native Begin/End.
// Both End() results are constructed in the native body; only the name end
// is compared. The live cursor record fixes the genuine original stack slots.
struct NameIteratorF341 {
    DWORD words[2];
    bool operator!=(const NameIteratorF341&) const;
    char*& operator*() const;
    NameIteratorF341 operator++(int);
};
struct ResourceIteratorF341 {
    DWORD words[2];
    ResourceIteratorF341 operator++(int);
    class ArchiveResourceF341*& operator*() const;
};
class ArchiveResourceF341 {
public:
    ~ArchiveResourceF341();
};
struct NameDequeF341 {
    void BeginInto(NameIteratorF341* dest);
    void EndInto(NameIteratorF341* dest);
    NameIteratorF341 Erase(NameIteratorF341 pos);
};
struct ResourceDequeF341 {
    void BeginInto(ResourceIteratorF341* dest);
    void EndInto(ResourceIteratorF341* dest);
    ResourceIteratorF341 Erase(ResourceIteratorF341 pos);
};
extern NameDequeF341 g_ArchiveNamesF341;
extern ResourceDequeF341 g_ArchiveResourcesF341;
struct ArchiveCursorStateF341 {
    NameIteratorF341 currentName;
    ResourceIteratorF341 endResource;
    NameIteratorF341 endName;
    ResourceIteratorF341 currentResource;
};
typedef char VerifyCursors32F341[(sizeof(ArchiveCursorStateF341)==32)?1:-1];
// The native entry is cdecl (RET), not a thiscall member (RET 4).
namespace ArchiveCatalogF341 { void CloseNamed(const char* name); }
void ArchiveCatalogF341::CloseNamed(const char* name) {
    ArchiveCursorStateF341 state;
    g_ArchiveNamesF341.BeginInto(&state.currentName);
    g_ArchiveNamesF341.EndInto(&state.endName);
    g_ArchiveResourcesF341.BeginInto(&state.currentResource);
    g_ArchiveResourcesF341.EndInto(&state.endResource);
    while(state.currentName!=state.endName) {
        if (!strcmp(*state.currentName,name)) {
            delete *state.currentResource;
            state.currentResource=g_ArchiveResourcesF341.Erase(state.currentResource);
            state.currentName=g_ArchiveNamesF341.Erase(state.currentName);
        } else {
            state.currentName++;
            state.currentResource++;
        }
    }
}
