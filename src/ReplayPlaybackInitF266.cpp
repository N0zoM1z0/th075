#include <windows.h>

// Three real 20-byte VC7 deque members are evidenced by original
// constructors/callees; no complete private replay owner is asserted.
class ReplayBaseF266 {
    void* config;
public:
    ReplayBaseF266();
    virtual ~ReplayBaseF266();
};
class ReplayDequeBaseF266 { protected: unsigned int physical[5]; };
class ReplayDequeNamesF266 : public ReplayDequeBaseF266 {
public:
    ReplayDequeNamesF266();
    ~ReplayDequeNamesF266();
    void Clear();
};
class ReplayDequeFilesF266 : public ReplayDequeBaseF266 {
public:
    ReplayDequeFilesF266();
    ~ReplayDequeFilesF266();
};
class ReplayDequeRecordsF266 : public ReplayDequeBaseF266 {
public:
    ReplayDequeRecordsF266();
    ~ReplayDequeRecordsF266();
};
typedef char AssertReplayDeque20F266[(sizeof(ReplayDequeBaseF266)==20)?1:-1];
class ReplayTextureF266 {
    unsigned char nativeObservedBytes[80];
public:
    ReplayTextureF266();
    void AllocateSlots(int);
    void LoadDefault(const char* file,const char* root);
};
typedef char AssertReplayTexture80F266[(sizeof(ReplayTextureF266)==80)?1:-1];
class ReplayActorF266 {
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(); virtual void Slot4(); virtual ~ReplayActorF266();
};
extern ReplayActorF266* g_ReplayActorAAt00671418;
extern ReplayActorF266* g_ReplayActorBAt0067141C;
extern const char g_ReplayCatalogFileAt00657FC0[];
extern const char g_ReplayCatalogRootAt00657FB8[];
extern unsigned short g_ReplayControllerAt0067162C;
class ReplayPlaybackInitF266 : public ReplayBaseF266 {
    ReplayTextureF266* texture;
    ReplayDequeNamesF266 names;
    ReplayDequeFilesF266 files;
    ReplayDequeRecordsF266 records;
public:
    ReplayPlaybackInitF266();
    virtual ~ReplayPlaybackInitF266();
    void ScanFiles();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ReplayPlaybackInitF266::ReplayPlaybackInitF266()
{
    names.Clear();
    texture=new ReplayTextureF266();
    texture->AllocateSlots(3);
    texture->LoadDefault(g_ReplayCatalogFileAt00657FC0,g_ReplayCatalogRootAt00657FB8);
    if (g_ReplayActorAAt00671418) {
        delete g_ReplayActorAAt00671418;
        g_ReplayActorAAt00671418=0;
    }
    if (g_ReplayActorBAt0067141C) {
        delete g_ReplayActorBAt0067141C;
        g_ReplayActorBAt0067141C=0;
    }
    ScanFiles();
    FIELD(unsigned char,0x51)=0;
    FIELD(unsigned short,0x48)=g_ReplayControllerAt0067162C;
    FIELD(unsigned char,0x4c)=5;
}
#undef FIELD
