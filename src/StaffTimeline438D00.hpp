#pragma once
#include "Graphics.hpp"

// Pointer-only interfaces; the complete original owner layouts are unknown.
class StaffTimeline438D00 { public: void RenderTimeline(); };
class TimelineDrawing438D00 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void SetTextureFilter(int);
    void DrawSprite(int, float, float, DWORD, float, float, float, float, unsigned char);
};
