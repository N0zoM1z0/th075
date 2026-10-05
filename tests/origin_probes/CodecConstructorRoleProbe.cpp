// Complete ordinary observer classes. Their layouts are not SDK owner layouts.
#include <d3dx8.h>
#include <stddef.h>

struct ProbeInput;
class PointerConstructorBase {
public:
    PointerConstructorBase(ProbeInput *input, UINT format, DWORD flags);
    virtual DWORD Code() const;
private:
    ProbeInput *input_;
    UINT format_;
    DWORD flags_;
};
PointerConstructorBase::PointerConstructorBase(ProbeInput *input, UINT format, DWORD flags)
    : input_(input), format_(format), flags_(flags) {}
DWORD PointerConstructorBase::Code() const { return format_ | flags_; }

class PointerConstructorDerived : public PointerConstructorBase {
public:
    explicit PointerConstructorDerived(ProbeInput *input);
    virtual DWORD Code() const;
};
PointerConstructorDerived::PointerConstructorDerived(ProbeInput *input)
    : PointerConstructorBase(input, D3DFMT_A8R8G8B8, 0) {}
DWORD PointerConstructorDerived::Code() const { return PointerConstructorBase::Code(); }

class DefaultConstructorBase {
public:
    DefaultConstructorBase();
    virtual DWORD Code() const;
private:
    DWORD flags_;
};
DefaultConstructorBase::DefaultConstructorBase() : flags_(D3DX_FILTER_BOX) {}
DWORD DefaultConstructorBase::Code() const { return flags_; }
class ImplicitDefaultObserver : public DefaultConstructorBase {
public:
    virtual DWORD Code() const;
};
DWORD ImplicitDefaultObserver::Code() const { return DefaultConstructorBase::Code(); }

class ImplicitCopyObserver {
public:
    virtual DWORD Code() const;
    DWORD flags;
};
DWORD ImplicitCopyObserver::Code() const { return flags; }

PointerConstructorDerived *ProbePointerCreate(ProbeInput *input)
{
    return new PointerConstructorDerived(input);
}
ImplicitDefaultObserver *ProbeDefaultCreate()
{
    return new ImplicitDefaultObserver;
}
ImplicitCopyObserver *ProbeCopyCreate(const ImplicitCopyObserver &other)
{
    return new ImplicitCopyObserver(other);
}

extern const unsigned int ConstructorRoleObserverLayout[] = {
    sizeof(PointerConstructorBase), sizeof(PointerConstructorDerived),
    sizeof(DefaultConstructorBase), sizeof(ImplicitDefaultObserver),
    sizeof(ImplicitCopyObserver), sizeof(ProbeInput *), sizeof(DWORD)
};
