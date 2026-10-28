#include <windows.h>
#include <d3d8.h>
// Two natural full MSVC7.1 /GX original resource destructor lifetimes.
// Owner prefix bytes are observed offsets, not inferred private fields.
class FighterPatternCollectionF491 {
public: void Clear(); ~FighterPatternCollectionF491();
};
class FighterResourcesF491 {
 unsigned char opaqueObservedOwnerBytes[0x7D0];
 FighterPatternCollectionF491 patterns;
public:~FighterResourcesF491();
};
FighterResourcesF491::~FighterResourcesF491() { patterns.Clear(); }
class D3DSharedResourceF491 {public: ~D3DSharedResourceF491();};
class SharedWindowResourceF491 {
 IDirect3DTexture8* originalInterface;
 unsigned char opaqueObservedOwnerBytes[0x24];
 D3DSharedResourceF491 resources;
public:~SharedWindowResourceF491();
};
SharedWindowResourceF491::~SharedWindowResourceF491() { originalInterface->Release(); }
