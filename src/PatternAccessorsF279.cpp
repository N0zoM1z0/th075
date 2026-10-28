// Borrowed native VC7 deque-index methods for game-owned pattern field
// extraction. Container helper implementations are explicitly not authored.
class PatternEntryVectorF279 {
public:
    unsigned char* At(int index);
};
class PatternSequenceTableF279 {
public:
    PatternEntryVectorF279* At(int index);
};
class PatternAccessorsF279 {
public:
    signed char GetByteField(short sequence,short entry);
    short GetWordField(short sequence,short entry);
    void* GetDwordField(short sequence,short entry);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define ROW (*reinterpret_cast<short*>(RAW+2*sequence))
#define ITEM reinterpret_cast<PatternSequenceTableF279*>(RAW+0x7d0)->At(ROW)->At(entry)
signed char PatternAccessorsF279::GetByteField(short sequence,short entry)
{
    return *reinterpret_cast<signed char*>(ITEM);
}
short PatternAccessorsF279::GetWordField(short sequence,short entry)
{
    return *reinterpret_cast<short*>(ITEM+2);
}
void* PatternAccessorsF279::GetDwordField(short sequence,short entry)
{
    return *reinterpret_cast<void**>(ITEM+4);
}
#undef ITEM
#undef ROW
#undef RAW
