// Complete supplied SDK classes and independent exception ownership/ABI models.
// The private CRT throw record and original link-search decisions remain unknown.
#include <stddef.h>
#include <windows.h>
#include <exception>
#include <typeinfo>
#include <new>
#include <stdlib.h>
#include <string.h>

class IndependentMessageOwner {
public:
    const char *message;
    int owned;

    IndependentMessageOwner() : message(0), owned(0) {}
    IndependentMessageOwner(const IndependentMessageOwner& other)
        : message(other.message), owned(other.owned) {
        if (owned) {
            char *copy = static_cast<char *>(malloc(strlen(other.message) + 1));
            message = copy;
            if (copy) strcpy(copy, other.message);
        }
    }
    IndependentMessageOwner& operator=(const IndependentMessageOwner& other) {
        if (this != &other) {
            this->~IndependentMessageOwner();
            new (this) IndependentMessageOwner(other);
        }
        return *this;
    }
    virtual ~IndependentMessageOwner() {
        if (owned) free(const_cast<char *>(message));
    }
    virtual const char *what() const {
        return message ? message : "independent unspecified message";
    }
};

extern "C" const unsigned long StandardExceptionLayoutProbe[] = {
    sizeof(void *), sizeof(DWORD), sizeof(ULONG_PTR), sizeof(int),
    sizeof(EXCEPTION_RECORD), offsetof(EXCEPTION_RECORD, ExceptionCode),
    offsetof(EXCEPTION_RECORD, ExceptionFlags), offsetof(EXCEPTION_RECORD, NumberParameters),
    offsetof(EXCEPTION_RECORD, ExceptionInformation), EXCEPTION_NONCONTINUABLE,
    EXCEPTION_MAXIMUM_PARAMETERS, sizeof(exception), sizeof(type_info), sizeof(bad_cast),
    sizeof(bad_typeid), sizeof(__non_rtti_object), sizeof(IndependentMessageOwner),
    offsetof(IndependentMessageOwner, message), offsetof(IndependentMessageOwner, owned),
    sizeof(const char *(exception::*)() const), sizeof(void (__stdcall *)(void *, void *)),
    _HAS_EXCEPTIONS
};

extern "C" void StandardExceptionDefaultControl(void *storage) {
    new (storage) exception();
}
extern "C" void StandardExceptionCopyControl(void *storage, const exception *other) {
    new (storage) exception(*other);
}
extern "C" exception& StandardExceptionAssignControl(exception& self, const exception& other) {
    return self = other;
}
extern "C" void StandardExceptionDestroyControl(exception *self) {
    self->exception::~exception();
}
extern "C" const char *StandardExceptionWhatControl(const exception *self) {
    return self->what();
}
extern "C" void StandardExceptionDeleteControl(exception *self) {
    delete self;
}
extern "C" void StandardTypeInfoDestroyControl(type_info *self) {
    self->type_info::~type_info();
}
extern "C" void StandardTypeInfoDeleteControl(type_info *self) {
    delete self;
}
extern "C" void StandardRaiseControl(DWORD code, DWORD flags, DWORD count,
                                      const ULONG_PTR *parameters) {
    RaiseException(code, flags, count, parameters);
}
extern "C" void StandardThrowParametersControl(void *object, const void *descriptor,
                                                DWORD code, ULONG_PTR magic) {
    ULONG_PTR parameters[3] = {magic, reinterpret_cast<ULONG_PTR>(object),
                              reinterpret_cast<ULONG_PTR>(descriptor)};
    RaiseException(code, EXCEPTION_NONCONTINUABLE, 3, parameters);
}
extern "C" void StandardMessageDefaultControl(void *storage) {
    new (storage) IndependentMessageOwner();
}
extern "C" void StandardMessageCopyControl(void *storage, const IndependentMessageOwner *other) {
    new (storage) IndependentMessageOwner(*other);
}
extern "C" void StandardMessageAssignControl(IndependentMessageOwner *self,
                                             const IndependentMessageOwner *other) {
    *self = *other;
}

__declspec(noreturn) void StandardIntegerThrowControl(int value) {
    throw value;
}
int StandardIntegerCatchControl(int value) {
    try {
        StandardIntegerThrowControl(value);
    } catch (int result) {
        return result;
    }
}
