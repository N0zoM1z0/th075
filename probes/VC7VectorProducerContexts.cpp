// Complete observations test whole SDK and ordinary source; original game types remain unknown.
#include <vector>

struct ScriptValue44Observation {
    unsigned char bytes[44];
    ~ScriptValue44Observation();
};
struct TextureValue16Observation {
    unsigned char bytes[16];
    ~TextureValue16Observation();
};
struct ViewAObservation { unsigned char bytes[4]; };
struct ViewBObservation { unsigned char bytes[4]; };
struct ViewCObservation { unsigned char bytes[4]; };
struct PlainValueObservation { unsigned char bytes[4]; };

#define OBSERVE_ENDPOINTS(T, N) \
    typedef std::vector<T> Vector##N; \
    Vector##N::iterator ObserveBegin##N(Vector##N& values) { return values.begin(); } \
    Vector##N::iterator ObserveEnd##N(Vector##N& values) { return values.end(); }

OBSERVE_ENDPOINTS(ScriptValue44Observation, Script)
OBSERVE_ENDPOINTS(ViewAObservation, ViewA)
OBSERVE_ENDPOINTS(ViewBObservation, ViewB)
OBSERVE_ENDPOINTS(ViewCObservation, ViewC)
OBSERVE_ENDPOINTS(TextureValue16Observation, Texture)
OBSERVE_ENDPOINTS(PlainValueObservation, Plain)

void ObserveAssignScript(VectorScript& values, unsigned count, const ScriptValue44Observation& value) {
    values.assign(count, value);
}
void ObserveAssignTexture(VectorTexture& values, unsigned count, const TextureValue16Observation& value) {
    values.assign(count, value);
}
void ObserveAssignPlain(VectorPlain& values, unsigned count, const PlainValueObservation& value) {
    values.assign(count, value);
}

template<class T> struct OrdinaryEndpointObservation {
    std::allocator<T> allocator;
    T* first;
    T* last;
    T* capacity_end;
    typename std::vector<T>::iterator begin() { return typename std::vector<T>::iterator(first); }
    typename std::vector<T>::iterator end() { return typename std::vector<T>::iterator(last); }
};
template<class T> struct OrdinaryIteratorObservation : std::vector<T>::const_iterator {
    explicit OrdinaryIteratorObservation(T* pointer) : std::vector<T>::const_iterator(pointer) {}
};
template<class T> struct OrdinaryAssignmentObservation : std::vector<T> {
    void assignValue(unsigned count, const T& value) {
        T temporary = value;
        this->erase(this->begin(), this->end());
        this->insert(this->begin(), count, temporary);
    }
};

VectorPlain::iterator ObserveOrdinaryBegin(OrdinaryEndpointObservation<PlainValueObservation>& values) {
    return values.begin();
}
VectorPlain::iterator ObserveOrdinaryEnd(OrdinaryEndpointObservation<PlainValueObservation>& values) {
    return values.end();
}
OrdinaryIteratorObservation<PlainValueObservation> ObserveOrdinaryIterator(PlainValueObservation* pointer) {
    return OrdinaryIteratorObservation<PlainValueObservation>(pointer);
}
void ObserveOrdinaryAssignScript(OrdinaryAssignmentObservation<ScriptValue44Observation>& values,
                                 unsigned count, const ScriptValue44Observation& value) {
    values.assignValue(count, value);
}
void ObserveOrdinaryAssignTexture(OrdinaryAssignmentObservation<TextureValue16Observation>& values,
                                  unsigned count, const TextureValue16Observation& value) {
    values.assignValue(count, value);
}

extern "C" const unsigned long VectorProducerLayout[] = {
    sizeof(ScriptValue44Observation), sizeof(TextureValue16Observation), sizeof(ViewAObservation),
    sizeof(ViewBObservation), sizeof(ViewCObservation), sizeof(PlainValueObservation),
    sizeof(VectorScript), sizeof(VectorViewA), sizeof(VectorViewB), sizeof(VectorViewC),
    sizeof(VectorTexture), sizeof(VectorPlain), sizeof(VectorScript::iterator), sizeof(VectorScript::const_iterator),
    sizeof(VectorViewA::iterator), sizeof(VectorViewB::iterator), sizeof(VectorViewC::iterator),
    sizeof(VectorTexture::iterator), sizeof(VectorPlain::iterator),
    sizeof(OrdinaryEndpointObservation<PlainValueObservation>), sizeof(OrdinaryIteratorObservation<PlainValueObservation>),
    sizeof(OrdinaryAssignmentObservation<ScriptValue44Observation>),
    sizeof(OrdinaryAssignmentObservation<TextureValue16Observation>)
};
