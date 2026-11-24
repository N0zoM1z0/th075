#pragma once

#include "SceneBase.hpp"

class BattleEndScene : public SceneBase {
public:
    BattleEndScene();
    virtual ~BattleEndScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();

    unsigned char unknown008[4];
};
