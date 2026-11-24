#include "LoadingLogoScenes.hpp"
#include "TextureManagerF198.hpp"

LoadingScene::~LoadingScene() {
    if(texture) delete texture;
}
LogoScene::~LogoScene() {
    if(texture) delete texture;
}
