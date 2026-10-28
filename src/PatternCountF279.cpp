// Count only one pattern row through the physical native scripted container.
// The underlying VC7 deque bodies are library code, not reconstructed here.
class PatternEntryQueueF279 {
public:
    short Size();
};
class PatternRowTableF279 {
public:
    PatternEntryQueueF279* At(int index);
};
class PatternCountF279 {
public:
    short CountPatternEntries(short row);
};
#define ROW (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this)+2*row))
short PatternCountF279::CountPatternEntries(short row)
{
    if (ROW<0) return 0;
    return reinterpret_cast<PatternRowTableF279*>(reinterpret_cast<unsigned char*>(this)+0x7d0)->At(ROW)->Size();
}
#undef ROW
