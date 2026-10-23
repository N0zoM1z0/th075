#pragma once
#include <d3dx8.h>
#include <stddef.h>

// Complete physical packet view, not a claim about original class/member names.
// Four 16-byte coordinate records are used by the quad helpers. The remaining
// 68 bytes are constructed at +0x40, zeroed and copied with the whole packet;
// their original member partition and meaning remain unknown.
struct RenderQuadPayload5E68C0 {
    DWORD words[17];
    RenderQuadPayload5E68C0();
};
class RenderQuadPacket5E68C0 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    RenderQuadPacket5E68C0();
    void BuildQuad(float, float, float, float);
    void BuildQuadFromRect(const RECT*);
};
typedef char RenderQuadPayloadSize5E68C0[(sizeof(RenderQuadPayload5E68C0) == 68) ? 1 : -1];
typedef char RenderQuadPayloadOffset5E68C0[(offsetof(RenderQuadPacket5E68C0, payload) == 64) ? 1 : -1];
typedef char RenderQuadPacketSize5E68C0[(sizeof(RenderQuadPacket5E68C0) == 132) ? 1 : -1];

// Pointer-only receiver views; never construct or embed these partial owners.
class RenderTexture5E68C0 {
public:
    void SetTextureFilter(int);
};
class RenderDrawing5E68C0 {
public:
    void DrawQuad(int, const RenderQuadPacket5E68C0*, const RECT*, DWORD);
};
class CharacterSpecial5E68C0 {
public:
    void RenderStage(signed char);
};
