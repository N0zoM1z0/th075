#include <d3d8.h>
// Complete compact observations; the original private music scene is not declared.
struct GlobalLifetimeObservation {
    GlobalLifetimeObservation();
    ~GlobalLifetimeObservation();
};
struct ResourceObservation { ~ResourceObservation(); };
struct SceneBaseObservation {
    virtual ~SceneBaseObservation();
    GlobalLifetimeObservation globals;
};
struct SceneRecordObservation {
    unsigned char flags;
    char* firstBuffer;
    char* secondBuffer;
    char* thirdBuffer;
    SceneRecordObservation();
    ~SceneRecordObservation();
};
SceneRecordObservation::SceneRecordObservation()
    : flags(0), firstBuffer(0), secondBuffer(0), thirdBuffer(0) {}
SceneRecordObservation::~SceneRecordObservation() {
    flags=0;
    delete [] firstBuffer;
    delete [] secondBuffer;
    delete [] thirdBuffer;
}
extern void ObserveModeExit();
extern void ObserveModeConfiguration(unsigned mode);
extern void ObserveModeRestore();
struct MusicSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
    IDirect3DTexture8* textures[4];
    SceneRecordObservation records[60];
    ~MusicSceneObservation();
};
MusicSceneObservation::~MusicSceneObservation() {
    textures[0]->Release();
    textures[1]->Release();
    textures[2]->Release();
    textures[3]->Release();
    if (resource) delete resource;
    ObserveModeExit();
    ObserveModeConfiguration(40);
    ObserveModeRestore();
}
extern const unsigned long MusicSceneObservationSizes[] = {
    sizeof(GlobalLifetimeObservation),sizeof(SceneRecordObservation),
    sizeof(SceneBaseObservation),sizeof(MusicSceneObservation)
};
struct ImplicitRecordObservation {
    unsigned char flags;
    char* firstBuffer;
    char* secondBuffer;
    char* thirdBuffer;
};
void EndImplicitRecordLifetime(ImplicitRecordObservation* value) {
    value->~ImplicitRecordObservation();
}
struct ImplicitMusicSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
    IDirect3DTexture8* textures[4];
    ImplicitRecordObservation records[60];
};
void ExerciseImplicitMusicSceneLifetime() {
    ImplicitMusicSceneObservation value;
}
extern const unsigned long MusicImplicitObservationSizes[] = {
    sizeof(ImplicitRecordObservation),sizeof(ImplicitMusicSceneObservation)
};
