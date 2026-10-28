// Borrowed factory receiver; physical target new operand 0xE8. The class
// carrier exposes that allocation size, not a recovered original object.
class MarisaGeneratedF223 {
    unsigned char observedBytes[0xe8];
public:
    MarisaGeneratedF223(void* fighter);
};
typedef char ValidateNew232F223[(sizeof(MarisaGeneratedF223)==0xe8)?1:-1];
class MarisaFactoryF223 {
public:
    void CreateOwnedObject(MarisaGeneratedF223** output);
};
void MarisaFactoryF223::CreateOwnedObject(MarisaGeneratedF223** output)
{
    *output = new MarisaGeneratedF223(this);
}
