// Complete vendor thread/math types and a synthetic code/name pair control.
#include <stddef.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <fpieee.h>
#include <cruntime.h>
#include <mtdll.h>

class CallbackControl {
public:
    void destroy();
};
typedef void (CallbackControl::*DestructorCallback)();
struct MathNamePairControl {
    int operation;
    const char *name;
};

extern "C" const unsigned long ShortRuntimeLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(_tiddata),
    offsetof(_tiddata, _holdrand), RAND_MAX, sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    _FpCodeFabs, sizeof(_FP80), sizeof(DestructorCallback),
    sizeof(MathNamePairControl), offsetof(MathNamePairControl, operation),
    offsetof(MathNamePairControl, name), EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH
};

extern "C" void __stdcall ShortRuntimeCallbackProbe(CallbackControl *element, DestructorCallback callback) {
    (element->*callback)();
}
