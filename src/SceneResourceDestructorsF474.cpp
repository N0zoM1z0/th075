#include "SequenceScenes.hpp"
#include "TextureManagerF198.hpp"
#include "ResultScene.hpp"
#include "TitleScene.hpp"

// Five complete 127-byte scene destructors; the base scene and texture
// destructors they call are already declared elsewhere.
class NativeSceneBaseF474 {
  void* nativeConfiguration;
public: NativeSceneBaseF474();virtual ~NativeSceneBaseF474();
};
class SceneTextureF474 {public:~SceneTextureF474();};
class ReplaySceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:ReplaySceneReleaseF474();virtual ~ReplaySceneReleaseF474();
};
class NameEntrySceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:NameEntrySceneReleaseF474();virtual ~NameEntrySceneReleaseF474();
};
OpeningScene::~OpeningScene() { if(texture) delete texture; }
ReplaySceneReleaseF474::~ReplaySceneReleaseF474() { if(texture) delete texture; }
NameEntrySceneReleaseF474::~NameEntrySceneReleaseF474() { if(texture) delete texture; }
ResultScene::~ResultScene() { if(textures) delete static_cast<SceneTextureF474*>(textures); }
StaffRollScene::~StaffRollScene() { if(texture) delete texture; }

// The title scene keeps its menu selection for the next visit.
extern short g_TitleSelectionAt00671630;
TitleScene::~TitleScene() {
  g_TitleSelectionAt00671630=menuIndex;
  if(textures) delete static_cast<SceneTextureF474*>(textures);
}
