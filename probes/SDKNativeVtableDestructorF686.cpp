// F686 diagnostic original SDK-style 19-byte virtual destructor C++ grammar.
#include <stdlib.h>
class SDKNativeVtableDestructorF686 { public: virtual ~SDKNativeVtableDestructorF686(); };
SDKNativeVtableDestructorF686::~SDKNativeVtableDestructorF686()
{
    ::free(*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x104c));
}
