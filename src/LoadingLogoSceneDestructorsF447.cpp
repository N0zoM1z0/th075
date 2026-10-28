// Independently exact two complete original R234 /GX scene-derived
// destructors. Genuine `delete texture` naturally creates native pointer
// temporary slots, scalar texture deleting dtor and base scene cleanup.
// Two original R234 scene resource destructors. Borrowed actual 8-byte
// scene base, native texture pointer at this+8 and compiler /GX lifetime.
class NativeSceneBaseF447 {
    void* config;
public:NativeSceneBaseF447();virtual ~NativeSceneBaseF447();
};
class NativeSmallTextureF447 { public:~NativeSmallTextureF447(); };
class LoadingSceneReleaseF447 : public NativeSceneBaseF447 {
    NativeSmallTextureF447* texture;
    unsigned char state;
public: LoadingSceneReleaseF447();virtual ~LoadingSceneReleaseF447();
};
class LogoSceneReleaseF447 : public NativeSceneBaseF447 {
    NativeSmallTextureF447* texture;
    short state;
public: LogoSceneReleaseF447();virtual ~LogoSceneReleaseF447();
};
LoadingSceneReleaseF447::~LoadingSceneReleaseF447() {
    if(texture) delete texture;
}
LogoSceneReleaseF447::~LogoSceneReleaseF447() {
    if(texture) delete texture;
}
