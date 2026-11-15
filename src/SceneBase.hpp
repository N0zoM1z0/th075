#ifndef TH075_SCENE_BASE_HPP
#define TH075_SCENE_BASE_HPP

// Base of every scene: the vtable pointer and a shared counter at +4. Each
// scene's vtable has three slots: the deleting destructor, Update and Render.
class SceneBase {
public:
    SceneBase();
    virtual ~SceneBase();               // 00431F40
private:
    unsigned int sharedCounter;
};
typedef char SceneBaseSize[sizeof(SceneBase) == 8 ? 1 : -1];
#endif
