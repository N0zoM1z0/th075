#include "GraphicsResourceClient.hpp"

// Target storage at 0x00671210. Only its 32-bit width and increment/decrement
// protocol are observed; int is a probe declaration, not recovered signedness.
extern int g_GraphicsResourceClientCount;

// 0x00401000..0x0040101A. Its paired cleanup at 0x00401020 decrements this
// count and releases shared D3D interfaces only when the count becomes zero.
GraphicsResourceClient::GraphicsResourceClient()
{
    ++g_GraphicsResourceClientCount;
}
