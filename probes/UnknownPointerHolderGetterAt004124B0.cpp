// Address-anchored C++ alternative for the 16-byte pointer getter at 004124B0.
// Its callers manipulate VC7 container proxies, but the original receiver type
// and the precise STL/game ownership boundary remain unresolved.
class UnknownPointerHolderAt004124B0 {
    void* firstPointer;
public:
    void* GetFirstPointerAt004124B0() const;
};

void* UnknownPointerHolderAt004124B0::GetFirstPointerAt004124B0() const
{
    return firstPointer;
}
