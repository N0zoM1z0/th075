#include <windows.h>

// Observed four 16-byte xyzw vertex components and a separately constructed
// fifth component at +64. Receiver and component interfaces are borrowed
// physical views; the original complete sprite class is not instantiated.
class SpriteVertexF211 {
    float x,y,z,w;
public:
    SpriteVertexF211();
    SpriteVertexF211(float xValue, float yValue, float zValue, float wValue);
};
typedef char AssertVertex16F211[(sizeof(SpriteVertexF211)==16)?1:-1];
class SpriteExtraF211 {
public:
    SpriteExtraF211();
};
class SpriteRectF211 {
    SpriteVertexF211 topLeft,topRight,bottomRight,bottomLeft;
    SpriteExtraF211 extra;
public:
    SpriteRectF211(const RECT* bounds);
};
SpriteRectF211::SpriteRectF211(const RECT* bounds)
{
    topLeft = SpriteVertexF211((float)bounds->left, (float)bounds->top, 0.0f, 0.0f);
    topRight = SpriteVertexF211((float)bounds->right, (float)bounds->top, 0.0f, 0.0f);
    bottomRight = SpriteVertexF211((float)bounds->right, (float)bounds->bottom, 0.0f, 0.0f);
    bottomLeft = SpriteVertexF211((float)bounds->left, (float)bounds->bottom, 0.0f, 0.0f);
}
