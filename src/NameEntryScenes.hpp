#pragma once

#include "SceneBase.hpp"
#include <windows.h>

class TextureManagerF198;
struct ProgressDifficulty;

class PlayerNameEntryScene : public SceneBase {
public:
    PlayerNameEntryScene();
    virtual ~PlayerNameEntryScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();
    void DrawRankLabel(float x, float y, DWORD tint, signed char rank);
    void DrawNameGlyphs(float x, float y, DWORD tint, const signed char* name);
    void DrawNumber(float x, float y, DWORD tint, int number, int minDigits);

    TextureManagerF198* texture;
    ProgressDifficulty* selectedRecord;
    short field010;
    short field012;
    short field014;
    short field016;
    int pathIndex;
    char replayPath[MAX_PATH];
    signed char rank;
};

class SharedNameEntryScene : public SceneBase {
public:
    SharedNameEntryScene();
    virtual ~SharedNameEntryScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();
    void DrawSaveFilename(float x, float y, DWORD tint, const char* filename);
    void DrawNameGlyphs(float x, float y, DWORD tint, const signed char* name);
    void DrawNumber(float x, float y, DWORD tint, int number, int minDigits);

    TextureManagerF198* texture;
    signed char field00C;
    short field00E;
    short field010;
    short field012;
    short field014;
    short field016;
    int pathIndex;
    char replayPath[MAX_PATH];
};
