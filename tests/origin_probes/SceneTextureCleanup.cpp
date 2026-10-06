#include <d3d8.h>
// Complete compact policy observations; no original private scene is declared.
struct GlobalLifetimeObservation {
    GlobalLifetimeObservation();
    ~GlobalLifetimeObservation();
};
struct ResourceObservation { ~ResourceObservation(); };
struct SceneBaseObservation {
    virtual ~SceneBaseObservation();
    GlobalLifetimeObservation globals;
};
struct TextureSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
    IDirect3DTexture8* texture;
    ~TextureSceneObservation();
};
TextureSceneObservation::~TextureSceneObservation() {
    if (resource) delete resource;
    if (texture) texture->Release();
}
struct ImplicitTextureSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
    IDirect3DTexture8* texture;
};
void ExerciseImplicitTextureSceneLifetime() {
    ImplicitTextureSceneObservation value;
}
extern const unsigned long SceneTextureLifetimeSizes[] = {
    sizeof(GlobalLifetimeObservation),sizeof(SceneBaseObservation),
    sizeof(TextureSceneObservation),sizeof(ImplicitTextureSceneObservation)
};
