// Physically observed stack temporary is 44 bytes and is always constructed
// and destroyed around the owner's resource-slot allocation call.
class TemporaryTextureSlotF198 {
    unsigned int observedSlots[11];
public:
    TemporaryTextureSlotF198();
    ~TemporaryTextureSlotF198();
};
typedef char ValidateTemporarySlot44F198[(sizeof(TemporaryTextureSlotF198)==44)?1:-1];

class TextureNameSlotsF198 {
public:
    void InitializeSlots(int count, const TemporaryTextureSlotF198& value);
};
class TexturePayloadSlotsF198 {
public:
    void InitializeSlots(int count, unsigned int* zeroSlot);
};
class TextureSlotAllocatorF198 {
public:
    void AllocateUnformattedSlots(int count);
};
#define AT(type, off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void TextureSlotAllocatorF198::AllocateUnformattedSlots(int count)
{
    TemporaryTextureSlotF198 defaultEntry;
    AT(unsigned char, 0x4c) = 0;
    reinterpret_cast<TextureNameSlotsF198*>(reinterpret_cast<unsigned char*>(this)+8)->InitializeSlots(count,defaultEntry);
    unsigned int zero = 0;
    reinterpret_cast<TexturePayloadSlotsF198*>(reinterpret_cast<unsigned char*>(this)+0x18)->InitializeSlots(count,&zero);
}
#undef AT
