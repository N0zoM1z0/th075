#include <windows.h>
// Six genuinely used eight-byte native iterator objects and both real
// output/count DWORDs form exactly 56 contiguous observed native stack bytes.
// Borrowed .Initialize() calls target each original constructor entrypoint
// (00414930/004149E0/00414A90). The semantic name is a caller-side C++ ABI
// alias so physical member order can differ from native construction order;
// it is not a claim that the original method was named Initialize. No fake
// padding/state fields or hand-coded instructions; original private iterators,
// record types and allocation internals remain opaque.
class ByteIteratorF219 {
    unsigned int actualState[2];
public:
    void Initialize();
    bool operator!=(const ByteIteratorF219&) const;
    char& operator*() const;
    ByteIteratorF219 operator++(int);
};
class WordIteratorF219 {
    unsigned int actualState[2];
public:
    void Initialize();
    bool operator!=(const WordIteratorF219&) const;
    short& operator*() const;
    WordIteratorF219 operator++(int);
};
class DwordIteratorF219 {
    unsigned int actualState[2];
public:
    void Initialize();
    bool operator!=(const DwordIteratorF219&) const;
    unsigned int& operator*() const;
    DwordIteratorF219 operator++(int);
};
typedef char CheckByteIterator8F219[(sizeof(ByteIteratorF219)==8)?1:-1];
typedef char CheckWordIterator8F219[(sizeof(WordIteratorF219)==8)?1:-1];
typedef char CheckDwordIterator8F219[(sizeof(DwordIteratorF219)==8)?1:-1];
class ByteQueueF219 {
public:
    ByteIteratorF219 Begin();
    ByteIteratorF219 End();
    unsigned int Size();
};
class WordQueueF219 {
public:
    WordIteratorF219 Begin();
    WordIteratorF219 End();
    unsigned int Size();
};
class DwordQueueF219 {
public:
    DwordIteratorF219 Begin();
    DwordIteratorF219 End();
    unsigned int Size();
};
struct NativeAppendFrameF326 {
    ByteIteratorF219 byteIndexBegin;
    DWORD written;
    ByteIteratorF219 byteIndexEnd;
    WordIteratorF219 wordIndexEnd;
    WordIteratorF219 wordIndexBegin;
    unsigned int count;
    DwordIteratorF219 dwordIndexEnd;
    DwordIteratorF219 dwordHead;
};
typedef char NativeFrame56F326[(sizeof(NativeAppendFrameF326)==56)?1:-1];
class ReplayAppendF219 {
public:
    void AppendRecord();
    void ClearQueues();
public:
    // Observed fields; meanings not yet known.
    HANDLE field000;
    unsigned char unknown004[0x116 - 0x004];
    signed char field116;
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayAppendF219::AppendRecord()
{
    if (!field000) return;
    NativeAppendFrameF326 frame;
    frame.byteIndexBegin.Initialize();
    frame.byteIndexEnd.Initialize();
    frame.wordIndexBegin.Initialize();
    frame.wordIndexEnd.Initialize();
    frame.dwordHead.Initialize();
    frame.dwordIndexEnd.Initialize();
    FIELD(DWORD,0x11c + 4*field116) =
        SetFilePointer(field000,0,0,FILE_CURRENT);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x144,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x145,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x146,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x147,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x148,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x149,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x14a,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x14c,2,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x14e,1,&frame.written,0);
    WriteFile(field000,reinterpret_cast<unsigned char*>(this)+0x150,4,&frame.written,0);
    frame.byteIndexBegin=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x154)).Begin();
    frame.byteIndexEnd=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x154)).End();
    frame.count=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x154)).Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++) {
        WriteFile(field000,&*frame.byteIndexBegin,1,&frame.written,0);
    }
    frame.wordIndexBegin=(*reinterpret_cast<WordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x168)).Begin();
    frame.wordIndexEnd=(*reinterpret_cast<WordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x168)).End();
    frame.count=(*reinterpret_cast<WordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x168)).Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.wordIndexBegin!=frame.wordIndexEnd; frame.wordIndexBegin++) {
        WriteFile(field000,&*frame.wordIndexBegin,2,&frame.written,0);
    }
    frame.byteIndexBegin=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x17C)).Begin();
    frame.byteIndexEnd=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x17C)).End();
    frame.count=(*reinterpret_cast<ByteQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x17C)).Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++) {
        WriteFile(field000,&*frame.byteIndexBegin,1,&frame.written,0);
    }
    frame.dwordHead=(*reinterpret_cast<DwordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x190)).Begin();
    frame.dwordIndexEnd=(*reinterpret_cast<DwordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x190)).End();
    frame.count=(*reinterpret_cast<DwordQueueF219*>(reinterpret_cast<unsigned char*>(this) + 0x190)).Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.dwordHead!=frame.dwordIndexEnd; frame.dwordHead++) {
        WriteFile(field000,&*frame.dwordHead,4,&frame.written,0);
    }
    ClearQueues();
    ++field116;
}
#undef FIELD
