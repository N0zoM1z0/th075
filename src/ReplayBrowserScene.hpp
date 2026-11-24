#pragma once

#include "ReplaySegmentedQueueF219.hpp"
#include "SceneBase.hpp"

class TextureManagerF198;

class ReplayBrowserScene : public SceneBase {
public:
    ReplayBrowserScene();
    virtual ~ReplayBrowserScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();
    void ScanFiles();
    void DrawFilename(float x, float y, DWORD color, const char* filename);
    void DrawNameGlyphs(float x, float y, DWORD color, const signed char* name);
    void DrawMetadataNumber(float x, float y, DWORD color, int value, int digits);

    TextureManagerF198* texture;
    std::deque<char*> filenames;
    std::deque<ReplayFileHeaderF219> headers;
    std::deque<unsigned char> secondaryModes;
    short field048;
    short field04A;
    unsigned char field04C;
    signed char field04D;
    signed char field04E;
    signed char field04F;
    signed char field050;
    signed char field051;
};
