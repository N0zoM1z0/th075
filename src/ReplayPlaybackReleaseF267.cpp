#include <stdlib.h>

// Three actually observed 20-byte VC7 deque boundaries, not complete
// original game container implementation or record class identity.
class ReplayBaseF267 {
    void* config;
public:
    ReplayBaseF267();
    virtual ~ReplayBaseF267();
};
class ReplayDequeBaseF267 { protected: unsigned int nativeWords[5]; };
class ReplayDequeNamesF267 : public ReplayDequeBaseF267 {
public:
    ReplayDequeNamesF267();
    ~ReplayDequeNamesF267();
    unsigned int Size() const;
    char** At(unsigned int index);
    void Clear();
};
class ReplayDequeFilesF267 : public ReplayDequeBaseF267 {
public:
    ReplayDequeFilesF267();
    ~ReplayDequeFilesF267();
};
class ReplayDequeRecordsF267 : public ReplayDequeBaseF267 {
public:
    ReplayDequeRecordsF267();
    ~ReplayDequeRecordsF267();
};
typedef char VerifyReplayDequeF267[(sizeof(ReplayDequeBaseF267)==20)?1:-1];
class ReplayTextureF267 {public: ~ReplayTextureF267();};
extern unsigned short g_ReplayControllerAt0067162C;
class ReplayPlaybackReleaseF267 : public ReplayBaseF267 {
    ReplayTextureF267* texture;
    ReplayDequeNamesF267 names;
    ReplayDequeFilesF267 files;
    ReplayDequeRecordsF267 records;
public:
    ReplayPlaybackReleaseF267();
    virtual ~ReplayPlaybackReleaseF267();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ReplayPlaybackReleaseF267::~ReplayPlaybackReleaseF267()
{
    g_ReplayControllerAt0067162C=FIELD(unsigned short,0x48);
    for (unsigned int index=0;index<names.Size();++index) {
        char* ownedName=*names.At(index);
        free(ownedName);
    }
    names.Clear();
    if (texture) delete texture;
}
#undef FIELD
