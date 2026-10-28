#include <windows.h>
class PackedFontUnitF293 {
public:
 bool IsDoubleByte(char lead);
 unsigned char DecodeUnit(const unsigned int* input,unsigned int* output);
};
unsigned char PackedFontUnitF293::DecodeUnit(const unsigned int* input,unsigned int* output)
{
 if (IsDoubleByte(static_cast<char>(*input))) {
     *output=((*input&0xffu)<<8)|static_cast<int>(*input&0xff00u)>>8;
     return 2;
 }
 *output=static_cast<char>(*input);
 return 1;
}
