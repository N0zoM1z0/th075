#include "InputJoystick.hpp"

// F735: the 19-byte original authored InputMapping release wrapper calls
// the already source-backed 278-byte native InputResourceClient destructor
// at the unchanged receiver offset. Inferred derived type/ABI only;
// the complete historical InputMapping object layout is not proven.
class InputMappingF735 : public InputResourceClient {
public:
    void ReleaseClient();
};

void InputMappingF735::ReleaseClient() {
    InputResourceClient::~InputResourceClient();
}
