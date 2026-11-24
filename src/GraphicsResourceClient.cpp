#include "GraphicsResourceClient.hpp"

// Shared count at 0x00671210. Increment and zero tests determine its use.
int g_GraphicsResourceClientCount;

// 0x00401000..0x0040101A. Its paired cleanup at 0x00401020 decrements this
// count and releases shared D3D interfaces only when the count becomes zero.
GraphicsResourceClient::GraphicsResourceClient()
{
    ++g_GraphicsResourceClientCount;
}
