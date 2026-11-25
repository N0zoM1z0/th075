#ifndef TH075_SCENE_BASE_HPP
#define TH075_SCENE_BASE_HPP

#include "config/GameDefaultsF193.hpp"

class SceneBase {
public:
    SceneBase();
    virtual ~SceneBase() = 0;
    virtual unsigned short Update() = 0;
    virtual void Render() = 0;
    unsigned short TranslateState(unsigned short mode);

private:
    GameDefaultsF193 defaults;
};
typedef char SceneBaseSize[sizeof(SceneBase) == 8 ? 1 : -1];
#endif
