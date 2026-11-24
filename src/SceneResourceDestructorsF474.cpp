#include "NameEntryScenes.hpp"
#include "SequenceScenes.hpp"
#include "TextureManagerF198.hpp"
#include "ResultScene.hpp"
#include "TitleScene.hpp"

class SceneTextureF474 {public:~SceneTextureF474();};
OpeningScene::~OpeningScene() { if(texture) delete texture; }
PlayerNameEntryScene::~PlayerNameEntryScene() { if(texture) delete texture; }
SharedNameEntryScene::~SharedNameEntryScene() { if(texture) delete texture; }
ResultScene::~ResultScene() { if(textures) delete static_cast<SceneTextureF474*>(textures); }
StaffRollScene::~StaffRollScene() { if(texture) delete texture; }

// The title scene keeps its menu selection for the next visit.
short g_TitleSelectionAt00671630;
TitleScene::~TitleScene() {
  g_TitleSelectionAt00671630=menuIndex;
  if(textures) delete static_cast<SceneTextureF474*>(textures);
}
