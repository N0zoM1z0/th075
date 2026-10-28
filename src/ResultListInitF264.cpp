#include <windows.h>
#include <new>

// Source-level scene view supports only independently observed fields.
// The queue has the complete physical five-DWORD VC7 deque boundary.
class ResultSceneBaseF264 {
    void* configReference;
public:
    ResultSceneBaseF264();
    virtual ~ResultSceneBaseF264();
};
class ResultRecordsDequeF264 {
    unsigned int physicalWords[5];
public:
    ResultRecordsDequeF264();
    ~ResultRecordsDequeF264();
};
typedef char AssertResultDeque20F264[(sizeof(ResultRecordsDequeF264)==20)?1:-1];
class ResultTextureF264 {
    unsigned char observedNativeBytes[80];
public:
    ResultTextureF264();
    void AllocateSlots(int);
    void Load(const char*,const char*);
};
typedef char AssertResultTexture80F264[(sizeof(ResultTextureF264)==80)?1:-1];
namespace ResultBitmapF264 { void __cdecl Allocate(int width,int height,void** slot,int depth); }
namespace ResultRecordsF264 { unsigned char __cdecl CheckSelection(unsigned char row,int mode); }
extern const char g_ResultListFileAt00658064[];
extern const char g_ResultListRootAt0065805C[];
class ResultListInitializerF264 : public ResultSceneBaseF264 {
    ResultTextureF264* texture;
    void* auxiliaryA;
    void* canvas;
    void* auxiliaryB;
    ResultRecordsDequeF264 records;
public:
    ResultListInitializerF264();
    virtual ~ResultListInitializerF264();
    void LoadCharacterTextures();
    void BuildCounterPage();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ResultListInitializerF264::ResultListInitializerF264()
{
    canvas=0;
    auxiliaryA=0;
    texture=new ResultTextureF264();
    texture->AllocateSlots(4);
    texture->Load(g_ResultListFileAt00658064,g_ResultListRootAt0065805C);
    ResultBitmapF264::Allocate(1024,512,&canvas,32);
    auxiliaryA=0;
    FIELD(unsigned char,0x1c5)=0;
    FIELD(unsigned char,0x1c3)=0;
    FIELD(unsigned char,0x1c4)=0;
    FIELD(short,0x1bc)=0;
    FIELD(unsigned char,0x1be)=5;
    for (int index=0;index<10;++index)
        FIELD(unsigned char,0x1c6+index)=ResultRecordsF264::CheckSelection(static_cast<unsigned char>(index),1);
    LoadCharacterTextures();
    BuildCounterPage();
}
#undef FIELD
