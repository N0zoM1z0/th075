// Complete synthetic observations; no original game owner is instantiated.
#include <list>
struct ArchiveReleaseValueObservation { unsigned char bytes[108]; };
struct CharacterReleaseValueObservation { unsigned char bytes[16]; };
typedef std::list<ArchiveReleaseValueObservation> ArchiveReleaseList;
typedef std::list<CharacterReleaseValueObservation> CharacterReleaseList;
extern "C" __declspec(dllimport) int __stdcall CloseObservedHandle(void*);
struct ExplicitArchiveReleaseObservation {
    void* handle;
    ArchiveReleaseList entries;
    ~ExplicitArchiveReleaseObservation() {
        if (handle) CloseObservedHandle(handle);
        entries.clear();
    }
};
struct ImplicitArchiveReleaseObservation { void* handle; ArchiveReleaseList entries; };
struct ReleaseInterfaceObservation {
    virtual long __stdcall query(const void*, void**) = 0;
    virtual unsigned long __stdcall retain() = 0;
    virtual unsigned long __stdcall release() = 0;
};
struct TextureReleaseObservation { ~TextureReleaseObservation(); };
// Only the observed +40 texture subobject spacing is tested by these scalars.
struct ExplicitSharedReleaseObservation {
    ReleaseInterfaceObservation* shared;
    unsigned long intervening_state[9];
    TextureReleaseObservation textures;
    ~ExplicitSharedReleaseObservation() { shared->release(); }
};
struct ImplicitSharedReleaseObservation {
    ReleaseInterfaceObservation* shared;
    unsigned long intervening_state[9];
    TextureReleaseObservation textures;
};
// Small complete base tests destruction order without reproducing target layout.
struct ReleaseBaseObservation {
    virtual void observedVirtual();
    ~ReleaseBaseObservation();
};
struct ExplicitCharacterReleaseObservation : ReleaseBaseObservation {
    CharacterReleaseList entries;
    ~ExplicitCharacterReleaseObservation() { entries.clear(); }
};
struct ImplicitCharacterReleaseObservation : ReleaseBaseObservation { CharacterReleaseList entries; };
void ObserveExplicitArchiveRelease(ExplicitArchiveReleaseObservation* p) { p->~ExplicitArchiveReleaseObservation(); }
void ObserveImplicitArchiveRelease(ImplicitArchiveReleaseObservation* p) { p->~ImplicitArchiveReleaseObservation(); }
void ObserveExplicitSharedRelease(ExplicitSharedReleaseObservation* p) { p->~ExplicitSharedReleaseObservation(); }
void ObserveImplicitSharedRelease(ImplicitSharedReleaseObservation* p) { p->~ImplicitSharedReleaseObservation(); }
void ObserveExplicitCharacterRelease(ExplicitCharacterReleaseObservation* p) { p->~ExplicitCharacterReleaseObservation(); }
void ObserveImplicitCharacterRelease(ImplicitCharacterReleaseObservation* p) { p->~ImplicitCharacterReleaseObservation(); }
struct OrdinaryArchiveTidyObservation {
    unsigned long observed_words[3];
    void tidy();
    void finish() { tidy(); }
};
struct OrdinaryCharacterTidyObservation {
    unsigned long observed_words[3];
    void tidy();
    void finish() { tidy(); }
};
void ObserveOrdinaryArchiveTidy(OrdinaryArchiveTidyObservation* p) { p->finish(); }
void ObserveOrdinaryCharacterTidy(OrdinaryCharacterTidyObservation* p) { p->finish(); }
extern "C" const unsigned long ResourceReleaseLayout[] = {
    sizeof(ArchiveReleaseValueObservation),sizeof(CharacterReleaseValueObservation),
    sizeof(ArchiveReleaseList),sizeof(CharacterReleaseList),
    sizeof(ExplicitArchiveReleaseObservation),sizeof(ImplicitArchiveReleaseObservation),
    sizeof(ExplicitSharedReleaseObservation),sizeof(ImplicitSharedReleaseObservation),
    sizeof(ReleaseBaseObservation),sizeof(ExplicitCharacterReleaseObservation),sizeof(ImplicitCharacterReleaseObservation)
};
