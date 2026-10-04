// Real supplied SDK jump-buffer/SEH interfaces and independent behavior controls.
// Original private unwind/NLG register contracts and live saved state are unknown.
#include <stddef.h>
#include <windows.h>
#include <setjmp.h>
#include <excpt.h>

extern "C" const unsigned long JumpUnwindLayoutProbe[] = {
    sizeof(void *), sizeof(unsigned long), sizeof(jmp_buf), sizeof(_JUMP_BUFFER),
    offsetof(_JUMP_BUFFER, Ebp), offsetof(_JUMP_BUFFER, Ebx),
    offsetof(_JUMP_BUFFER, Edi), offsetof(_JUMP_BUFFER, Esi),
    offsetof(_JUMP_BUFFER, Esp), offsetof(_JUMP_BUFFER, Eip),
    offsetof(_JUMP_BUFFER, Registration), offsetof(_JUMP_BUFFER, TryLevel),
    offsetof(_JUMP_BUFFER, Cookie), offsetof(_JUMP_BUFFER, UnwindFunc),
    offsetof(_JUMP_BUFFER, UnwindData), sizeof(((_JUMP_BUFFER *)0)->UnwindData),
    offsetof(NT_TIB, ExceptionList), sizeof(DWORD), EXCEPTION_ACCESS_VIOLATION,
    EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH, EXCEPTION_CONTINUE_EXECUTION
};

extern "C" __declspec(noreturn) void JumpTransferControl(jmp_buf saved, int value) {
    longjmp(saved, value);
}
extern "C" int JumpCaptureControl(jmp_buf saved) { return setjmp(saved); }
extern "C" int JumpResultControl(int value) { return value ? value : 1; }
extern "C" unsigned long JumpCookieControl(const _JUMP_BUFFER *saved) {
    return saved->Cookie;
}
extern "C" unsigned long JumpSavedReturnControl(const _JUMP_BUFFER *saved) {
    return saved->Eip;
}

extern "C" int __stdcall IndependentReadProbeControl(const volatile DWORD *address) {
    __try {
        (void)*address;
        return 1;
    } __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) {
        return 0;
    }
}
extern "C" int IndependentFilterControl(DWORD code) {
    return code == EXCEPTION_ACCESS_VIOLATION
        ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}

extern "C" void IndependentFinallyControl(volatile DWORD *state, DWORD value) {
    __try {
        *state = value;
    } __finally {
        *state = *state + 1;
    }
}
