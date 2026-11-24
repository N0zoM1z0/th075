#include "Graphics.hpp"
#include "TextureManagerF198.hpp"

class SpriteDrawingF736 {
public:
    void DrawOpaqueSprite(int a, int b, int c, int tint);
    void DrawOpaqueSpriteWhite(int a, int b, int c);
};
void SpriteDrawingF736::DrawOpaqueSpriteWhite(int a, int b, int c) {
    DrawOpaqueSprite(a, b, c, -1);
}
void TextureManagerF198::GetTextureRect(int index,RECT* rectangle) {
    rectangle->left = 0;
    rectangle->top = 0;
    rectangle->right = entries[index].storedWidth;
    rectangle->bottom = entries[index].storedHeight;
}
