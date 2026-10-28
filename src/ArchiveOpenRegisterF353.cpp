#include <windows.h>
#include <string.h>
// Only the exact 16-byte physical allocation is modeled; no complete private
// archive object or deque layout is inferred from this borrowed call interface.
// The name-list append takes an actual temporary null pointer by const
// reference. VC7.1 therefore places the active new/ctor and deque null
// values in the original native EH stack slots, unlike a named name-null
// variable, without any inert locals or fabricated padding.
class ArchiveOpenContextF353 {
    DWORD observedCarrier[4];
public:
    ArchiveOpenContextF353();
    void OpenAndReadIndex(const char* filename);
};
typedef char VerifyNativeArchiveContextF353[(sizeof(ArchiveOpenContextF353)==16)?1:-1];
class ArchiveResourceDequeF353 {
public:
    void Append(const ArchiveOpenContextF353* const& item);
    ArchiveOpenContextF353** Back();
};
class ArchiveNameDequeF353 {
public:
    void Append(const char* const& item);
    char** Back();
};
extern ArchiveResourceDequeF353 g_ArchiveObjectsF353;
extern ArchiveNameDequeF353 g_ArchiveNamesF353;
namespace ArchiveCatalogF353 {
void OpenAndRegister(const char* archiveFilename, const char* registeredName) {
    ArchiveOpenContextF353* emptyArchive=0;
    g_ArchiveObjectsF353.Append(emptyArchive);
    *g_ArchiveObjectsF353.Back()=new ArchiveOpenContextF353();
    (*g_ArchiveObjectsF353.Back())->OpenAndReadIndex(archiveFilename);
    g_ArchiveNamesF353.Append(static_cast<char*>(0));
    *g_ArchiveNamesF353.Back()=new char[strlen(registeredName)+1];
    strcpy(*g_ArchiveNamesF353.Back(),registeredName);
}
}
