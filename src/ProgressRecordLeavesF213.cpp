// Borrowed this-pointer record layout. The original source-level complete
// record class and packed element types are unknown; these two methods never
// instantiate it.
class ProgressRecordLeavesF213 {
public:
    void RaiseSelectedValue(signed char value);
    void IncrementSelectedRecordCount();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define REC_BYTE(off) (*reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x17f0*FIELD(signed char,0x16ac4) + 0x5fc*FIELD(signed char,0x16ac5) + (off)))
#define REC_DWORD(off) FIELD(int,0x5fc*FIELD(signed char,0x16ac5) + 0x17f0*FIELD(signed char,0x16ac4) + (off))
void ProgressRecordLeavesF213::RaiseSelectedValue(signed char value)
{
    if (value > REC_BYTE(0x556))
        REC_BYTE(0x556) = value;
}
void ProgressRecordLeavesF213::IncrementSelectedRecordCount()
{
    REC_DWORD(0) = REC_DWORD(0) + 1;
}
#undef REC_DWORD
#undef REC_BYTE
#undef FIELD
