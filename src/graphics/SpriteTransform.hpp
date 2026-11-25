#ifndef TH075_SPRITE_TRANSFORM_HPP
#define TH075_SPRITE_TRANSFORM_HPP

#include <d3dx8.h>

// Only the first four coordinate records are represented here. The enclosing
// 132-byte owner has additional unknown state. Never instantiate or embed this
// partial interface, or use its sizeof as the original owner's extent.
class SpriteTransform
{
public:
    void BuildQuadFromRect(const RECT *rectangle);
    void BuildQuad(float left, float top, float right, float bottom);
    void TranslateQuad(float x, float y, float z);
    void ScaleQuad(float x, float y, float z, float scaleX, float scaleY, float scaleZ);
    void RotateQuad(float x, float y, float z, float angleX, float angleY, float angleZ);

private:
    D3DXVECTOR4 corners_[4];
};

#endif
