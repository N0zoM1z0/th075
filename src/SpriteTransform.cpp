#include "SpriteTransform.hpp"
#include "MathLookup.hpp"

extern float g_ZeroFloat;

void SpriteTransform::BuildQuadFromRect(const RECT *rectangle)
{
    corners_[0] = D3DXVECTOR4(static_cast<float>(rectangle->left),
        static_cast<float>(rectangle->top), 0.0f, 0.0f);
    corners_[1] = D3DXVECTOR4(static_cast<float>(rectangle->right),
        static_cast<float>(rectangle->top), 0.0f, 0.0f);
    corners_[2] = D3DXVECTOR4(static_cast<float>(rectangle->right),
        static_cast<float>(rectangle->bottom), 0.0f, 0.0f);
    corners_[3] = D3DXVECTOR4(static_cast<float>(rectangle->left),
        static_cast<float>(rectangle->bottom), 0.0f, 0.0f);
}

void SpriteTransform::BuildQuad(float left, float top, float right, float bottom)
{
    corners_[0] = D3DXVECTOR4(left, top, 0.0f, 0.0f);
    corners_[1] = D3DXVECTOR4(right, top, 0.0f, 0.0f);
    corners_[2] = D3DXVECTOR4(right, bottom, 0.0f, 0.0f);
    corners_[3] = D3DXVECTOR4(left, bottom, 0.0f, 0.0f);
}

void SpriteTransform::TranslateQuad(float x, float y, float z)
{
    corners_[0].x = x + corners_[0].x;
    corners_[0].y = y + corners_[0].y;
    corners_[0].z = z + corners_[0].z;
    corners_[3].x = x + corners_[3].x;
    corners_[3].y = y + corners_[3].y;
    corners_[3].z = z + corners_[3].z;
    corners_[1].x = x + corners_[1].x;
    corners_[1].y = y + corners_[1].y;
    corners_[1].z = z + corners_[1].z;
    corners_[2].x = x + corners_[2].x;
    corners_[2].y = y + corners_[2].y;
    corners_[2].z = z + corners_[2].z;
}

void SpriteTransform::ScaleQuad(float x, float y, float z,
    float scaleX, float scaleY, float scaleZ)
{
    if (scaleX != 1.0f)
    {
        corners_[0].x = (corners_[0].x - x) * scaleX + x;
        corners_[3].x = (corners_[3].x - x) * scaleX + x;
        corners_[1].x = (corners_[1].x - x) * scaleX + x;
        corners_[2].x = (corners_[2].x - x) * scaleX + x;
    }
    if (scaleY != 1.0f)
    {
        corners_[0].y = (corners_[0].y - y) * scaleY + y;
        corners_[3].y = (corners_[3].y - y) * scaleY + y;
        corners_[1].y = (corners_[1].y - y) * scaleY + y;
        corners_[2].y = (corners_[2].y - y) * scaleY + y;
    }
    if (scaleZ != 1.0f)
    {
        corners_[0].z = (corners_[0].z - z) * scaleZ + z;
        corners_[3].z = (corners_[3].z - z) * scaleZ + z;
        corners_[1].z = (corners_[1].z - z) * scaleZ + z;
        corners_[2].z = (corners_[2].z - z) * scaleZ + z;
    }
}

void SpriteTransform::RotateQuad(float x, float y, float z,
    float angleX, float angleY, float angleZ)
{
    D3DXVECTOR4 before;
    float cosine, sine;
    if (angleZ != g_ZeroFloat)
    {
        cosine = MathLookup::ReadCosTable(angleZ);
        sine = MathLookup::ReadPhaseTable(angleZ);
        before = corners_[0];
        corners_[0].x = (before.x - x) * cosine + x - (before.y - y) * sine;
        corners_[0].y = (before.x - x) * sine + y + (before.y - y) * cosine;
        before = corners_[3];
        corners_[3].x = (before.x - x) * cosine + x - (before.y - y) * sine;
        corners_[3].y = (before.x - x) * sine + y + (before.y - y) * cosine;
        before = corners_[1];
        corners_[1].x = (before.x - x) * cosine + x - (before.y - y) * sine;
        corners_[1].y = (before.x - x) * sine + y + (before.y - y) * cosine;
        before = corners_[2];
        corners_[2].x = (before.x - x) * cosine + x - (before.y - y) * sine;
        corners_[2].y = (before.x - x) * sine + y + (before.y - y) * cosine;
    }
    if (angleY != g_ZeroFloat)
    {
        cosine = MathLookup::ReadCosTable(angleY);
        sine = MathLookup::ReadPhaseTable(angleY);
        before = corners_[0];
        corners_[0].x = (before.z - z) * sine + x + (before.x - x) * cosine;
        corners_[0].z = (before.z - z) * cosine + z - (before.x - x) * sine;
        before = corners_[3];
        corners_[3].x = (before.z - z) * sine + x + (before.x - x) * cosine;
        corners_[3].z = (before.z - z) * cosine + z - (before.x - x) * sine;
        before = corners_[1];
        corners_[1].x = (before.z - z) * sine + x + (before.x - x) * cosine;
        corners_[1].z = (before.z - z) * cosine + z - (before.x - x) * sine;
        before = corners_[2];
        corners_[2].x = (before.z - z) * sine + x + (before.x - x) * cosine;
        corners_[2].z = (before.z - z) * cosine + z - (before.x - x) * sine;
    }
    if (angleX != g_ZeroFloat)
    {
        cosine = MathLookup::ReadCosTable(angleX);
        sine = MathLookup::ReadPhaseTable(angleX);
        before = corners_[0];
        corners_[0].y = (before.z - z) * sine + y + (before.y - y) * cosine;
        corners_[0].z = (before.z - z) * cosine + z - (before.y - y) * sine;
        before = corners_[3];
        corners_[3].y = (before.z - z) * sine + y + (before.y - y) * cosine;
        corners_[3].z = (before.z - z) * cosine + z - (before.y - y) * sine;
        before = corners_[1];
        corners_[1].y = (before.z - z) * sine + y + (before.y - y) * cosine;
        corners_[1].z = (before.z - z) * cosine + z - (before.y - y) * sine;
        before = corners_[2];
        corners_[2].y = (before.z - z) * sine + y + (before.y - y) * cosine;
        corners_[2].z = (before.z - z) * cosine + z - (before.y - y) * sine;
    }
}
