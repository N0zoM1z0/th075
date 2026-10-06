// Complete ordinary public-interface owners; no original private class is declared.
#include <d3dx8.h>
#include <new>

class OrdinaryBuffer : public ID3DXBuffer {
public:
    OrdinaryBuffer();
    HRESULT __stdcall QueryInterface(REFIID id, void** result);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    void* __stdcall GetBufferPointer();
    DWORD __stdcall GetBufferSize();
    virtual ~OrdinaryBuffer();
    virtual HRESULT Initialize(unsigned long size);
protected:
    unsigned long references;
    void* storage;
    unsigned long capacity;
};

OrdinaryBuffer::OrdinaryBuffer() {
    capacity = 0;
    storage = 0;
    references = 1;
}
OrdinaryBuffer::~OrdinaryBuffer() { ::operator delete(storage); }
HRESULT __stdcall OrdinaryBuffer::QueryInterface(REFIID id, void** result) {
    if (id == IID_IUnknown || id == IID_ID3DXBuffer) {
        *result = static_cast<ID3DXBuffer*>(this);
        AddRef();
        return S_OK;
    }
    *result = 0;
    return E_NOINTERFACE;
}
ULONG __stdcall OrdinaryBuffer::AddRef() { return ++references; }
ULONG __stdcall OrdinaryBuffer::Release() {
    unsigned long count = --references;
    if (!count) delete this;
    return count;
}
void* __stdcall OrdinaryBuffer::GetBufferPointer() { return storage; }
DWORD __stdcall OrdinaryBuffer::GetBufferSize() { return capacity; }
HRESULT OrdinaryBuffer::Initialize(unsigned long size) {
    void* replacement = ::operator new(size);
    if (!replacement) return E_OUTOFMEMORY;
    ::operator delete(storage);
    storage = replacement;
    capacity = size;
    return S_OK;
}

struct StringState {
    unsigned long length;
    unsigned long available;
    StringState() : length(0), available(0) {}
    void Consume(unsigned long count) {
        if (count <= available) { length += count; available -= count; }
    }
};
class ImplicitStringBuffer : public OrdinaryBuffer {
public:
    StringState state;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = OrdinaryBuffer::Initialize(size);
        if (result >= 0) { state.length = 0; state.available = size; }
        return result;
    }
};
class ExplicitStringBuffer : public OrdinaryBuffer {
public:
    ExplicitStringBuffer();
    ~ExplicitStringBuffer();
    StringState state;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = OrdinaryBuffer::Initialize(size);
        if (result >= 0) { state.length = 0; state.available = size; }
        return result;
    }
};
ExplicitStringBuffer::ExplicitStringBuffer() {}
ExplicitStringBuffer::~ExplicitStringBuffer() {}

void ConstructImplicit(void* storage) { new (storage) ImplicitStringBuffer; }
void DestroyImplicit(ImplicitStringBuffer* value) { value->~ImplicitStringBuffer(); }
void ConstructExplicit(void* storage) { new (storage) ExplicitStringBuffer; }
void DestroyExplicit(ExplicitStringBuffer* value) { value->~ExplicitStringBuffer(); }

class ImplicitDestructorBuffer : public OrdinaryBuffer {
public:
    ImplicitDestructorBuffer();
    unsigned long length, available;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = OrdinaryBuffer::Initialize(size);
        if (result >= 0) { length = 0; available = size; }
        return result;
    }
};
ImplicitDestructorBuffer::ImplicitDestructorBuffer() : length(0), available(0) {}
class ExplicitDestructorBuffer : public OrdinaryBuffer {
public:
    ExplicitDestructorBuffer();
    ~ExplicitDestructorBuffer();
    unsigned long length, available;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = OrdinaryBuffer::Initialize(size);
        if (result >= 0) { length = 0; available = size; }
        return result;
    }
};
ExplicitDestructorBuffer::ExplicitDestructorBuffer() : length(0), available(0) {}
ExplicitDestructorBuffer::~ExplicitDestructorBuffer() {}
void ConstructImplicitDestructor(void* storage) { new (storage) ImplicitDestructorBuffer; }
void DestroyImplicitDestructor(ImplicitDestructorBuffer* value) { value->~ImplicitDestructorBuffer(); }
void ConstructExplicitDestructor(void* storage) { new (storage) ExplicitDestructorBuffer; }
void DestroyExplicitDestructor(ExplicitDestructorBuffer* value) { value->~ExplicitDestructorBuffer(); }

extern const unsigned long StringBufferLayout[] = {
    sizeof(OrdinaryBuffer), sizeof(StringState),
    sizeof(ImplicitStringBuffer), sizeof(ExplicitStringBuffer),
    sizeof(ImplicitDestructorBuffer), sizeof(ExplicitDestructorBuffer)
};
