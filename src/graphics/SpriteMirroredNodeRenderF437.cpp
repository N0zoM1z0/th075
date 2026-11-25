#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/Actor.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include "battle/BackgroundStageBaseF479.hpp"
#include "engine/GameLeafHelpers.hpp"
#include <windows.h>

// All scene, child, and drawing owner declarations are borrowed call-only
// views: only the two complete native 132-byte stack quad values are owned.
class SpriteRenderDeviceF254 {
public:
};
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;

// Only genuine live native fields are represented, no private scene owner.
// F437 independently reconstructed entire 1,268-byte R035 mirrored-node
// sprite renderer; the native stack has two *observed* 140-byte allocation
// extents even though only 132 bytes in each are decoded as geometry. The
// final eight bytes of each carrier have no asserted private field identity
// and are never read, written or counted separately as additional CODE.
// Comparison of previously exact F129/F126 renderers proves an
// unparenthesized float field lvalue makes VC7.1 emit native FILD/MOV/FSUBR
// rather than nonnative FLD/loaded-index/FISUB. No manual assembly.
// Original stack layout has each independently constructed quad carrier at
// a 140-byte interval, with 132 known rendered packet bytes and two unused
// but physically reserved DWORDs. Only first 132 bytes are ever accessed.
struct RawQuadCarrierF355 { DWORD words[35]; };
typedef char CheckCarrierSizeF355[(sizeof(RawQuadCarrierF355)==140)?1:-1];
struct NativeMirrorFrameF355 {
    RECT sourceRect;
    RawQuadCarrierF355 composed;
    BackgroundStageFloatFieldsF933 tint;
    float xShift;
    DWORD color;
    RawQuadCarrierF355 transformed;
    float yOrigin;
};
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
#define DRAWER reinterpret_cast<SpriteRenderDeviceF254*>(drawing)
// Actor vtable slot 4: the reflection drawn below an actor.
void ActorRenderingBase::RenderMirroredNode()
{
    NativeMirrorFrameF355 state;
#define transformed (*reinterpret_cast<SpriteQuad40CA80*>(&state.transformed))
#define composed (*reinterpret_cast<SpriteQuad40CA80*>(&state.composed))
    // VC7.1 supports a direct constructor call on aligned storage.
    transformed.SpriteQuad40CA80::SpriteQuad40CA80();
    composed.SpriteQuad40CA80::SpriteQuad40CA80();
#define xShift state.xShift
#define yOrigin state.yOrigin
#define sourceRect state.sourceRect
#define color state.color
#define tint state.tint
    xShift = g_CombatViewOffsetX - GeometryConstants::HundredSixty;
    yOrigin = g_CombatViewOffsetY;
    reinterpret_cast<TextureManagerF198*>(DRAWER)->GetTextureRect(drawFrame->textureIndex,&sourceRect);
    TRANSFORM(transformed)->BuildQuadFromRect(&sourceRect);
    if (drawFrame->pose) {
        TRANSFORM(transformed)->ScaleQuad(static_cast<float>(drawFrame->originX),static_cast<float>(drawFrame->originY),0.0f,
              drawFrame->pose->scaleX,
              drawFrame->pose->scaleY,
              drawFrame->pose->scaleZ);
        TRANSFORM(transformed)->RotateQuad(static_cast<float>(drawFrame->originX),static_cast<float>(drawFrame->originY),0.0f,
              drawFrame->pose->rotationX,
              drawFrame->pose->rotationY,
              drawFrame->pose->rotationZ);
        TRANSFORM(transformed)->ScaleQuad(0.0f,0.0f,0.0f,static_cast<float>(facing),1.0f,1.0f);
    } else if (drawFrame->field0C) {
        TRANSFORM(transformed)->ScaleQuad(0.0f,0.0f,0.0f,static_cast<float>(static_cast<int>(facing)<<1),2.0f,2.0f);
    }
    if (field040) {
        TRANSFORM(transformed)->ScaleQuad(static_cast<float>(facing)*(static_cast<float>(drawFrame->originX)+(pivotX)),static_cast<float>(drawFrame->originY)-(pivotY),pivotZ,scaleX,scaleY,scaleZ);
        TRANSFORM(transformed)->RotateQuad(static_cast<float>(facing)*(static_cast<float>(drawFrame->originX)+(pivotX)),static_cast<float>(drawFrame->originY)-(pivotY),pivotZ,rotationX,rotationY,
               static_cast<float>(facing)*(rotationZ));
    }
    TRANSFORM(transformed)->TranslateQuad(x-(facing)*(drawFrame->originX),
                                         -(y)-static_cast<float>(drawFrame->originY),0.0f);
    SpriteScene::DispatchGlobalDraw(&composed,&color,&transformed);
    TRANSFORM(composed)->TranslateQuad(xShift,yOrigin+GeometryConstants::FourHundredTwenty+(field06C),0.0f);
    g_CurrentBattleStageAt00671424->CopyParameters(&tint);
    reinterpret_cast<TextureManagerF198*>(DRAWER)->SetTextureFilter(2);
    if (tint.floatAt0C != FloatConstants::Zero || tint.floatAt10 != FloatConstants::Zero || tint.floatAt14 != FloatConstants::Zero) {
        reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawProjectedQuad(drawFrame->textureIndex,composed,&sourceRect,tint.floatAt0C+xShift,tint.floatAt10+yOrigin,tint.floatAt14,color);
    } else {
        reinterpret_cast<TextureManagerF198*>(DRAWER)->DrawQuad(drawFrame->textureIndex,composed,&sourceRect,color);
    }
    reinterpret_cast<TextureManagerF198*>(DRAWER)->SetTextureFilter(1);
}
#undef tint
#undef color
#undef sourceRect
#undef yOrigin
#undef xShift
#undef composed
#undef transformed
#undef DRAWER
#undef TRANSFORM
