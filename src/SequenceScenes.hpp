#pragma once

#include "SceneBase.hpp"

class TextureManagerF198;

class OpeningScene : public SceneBase {
public:
    OpeningScene();
    virtual ~OpeningScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();

    TextureManagerF198* texture;
    unsigned int elapsed;
    unsigned int startTicks;
};

class StaffRollScene : public SceneBase {
public:
    StaffRollScene();
    virtual ~StaffRollScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollSkipInput();
    void AdvanceHookAt00438CF0();

    TextureManagerF198* texture;
    unsigned int elapsed;
    unsigned int startTicks;
};
