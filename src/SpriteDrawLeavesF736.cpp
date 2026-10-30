#include "Graphics.hpp"

// F736: two complete R011 sprite drawing small authored functions.
// The caller-visible RECT, +8 owner subobject and +4/+8 record fields
// are original machine-code observations; complete class layout unknown.
struct NativeSpriteRectRecordF736 {
    unsigned int nativeWord0;
    int rightAt4;
    int bottomAt8;
};
class NativeSpriteRectListF736 {
public: NativeSpriteRectRecordF736* At(int index);
};
class SpriteDrawingF736 {
    unsigned int sourceOwnedPrefixAt0And4[2];
    NativeSpriteRectListF736 rectRecordsAt8;
public:
    void DrawOpaqueSprite(int a, int b, int c, int tint);
    void DrawOpaqueSpriteWhite(int a, int b, int c);
    void GetTextureRect(int index,RECT* rectangle);
};
void SpriteDrawingF736::DrawOpaqueSpriteWhite(int a, int b, int c) {
    DrawOpaqueSprite(a, b, c, -1);
}
void SpriteDrawingF736::GetTextureRect(int index,RECT* rectangle) {
    rectangle->left = 0;
    rectangle->top = 0;
    rectangle->right = rectRecordsAt8.At(index)->rightAt4;
    rectangle->bottom = rectRecordsAt8.At(index)->bottomAt8;
}
