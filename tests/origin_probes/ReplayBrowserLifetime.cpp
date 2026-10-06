#include <deque>
// Complete generic observations, not recovered original scene declarations.
struct SceneBaseObservation {
    unsigned globals;
    virtual ~SceneBaseObservation();
    virtual void Update();
    virtual void Render();
};
struct ChildSceneObservation {
    unsigned state;
    ~ChildSceneObservation();
};
extern unsigned short savedSelectionObservation;
struct ReplayBrowserLifetimeObservation : SceneBaseObservation {
    ChildSceneObservation* child;
    std::deque<unsigned char*> filenames;
    std::deque<unsigned> records;
    std::deque<unsigned char> scratch;
    unsigned short selection;
    ~ReplayBrowserLifetimeObservation();
};
ReplayBrowserLifetimeObservation::~ReplayBrowserLifetimeObservation() {
    savedSelectionObservation = selection;
    unsigned index;
    for (index = 0; index < filenames.size(); ++index)
        delete [] filenames[index];
    filenames.clear();
    if (child)
        delete child;
}
struct EmptyReplayBrowserLifetimeObservation : SceneBaseObservation {
    ChildSceneObservation* child;
    std::deque<unsigned char*> filenames;
    std::deque<unsigned> records;
    std::deque<unsigned char> scratch;
    unsigned short selection;
    ~EmptyReplayBrowserLifetimeObservation();
};
EmptyReplayBrowserLifetimeObservation::~EmptyReplayBrowserLifetimeObservation() {}
struct ImplicitReplayBrowserLifetimeObservation : SceneBaseObservation {
    ChildSceneObservation* child;
    std::deque<unsigned char*> filenames;
    std::deque<unsigned> records;
    std::deque<unsigned char> scratch;
    unsigned short selection;
};
void DestroyImplicitBrowser(ImplicitReplayBrowserLifetimeObservation* value) {
    value->~ImplicitReplayBrowserLifetimeObservation();
}
ImplicitReplayBrowserLifetimeObservation* CreateImplicitBrowser() {
    return new ImplicitReplayBrowserLifetimeObservation;
}
extern const unsigned long ReplayBrowserLifetimeObservationSizes[] = {
    sizeof(SceneBaseObservation),sizeof(ChildSceneObservation),
    sizeof(ReplayBrowserLifetimeObservation),sizeof(std::deque<unsigned char*>),
    sizeof(std::deque<unsigned>),sizeof(std::deque<unsigned char>)
};
