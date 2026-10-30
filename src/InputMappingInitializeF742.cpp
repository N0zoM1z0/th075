#include "InputJoystick.hpp"
#include <string.h>

// F742: original InputMapping initializer calls the true native
// InputResourceClient ctor on base ECX without adjustment, then zeroes
// two ACTUALLY used contiguous native storage ranges. Original class
// member semantics beyond these physical sizes/offsets remain unknown.
class InputMappingF742 : public InputResourceClient {
    unsigned char realOriginalBaseTail[4];
    unsigned char realMappingAt4[40];
    unsigned char realAxesAt2C[28];
public:
    InputMappingF742();
};
typedef char CheckInitMappingRealLayoutF742[
    (sizeof(InputMappingF742)==72)?1:-1];

InputMappingF742::InputMappingF742() {
    memset(realAxesAt2C,0,28);
    memset(realMappingAt4,0,40);
}
