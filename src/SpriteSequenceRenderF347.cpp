#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>

// Borrowed list/iterator only: its element and owner layouts are not asserted.
// Native all-three scale comparisons use a right-side literal 0.0f; the
// related x87 load order is source-expression sensitive in VC7.1. The
// 12-byte triple view records only the three observed scalar fields, not
// a reconstructed private sprite element or owning container.
class SequenceIteratorF261 {
    void* cursor;
public:
    bool operator!=(const SequenceIteratorF261&) const;
    unsigned char* operator->() const;
    SequenceIteratorF261 operator++(int);
};
class SequenceListF261 {
public:
    unsigned int size() const;
    SequenceIteratorF261 begin();
    void End(SequenceIteratorF261* out);
};
class SequenceRendererF261 {
public:
    void GetTextureRect(int texture, RECT* rectangle);
    void SetBlendMode(int mode);
    void DrawQuad(int texture, const SpriteQuad40CA80& quad, const RECT* rectangle, DWORD tint);
    void DrawProjectedQuad(int texture, const SpriteQuad40CA80& quad, const RECT* rectangle,
                           DWORD scaleXBits, DWORD scaleYBits, DWORD scaleZBits, DWORD tint);
};
extern float g_CombatViewOffsetX;
extern const float g_SequenceBaseOffsetAt00657834;
extern float g_CombatViewOffsetY;
extern const float g_SequenceYOffsetAt00657830;
extern const float g_SequenceDefaultScaleAt0065782C;
struct NativeQuadCarrierF331 {
    DWORD words[33];
    void Construct(); // original native 0040D990 SpriteQuad ctor via borrowed thiscall ABI
};
typedef char TestNativeQuadCarrierF331[(sizeof(NativeQuadCarrierF331)==132)?1:-1];
struct NativeSequenceStateF331 {
    int counter;
    RECT rect;
    SequenceIteratorF261 end;
    float x;
    DWORD tint;
    NativeQuadCarrierF331 quad;
};
struct NativeScaleTripleF336 {float x,y,z;};
class SpriteSequenceF261 { public: void RenderElements(); public:
    // Observed fields; meanings not yet known.
    void* field000;
    unsigned char unknown004[0x010 - 0x004];
    signed char field010;
    unsigned char unknown011[0x012 - 0x011];
    short field012;
    unsigned long field014;
};
#define REC(type,p,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(p)+(off)))
#define LIST reinterpret_cast<SequenceListF261*>(reinterpret_cast<unsigned char*>(this)+4)
#define DRAWER reinterpret_cast<SequenceRendererF261*>(field000)
#define QUAD (*reinterpret_cast<SpriteQuad40CA80*>(&state.quad))
#define TRANSLATE(q) reinterpret_cast<SpriteTransform*>(&(q))
void SpriteSequenceF261::RenderElements()
{
    if (!LIST->size()) return;
    if (field010<=0) return;
    {
        SequenceIteratorF261 it=LIST->begin();
        NativeSequenceStateF331 state;
        LIST->End(&state.end);
        state.x=g_CombatViewOffsetX-g_SequenceBaseOffsetAt00657834;
        float y=g_CombatViewOffsetY;
        state.quad.Construct();
        {
        state.counter=0;
        for (;it!=state.end;it++,++state.counter) {
            if (state.counter%field010==field010-1) {

                DRAWER->GetTextureRect(REC(short,it.operator->(),0),&state.rect);
                switch(REC(unsigned char,it.operator->(),0xa0)) {
                case 0: DRAWER->SetBlendMode(0); break;
                case 1: DRAWER->SetBlendMode(2); break;
                case 2: DRAWER->SetBlendMode(3); break;
                }
                QUAD=*reinterpret_cast<const SpriteQuad40CA80*>(it.operator->()+4);
                state.tint=(((REC(DWORD,it.operator->(),0x9c)>>24)*state.counter)/field012<<24)
                    | (field014&REC(DWORD,it.operator->(),0x9c));
                TRANSLATE(QUAD)->TranslateQuad(state.x,y+g_SequenceYOffsetAt00657830,0.0f);
                if (reinterpret_cast<NativeScaleTripleF336*>(it.operator->()+0x90)->x!=0.0f ||
                    reinterpret_cast<NativeScaleTripleF336*>(it.operator->()+0x90)->y!=0.0f ||
                    reinterpret_cast<NativeScaleTripleF336*>(it.operator->()+0x90)->z!=0.0f) {
                    DRAWER->DrawProjectedQuad(REC(short,it.operator->(),0),QUAD,&state.rect,
                        REC(DWORD,it.operator->(),0x90),REC(DWORD,it.operator->(),0x94),
                        REC(DWORD,it.operator->(),0x98),state.tint);
                } else {
                    DRAWER->DrawQuad(REC(short,it.operator->(),0),QUAD,&state.rect,state.tint);
                }
            }
        }
        }
    }
}
#undef REC
#undef LIST
#undef DRAWER
#undef QUAD
#undef TRANSLATE
