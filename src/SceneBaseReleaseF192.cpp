// This accepted source contains only the independently authored destructor.
// The paired 0x004251C0 constructor remains origin-unknown (R108) even
// though its full 34-byte private compiler preview is structurally exact.
class SceneDefaultConfigF192 {
public:
    void ReleaseDefaults();
};
class SceneBaseReleaseF192 {
public:
    ~SceneBaseReleaseF192();
};
extern const void* g_SceneBaseVirtualTableAt00657B88[];

SceneBaseReleaseF192::~SceneBaseReleaseF192()
{
    *reinterpret_cast<const void***>(this) = g_SceneBaseVirtualTableAt00657B88;
    reinterpret_cast<SceneDefaultConfigF192*>(
        reinterpret_cast<unsigned char*>(this) + 4)->ReleaseDefaults();
}
