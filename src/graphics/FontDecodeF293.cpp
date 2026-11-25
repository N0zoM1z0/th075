#include "graphics/FontSurface.hpp"
unsigned char FontSurface::DecodeUnit(const char* input,int* output)
{
 if (IsDoubleByte(static_cast<char>(*reinterpret_cast<const unsigned int*>(input)))) {
     *output=((*reinterpret_cast<const unsigned int*>(input)&0xffu)<<8)|static_cast<int>(*reinterpret_cast<const unsigned int*>(input)&0xff00u)>>8;
     return 2;
 }
 *output=static_cast<char>(*reinterpret_cast<const unsigned int*>(input));
 return 1;
}
