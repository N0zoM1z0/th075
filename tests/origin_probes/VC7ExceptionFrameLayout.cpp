// Real SDK/thread declarations and independent compiler ABI/SEH controls.
// Private CRT FuncInfo, guard and frame-info record types are not declared here.
#include <stddef.h>
#include <windows.h>
#include <excpt.h>
#include <eh.h>
#include <mtdll.h>

class IndependentFrameMember {
public:
    int value;
    void Touch() { ++value; }
    void Copy(void *source) { value = *static_cast<int *>(source); }
    void CopyWithFlag(void *source, int flag) {
        value = *static_cast<int *>(source) + flag;
    }
};

extern "C" const unsigned long ExceptionFrameLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(EXCEPTION_RECORD),
    offsetof(EXCEPTION_RECORD, ExceptionCode), offsetof(EXCEPTION_RECORD, ExceptionFlags),
    offsetof(EXCEPTION_RECORD, ExceptionRecord), offsetof(EXCEPTION_RECORD, ExceptionAddress),
    offsetof(EXCEPTION_RECORD, NumberParameters), offsetof(EXCEPTION_RECORD, ExceptionInformation),
    sizeof(((EXCEPTION_RECORD *)0)->ExceptionInformation), sizeof(EXCEPTION_POINTERS),
    offsetof(EXCEPTION_POINTERS, ExceptionRecord), offsetof(EXCEPTION_POINTERS, ContextRecord),
    sizeof(CONTEXT), sizeof(_tiddata), offsetof(_tiddata, _translator),
    offsetof(_tiddata, _curexception), offsetof(_tiddata, _curcontext),
    offsetof(_tiddata, _pFrameInfoChain), sizeof(_se_translator_function),
    EXCEPTION_NONCONTINUABLE, EXCEPTION_MAXIMUM_PARAMETERS,
    ExceptionContinueExecution, ExceptionContinueSearch, ExceptionNestedException,
    ExceptionCollidedUnwind, static_cast<unsigned long>(EXCEPTION_CONTINUE_EXECUTION),
    EXCEPTION_CONTINUE_SEARCH, EXCEPTION_EXECUTE_HANDLER,
    sizeof(void (IndependentFrameMember::*)()),
    sizeof(void (IndependentFrameMember::*)(void *)),
    sizeof(void (IndependentFrameMember::*)(void *, int))
};

extern "C" void FrameTranslatorCallControl(_se_translator_function worker,
                                               EXCEPTION_RECORD *record, CONTEXT *context) {
    EXCEPTION_POINTERS pointers = {record, context};
    worker(record->ExceptionCode, &pointers);
}

extern "C" void *FrameStdcall3Control(
    void *(__stdcall *worker)(void *, void *, unsigned long),
    void *first, void *second, unsigned long code) {
    return worker(first, second, code);
}

extern "C" void FrameMember0Control(IndependentFrameMember *self,
                                        void (IndependentFrameMember::*worker)()) {
    (self->*worker)();
}
extern "C" void FrameMember1Control(IndependentFrameMember *self,
                                        void (IndependentFrameMember::*worker)(void *),
                                        void *source) {
    (self->*worker)(source);
}
extern "C" void FrameMember2Control(IndependentFrameMember *self,
                                        void (IndependentFrameMember::*worker)(void *, int),
                                        void *source, int flag) {
    (self->*worker)(source, flag);
}

extern "C" void FrameScopeFinallyControl(void (__cdecl *worker)(void *),
                                             void (__cdecl *cleanup)(void *), void *context) {
    __try {
        worker(context);
    } __finally {
        cleanup(context);
    }
}

extern "C" int FrameScopeFilterControl(void (__cdecl *worker)(void *), void *context,
                                            EXCEPTION_POINTERS **observed) {
    __try {
        worker(context);
        return 0;
    } __except((*observed = GetExceptionInformation(),
                GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION
                    ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)) {
        return 1;
    }
}

__declspec(noreturn) void FrameCppThrowControl(int value) {
    throw value;
}

int FrameCppCatchControl(int value) {
    try {
        FrameCppThrowControl(value);
    } catch (int result) {
        return result;
    }
}
