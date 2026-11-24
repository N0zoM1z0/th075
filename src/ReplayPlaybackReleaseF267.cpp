#include "ReplayBrowserScene.hpp"
#include "TextureManagerF198.hpp"
#include <stdlib.h>

extern unsigned short g_ReplayControllerAt0067162C;
ReplayBrowserScene::~ReplayBrowserScene()
{
    g_ReplayControllerAt0067162C=field048;
    for (unsigned int index=0;index<filenames.size();++index) {
        char* ownedName=filenames[index];
        free(ownedName);
    }
    filenames.clear();
    if (texture) delete texture;
}
