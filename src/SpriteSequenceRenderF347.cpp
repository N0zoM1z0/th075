#include "GeometryConstants.hpp"
#include "TextureManagerF198.hpp"
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
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
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
struct NativeSequenceDrawRecordF347 {
    short textureIndex;
    unsigned char unknown002[2];
    SpriteQuad40CA80 quad;
    unsigned char unknown088[8];
    NativeScaleTripleF336 projection;
    DWORD tint;
    unsigned char blendMode;
};
class SpriteSequenceF261 { public: void RenderElements(); public:
    // Observed fields; meanings not yet known.
    void* field000;
    unsigned char unknown004[0x010 - 0x004];
    signed char field010;
    unsigned char unknown011[0x012 - 0x011];
    short field012;
    unsigned long field014;
};
#define DRAW_RECORD (reinterpret_cast<const NativeSequenceDrawRecordF347*>(it.operator->()))
#define LIST reinterpret_cast<SequenceListF261*>(reinterpret_cast<unsigned char*>(this)+4)
#define DRAWER field000
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
        state.x=g_CombatViewOffsetX-GeometryConstants::HundredSixty;
        float y=g_CombatViewOffsetY;
        state.quad.Construct();
        {
        state.counter=0;
        for (;it!=state.end;it++,++state.counter) {
            if (state.counter%field010==field010-1) {

                reinterpret_cast<TextureManagerF198*>(DRAWER)->GetTextureRect(DRAW_RECORD->textureIndex,&state.rect);
                switch(DRAW_RECORD->blendMode) {
                case 0: reinterpret_cast<TextureManagerF198*>(DRAWER)->SetBlendMode(0); break;
                case 1: reinterpret_cast<TextureManagerF198*>(DRAWER)->SetBlendMode(2); break;
                case 2: reinterpret_cast<TextureManagerF198*>(DRAWER)->SetBlendMode(3); break;
                }
                QUAD=DRAW_RECORD->quad;
                state.tint=(((DRAW_RECORD->tint>>24)*state.counter)/field012<<24)
                    | (field014&DRAW_RECORD->tint);
                TRANSLATE(QUAD)->TranslateQuad(state.x,y+GeometryConstants::FourHundredTwenty,0.0f);
                if (DRAW_RECORD->projection.x!=0.0f ||
                    DRAW_RECORD->projection.y!=0.0f ||
                    DRAW_RECORD->projection.z!=0.0f) {
                    reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawProjectedQuad(DRAW_RECORD->textureIndex,QUAD,&state.rect,
                        DRAW_RECORD->projection.x,DRAW_RECORD->projection.y,
                        DRAW_RECORD->projection.z,state.tint);
                } else {
                    reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawQuad(DRAW_RECORD->textureIndex,QUAD,&state.rect,state.tint);
                }
            }
        }
        }
    }
}
#undef DRAW_RECORD
#undef LIST
#undef DRAWER
#undef QUAD
#undef TRANSLATE
