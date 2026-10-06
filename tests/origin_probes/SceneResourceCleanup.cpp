// Complete compact lifetime alternatives; no original private game layout.
struct ResourceObservation { ~ResourceObservation(); };
struct GlobalLifetimeObservation {
    GlobalLifetimeObservation();
    ~GlobalLifetimeObservation();
};
struct SceneBaseObservation {
    virtual ~SceneBaseObservation();
    GlobalLifetimeObservation globals;
};
struct ExplicitSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
    ~ExplicitSceneObservation();
};
ExplicitSceneObservation::~ExplicitSceneObservation() {
    if (resource) delete resource;
}
struct ImplicitSceneObservation : SceneBaseObservation {
    ResourceObservation* resource;
};
void DestroyImplicitSceneObservation(ImplicitSceneObservation* value) {
    value->~ImplicitSceneObservation();
}
extern const unsigned long SceneLifetimeSizes[] = {
    sizeof(ResourceObservation),sizeof(SceneBaseObservation),
    sizeof(ExplicitSceneObservation),sizeof(ImplicitSceneObservation)
};
void ExerciseImplicitSceneLifetime() {
    ImplicitSceneObservation value;
}
struct OwnedResourceObservation {
    ResourceObservation* resource;
    ~OwnedResourceObservation();
};
OwnedResourceObservation::~OwnedResourceObservation() {
    if (resource) delete resource;
}
struct ImplicitOwningSceneObservation : SceneBaseObservation {
    OwnedResourceObservation resource;
};
void ExerciseImplicitOwningSceneLifetime() {
    ImplicitOwningSceneObservation value;
}
