#include "ui/LoadingLogoScenes.hpp"
#include "graphics/TextureManagerF198.hpp"

LoadingScene::~LoadingScene() {
    if(texture) delete texture;
}
LogoScene::~LogoScene() {
    if(texture) delete texture;
}
