// Complete vendor exception types and a synthetic member-call ABI control.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <fpieee.h>

class ElementCallbackControl {
public:
    void construct();
    void destroy();
};
typedef void (ElementCallbackControl::*ElementCallback)();

extern "C" const unsigned long VectorMathParentLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(double), sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    sizeof(ElementCallback), sizeof(_FP80),
    EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH
};

extern "C" void __stdcall VectorMathParentCallbackProbe(ElementCallbackControl *element, ElementCallback callback) {
    (element->*callback)();
}
