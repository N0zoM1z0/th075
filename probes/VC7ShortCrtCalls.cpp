#include <stdlib.h>
#include <float.h>
#include <setjmp.h>
#include <stddef.h>
#include <string.h>

struct ThreeWordObservation { unsigned long words[3]; };

int ParseDecimalText(const char* text) { return atoi(text); }
int CheckFiniteSdk(double value) { return _finite(value); }
char* FormatUnsignedWide(unsigned __int64 value, char* buffer, int radix) {
    return _ui64toa(value, buffer, radix);
}
void RestoreSdkJump(jmp_buf buffer, int result) { longjmp(buffer, result); }
unsigned long ReadJumpRegistration(const _JUMP_BUFFER* buffer) { return buffer->Registration; }
unsigned long ReadJumpTryLevel(const _JUMP_BUFFER* buffer) { return buffer->TryLevel; }

// Ordinary source alternatives test ownership ambiguity, not game declarations.
int CheckFiniteExpression(double value) {
    const unsigned short* words = reinterpret_cast<const unsigned short*>(&value);
    return (words[3] & 0x7ff0) != 0x7ff0;
}
void ClearThreeWordObservation(ThreeWordObservation* value) {
    memset(value, 0, sizeof(*value));
}

extern "C" const unsigned long ShortCrtCallLayout[] = {
    sizeof(jmp_buf), sizeof(_JUMP_BUFFER), offsetof(_JUMP_BUFFER, Ebp),
    offsetof(_JUMP_BUFFER, Registration), offsetof(_JUMP_BUFFER, TryLevel),
    sizeof(unsigned long), sizeof(double), sizeof(unsigned short),
    sizeof(ThreeWordObservation), _JBLEN, DBL_MAX_EXP
};
