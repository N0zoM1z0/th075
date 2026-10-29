// F670: original source-UNKNOWN complete scoped-local native CODE grammar.
// The actual PE has a one-byte stack-addressed temporary and ctor/dtor calls.
// This is NOT an assertion of historical original class name or ownership.
// Ordinary VC7.1 C++; no inline ASM, target-byte graft or fake padding.
class SmallScopedLifetimeF670 {
public:
    explicit SmallScopedLifetimeF670(int);
    ~SmallScopedLifetimeF670();
};
extern "C" void NativeLocalScopeF670()
{
    SmallScopedLifetimeF670 local(16);
}
