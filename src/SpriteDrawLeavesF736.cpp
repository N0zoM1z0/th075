#include "Graphics.hpp"
#include "TextureManagerF198.hpp"

class SpriteDrawingF736 {
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
    rectangle->right = reinterpret_cast<TextureManagerF198*>(this)->entries[index].storedWidth;
    rectangle->bottom = reinterpret_cast<TextureManagerF198*>(this)->entries[index].storedHeight;
}
