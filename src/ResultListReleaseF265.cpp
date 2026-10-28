#include <windows.h>
#include <d3d8.h>

// Only the native-observed result scene boundaries, 20-byte VC7 deque
// lifetime, and borrowed game/D3D8 cleanup calls are represented.
class ResultSceneBaseF265 {
    void* configuration;
public:
    ResultSceneBaseF265();
    virtual ~ResultSceneBaseF265();
};
class ResultTextureF265 {
public:
    ~ResultTextureF265();
};
class ResultRecordsDequeF265 {
    unsigned int physicalWords[5];
public:
    ResultRecordsDequeF265();
    ~ResultRecordsDequeF265();
};
typedef char AssertResultDeque20F265[(sizeof(ResultRecordsDequeF265)==20)?1:-1];
class ResultListReleaseF265 : public ResultSceneBaseF265 {
    ResultTextureF265* mainTexture;
    ResultTextureF265* pageTexture;
    IDirect3DTexture8* canvas;
    void* extraCanvas;
    ResultRecordsDequeF265 records;
public:
    ResultListReleaseF265();
    virtual ~ResultListReleaseF265();
    void ClearEntries();
};
ResultListReleaseF265::~ResultListReleaseF265()
{
    ClearEntries();
    if (pageTexture) delete pageTexture;
    if (mainTexture) delete mainTexture;
    if (canvas) canvas->Release();
}
