#include "TextOverlay.hpp"
#include "GraphicsTexture.hpp"
extern const char g_WindowResourceFileAt00657898[] = "data\\system\\window.dat";
extern const char g_WindowResourceRootAt00657890[] = "data";
TextOverlay::TextOverlay() {
 textureManager.AllocateUnformattedSlots(1);
 textureManager.LoadDefault(g_WindowResourceFileAt00657898,g_WindowResourceRootAt00657890);
 Graphics::CreateTexture(1024, 512, &texture, 0x20);
}
