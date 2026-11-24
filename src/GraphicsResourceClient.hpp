#ifndef TH075_GRAPHICS_RESOURCE_CLIENT_HPP
#define TH075_GRAPHICS_RESOURCE_CLIENT_HPP

// WinMain constructs this one-byte, stateless client in a standalone slot.
// Its lifetime updates the shared D3D client count.
class GraphicsResourceClient
{
public:
    GraphicsResourceClient();
    ~GraphicsResourceClient();
};

#endif
