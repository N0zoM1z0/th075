#ifndef TH075_RESULT_LIST_SCENE_HPP
#define TH075_RESULT_LIST_SCENE_HPP
#include "SceneBase.hpp"
#include <d3d8.h>
struct IDirect3DTexture8;
class TextureManagerF198;

// The replay/result browser keeps a five-DWORD VC7 deque at +0x18.
// Its element representation remains unknown; only Count's call contract
// and the deque's observed physical extent are used by this scene.
class ResultListRecords {
    unsigned int physicalWords[5];
public:
    ResultListRecords();
    ~ResultListRecords();
    unsigned int Count() const;
    int Size();
    char** Entry(int index);
};

typedef char ResultListDequePhysicalSize[(sizeof(ResultListRecords) == 20) ? 1 : -1];

// Result-list browser (separate from the match-scoring ResultScene).
// Only observed fields are declared; never instantiate or infer its full size.
class ResultListScene : public SceneBase {
public:
    ResultListScene();
    virtual ~ResultListScene();
    virtual unsigned short Advance();  // slot 1, 0042F970
    virtual void Render();             // slot 2, 00430080
    void PollInput();                  // 00430D80
    void LoadSelectedCharacterResources();
    void LoadEncodedCards(void* cards, const char* resourceName);
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
    ResultListRecords records;         // +018, five native DWORDs
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
#endif
