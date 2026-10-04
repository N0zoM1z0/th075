// Complete supplied SDK interfaces and an independent inheritance model.
// These controls do not define the original private game or CRT source layout.
#include <exception>
#include <typeinfo.h>
#include <new>

class IndependentCastFailure : public exception {
public:
    explicit IndependentCastFailure(const char *message) : exception(message) {}
    virtual ~IndependentCastFailure() {}
};

class IndependentTypeFailure : public exception {
public:
    explicit IndependentTypeFailure(const char *message) : exception(message) {}
    virtual ~IndependentTypeFailure() {}
};

class IndependentMissingRtti : public IndependentTypeFailure {
public:
    explicit IndependentMissingRtti(const char *message) : IndependentTypeFailure(message) {}
    virtual ~IndependentMissingRtti() {}
};

extern "C" const unsigned long DerivedExceptionLayoutProbe[] = {
    sizeof(void *), sizeof(exception), sizeof(bad_cast), sizeof(bad_typeid),
    sizeof(__non_rtti_object), sizeof(IndependentCastFailure),
    sizeof(IndependentTypeFailure), sizeof(IndependentMissingRtti)
};

extern "C" void DerivedCastMessageControl(void *storage, const char *message) {
    new (storage) bad_cast(message);
}
extern "C" void DerivedCastCopyControl(void *storage, const bad_cast *other) {
    new (storage) bad_cast(*other);
}
extern "C" void DerivedCastDestroyControl(bad_cast *self) {
    self->bad_cast::~bad_cast();
}
extern "C" void DerivedCastDeleteControl(bad_cast *self) { delete self; }
extern "C" void DerivedTypeMessageControl(void *storage, const char *message) {
    new (storage) bad_typeid(message);
}
extern "C" void DerivedTypeCopyControl(void *storage, const bad_typeid *other) {
    new (storage) bad_typeid(*other);
}
extern "C" void DerivedTypeDestroyControl(bad_typeid *self) {
    self->bad_typeid::~bad_typeid();
}
extern "C" void DerivedTypeDeleteControl(bad_typeid *self) { delete self; }
extern "C" void DerivedNonRttiMessageControl(void *storage, const char *message) {
    new (storage) __non_rtti_object(message);
}
extern "C" void DerivedNonRttiCopyControl(void *storage, const __non_rtti_object *other) {
    new (storage) __non_rtti_object(*other);
}
extern "C" void DerivedNonRttiDestroyControl(__non_rtti_object *self) {
    self->__non_rtti_object::~__non_rtti_object();
}
extern "C" void DerivedNonRttiDeleteControl(__non_rtti_object *self) { delete self; }
extern "C" void IndependentCastConstructControl(void *storage, const char *message) {
    new (storage) IndependentCastFailure(message);
}
extern "C" void IndependentTypeConstructControl(void *storage, const char *message) {
    new (storage) IndependentTypeFailure(message);
}
extern "C" void IndependentNonRttiConstructControl(void *storage, const char *message) {
    new (storage) IndependentMissingRtti(message);
}
extern "C" void IndependentFailureDeleteControl(exception *self) { delete self; }
