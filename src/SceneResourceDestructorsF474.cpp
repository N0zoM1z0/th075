#include "ResultScene.hpp"

// Five complete 127-byte scene destructors; the base scene and texture
// destructors they call are already declared elsewhere.
class NativeSceneBaseF474 {
  void* nativeConfiguration;
public: NativeSceneBaseF474();virtual ~NativeSceneBaseF474();
};
class SceneTextureF474 {public:~SceneTextureF474();};
class OpeningSceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:OpeningSceneReleaseF474();virtual ~OpeningSceneReleaseF474();
};
class ReplaySceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:ReplaySceneReleaseF474();virtual ~ReplaySceneReleaseF474();
};
class NameEntrySceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:NameEntrySceneReleaseF474();virtual ~NameEntrySceneReleaseF474();
};
class StaffRollSceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
public:StaffRollSceneReleaseF474();virtual ~StaffRollSceneReleaseF474();
};
OpeningSceneReleaseF474::~OpeningSceneReleaseF474() { if(texture) delete texture; }
ReplaySceneReleaseF474::~ReplaySceneReleaseF474() { if(texture) delete texture; }
NameEntrySceneReleaseF474::~NameEntrySceneReleaseF474() { if(texture) delete texture; }
ResultScene::~ResultScene() { if(textures) delete static_cast<SceneTextureF474*>(textures); }
StaffRollSceneReleaseF474::~StaffRollSceneReleaseF474() { if(texture) delete texture; }

// The real title-scene member at +0x38 is read before resource deletion.
// The gap from the proven +8 texture through +0x37 is a physical carrier,
// not an assertion about other private fields.
extern short g_TitleSelectionAt00671630;
class TitleSceneReleaseF474:public NativeSceneBaseF474 {
  SceneTextureF474* texture;
  unsigned char untypedObservedOwnerRegion[0x2C];
  signed char actualSelectionAt0038;
public:TitleSceneReleaseF474();virtual ~TitleSceneReleaseF474();
};
TitleSceneReleaseF474::~TitleSceneReleaseF474() {
  g_TitleSelectionAt00671630=actualSelectionAt0038;
  if(texture) delete texture;
}
