// Independently exact complete original R053 LoadingScene/LogoScene derived
// constructors. Each has its own native vtable, genuine /GX EH handler,
// exact data/system filenames and physically different 8-/16-bit state.
// Independent R053 loading and logo derived scene resource constructors.
// Only physical 8-byte scene base and borrowed 80-byte texture manager ABI.
class NativeSceneBaseF446 {
    void* config;
public:NativeSceneBaseF446();virtual ~NativeSceneBaseF446();
};
class NativeSmallTextureF446 {
    unsigned char observedStorage[80];
public:NativeSmallTextureF446();void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
typedef char VerifyNative80F446[(sizeof(NativeSmallTextureF446)==80)?1:-1];
extern char g_LoadArchiveRootAt00657B94[];
extern char g_LoadArchivePathAt00657B9C[];
extern char g_LogoArchiveRootAt00657BC0[];
extern char g_LogoArchivePathAt00657BC8[];
class LoadingSceneInitF446 : public NativeSceneBaseF446 {
    NativeSmallTextureF446* texture;
    unsigned char state;
public:LoadingSceneInitF446();virtual ~LoadingSceneInitF446();
};
class LogoSceneInitF446 : public NativeSceneBaseF446 {
    NativeSmallTextureF446* texture;
    short state;
public:LogoSceneInitF446();virtual ~LogoSceneInitF446();
};
LoadingSceneInitF446::LoadingSceneInitF446() {
    texture=new NativeSmallTextureF446;
    texture->AllocateSlots(1);
    texture->LoadArchive(g_LoadArchivePathAt00657B9C,g_LoadArchiveRootAt00657B94);
    state=0;
}
LogoSceneInitF446::LogoSceneInitF446() {
    texture=new NativeSmallTextureF446;
    texture->AllocateSlots(1);
    texture->LoadArchive(g_LogoArchivePathAt00657BC8,g_LogoArchiveRootAt00657BC0);
    state=0;
}
