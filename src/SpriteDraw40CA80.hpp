#pragma once
#include "StaffTimeline438D00.hpp"
#include "CharacterSpecial5E68C0.hpp"
#include "SpriteQuad.hpp"
#include "GraphicsTexturedDraw.hpp"
#include "CameraUpdate4126C0.hpp"

// Pointer-only interface for the texture lookup entry.
class SpriteTextures40CA80 { public: IDirect3DTexture8* GetTexture(int); };
