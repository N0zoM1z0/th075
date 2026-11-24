#ifndef TH075_RESULT_LIST_SCENE_HPP
#define TH075_RESULT_LIST_SCENE_HPP
#include "SceneBase.hpp"
#include <d3d8.h>
#include <deque>
struct IDirect3DTexture8;
class TextureManagerF198;

// Result-list browser (separate from the match-scoring ResultScene).
// Only observed fields are declared; never instantiate or infer its full size.
class ResultListScene : public SceneBase {
public:
    ResultListScene();
    virtual ~ResultListScene();
    virtual unsigned short Update();  // slot 1, 0042F970
    virtual void Render();             // slot 2, 00430080
    void PollInput();                  // 00430D80
    void LoadSelectedCharacterResources();
    void LoadEncodedCards(const char* character, const char* resourceName);
    void LoadPlainCards(const char* character);
    void ClearEntries();
    void BuildRecordPage();
    void BuildCounterPage();
    void DrawCounter(float x, float y, DWORD color, int number, int style);
    void DrawNameGlyphs(float x, float y, DWORD color, const signed char* name);
    void DrawRankLabel(float x, float y, unsigned int color, signed char rank);

    TextureManagerF198* mainTexture;     // +008
    TextureManagerF198* auxiliaryTexture; // +00C
    IDirect3DTexture8* canvas;        // +010
    void* selectedRecord;              // +014
    std::deque<char*> records;        // +018, owned card names
    unsigned char unknown02C[0x1BC - 0x02C];
    short pageIndex;                   // +1BC
    unsigned char displayAlpha;        // +1BE
    signed char horizontalInput;       // +1BF
    signed char verticalInput;         // +1C0
    signed char confirmInput;          // +1C1
    signed char cancelInput;           // +1C2
    signed char selectedCharacter;     // +1C3
    signed char difficultyIndex;       // +1C4
    signed char showingRecords;        // +1C5
    unsigned char selectableCharacter[10]; // +1C6..+1CF
};
typedef char ResultListDequeSize[(sizeof(std::deque<char*>) == 20) ? 1 : -1];
#endif
