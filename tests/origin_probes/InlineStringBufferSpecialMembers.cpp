// Complete generic owners with explicit class-inline special members.
#include <d3dx8.h>
#include <new>

class InlineBuffer : public ID3DXBuffer {
public:
    InlineBuffer() {
        capacity = 0;
        storage = 0;
        references = 1;
    }
    HRESULT __stdcall QueryInterface(REFIID id, void** result);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    void* __stdcall GetBufferPointer();
    DWORD __stdcall GetBufferSize();
    virtual ~InlineBuffer();
    virtual HRESULT Initialize(unsigned long size);
protected:
    unsigned long references;
    void* storage;
    unsigned long capacity;
};

InlineBuffer::~InlineBuffer() { ::operator delete(storage); }
HRESULT __stdcall InlineBuffer::QueryInterface(REFIID id, void** result) {
    if (id == IID_IUnknown || id == IID_ID3DXBuffer) {
        *result = static_cast<ID3DXBuffer*>(this);
        AddRef();
        return S_OK;
    }
    *result = 0;
    return E_NOINTERFACE;
}
ULONG __stdcall InlineBuffer::AddRef() { return ++references; }
ULONG __stdcall InlineBuffer::Release() {
    unsigned long count = --references;
    if (!count) delete this;
    return count;
}
void* __stdcall InlineBuffer::GetBufferPointer() { return storage; }
DWORD __stdcall InlineBuffer::GetBufferSize() { return capacity; }
HRESULT InlineBuffer::Initialize(unsigned long size) {
    void* replacement = ::operator new(size);
    if (!replacement) return E_OUTOFMEMORY;
    ::operator delete(storage);
    storage = replacement;
    capacity = size;
    return S_OK;
}

class ExplicitInlineStringBuffer : public InlineBuffer {
public:
    ExplicitInlineStringBuffer() : length(0), available(0) {}
    ~ExplicitInlineStringBuffer() {}
    unsigned long length, available;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = InlineBuffer::Initialize(size);
        if (result >= 0) { length = 0; available = size; }
        return result;
    }
};
class ImplicitInlineStringBuffer : public InlineBuffer {
public:
    ImplicitInlineStringBuffer() : length(0), available(0) {}
    unsigned long length, available;
    HRESULT Initialize(unsigned long size) {
        HRESULT result = InlineBuffer::Initialize(size);
        if (result >= 0) { length = 0; available = size; }
        return result;
    }
};

void ConstructInlineBase(void* storage) { new (storage) InlineBuffer; }
void ConstructExplicitInline(void* storage) { new (storage) ExplicitInlineStringBuffer; }
void DestroyExplicitInline(ExplicitInlineStringBuffer* value) { value->~ExplicitInlineStringBuffer(); }
void ConstructImplicitInline(void* storage) { new (storage) ImplicitInlineStringBuffer; }
void DestroyImplicitInline(ImplicitInlineStringBuffer* value) { value->~ImplicitInlineStringBuffer(); }

extern const unsigned long InlineBufferLayout[] = {
    sizeof(InlineBuffer), sizeof(ExplicitInlineStringBuffer), sizeof(ImplicitInlineStringBuffer)
};
