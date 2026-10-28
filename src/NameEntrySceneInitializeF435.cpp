// Complete original 260-byte R109 name-entry scene constructor.
// Actual VC7.1 /GX EH, native vtable, replay archive pathname and
// resource selection reader are generated from natural source.
// R109 original name-entry scene C++ constructor with real textures and
// game replay selection state. Only borrowed scene and archive ABI.
class SceneBaseF435 {
    void* config;
public: SceneBaseF435();virtual ~SceneBaseF435();
};
class NameEntryTextureF435 {
    unsigned char physicalStorage[80];
public: NameEntryTextureF435(); void AllocateSlots(int); void LoadArchive(const char*,const char*);
};
typedef char VerifyTexture80F435[(sizeof(NameEntryTextureF435)==80)?1:-1];
class ReplayDataReaderF435 {
public: void* GetSelection(void* out);
};
extern ReplayDataReaderF435 g_ReplayDataReaderAt00671750;
extern signed char g_ReplayNameModeAt006714CE;
extern char g_ReplayDataPathAt00657F84[];
extern char g_ReplayArchiveRootAt00657F7C[];
class NameEntryInitF435 : public SceneBaseF435 {
    NameEntryTextureF435* texture;
public:NameEntryInitF435();virtual ~NameEntryInitF435();
};
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
NameEntryInitF435::NameEntryInitF435() {
    FIELD(NameEntryTextureF435*,8) = new NameEntryTextureF435;
    FIELD(NameEntryTextureF435*,8)->AllocateSlots(3);
    FIELD(NameEntryTextureF435*,8)->LoadArchive(g_ReplayDataPathAt00657F84,g_ReplayArchiveRootAt00657F7C);
    FIELD(short,0xE)=0;
    FIELD(short,0x10)=0;
    FIELD(short,0x12)=0;
    FIELD(short,0x14)=0;
    if(g_ReplayNameModeAt006714CE<0) FIELD(unsigned char,0xC)=1;
    else FIELD(unsigned char,0xC)=0;
    FIELD(void*,0x18)=g_ReplayDataReaderAt00671750.GetSelection(reinterpret_cast<unsigned char*>(this)+0x1C);
}
#undef FIELD
