#pragma once

#include "SceneBase.hpp"

class TextureManagerF198;

class LoadingScene : public SceneBase {
public:
    LoadingScene();
    virtual ~LoadingScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    TextureManagerF198* texture;
    unsigned char loaded;
};

class LogoScene : public SceneBase {
public:
    LogoScene();
    virtual ~LogoScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();

    TextureManagerF198* texture;
    unsigned short elapsedFrames;
};
