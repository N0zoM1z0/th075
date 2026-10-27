// Borrowed, call-only VC7.1 deque policies. Their actual receivers at
// ReplayRecords+0x154/+0x168/+0x17C/+0x190 and returned element count are
// independently anchored by the full authored replay reader/writer CFG.
// No incomplete ReplayRecords object or deque owner is allocated.
class ByteQueueF220 { public: void Clear(); unsigned int Size(); };
class WordQueueF220 { public: void Clear(); };
class DwordQueueF220 { public: void Clear(); };
class ReplayQueuePolicyF220 {
public:
    void ClearFourQueues();
    unsigned char IsPrimaryInputQueueEmpty();
};
#define QUEUE(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void ReplayQueuePolicyF220::ClearFourQueues()
{
    QUEUE(ByteQueueF220,0x154).Clear();
    QUEUE(WordQueueF220,0x168).Clear();
    QUEUE(ByteQueueF220,0x17c).Clear();
    QUEUE(DwordQueueF220,0x190).Clear();
}
unsigned char ReplayQueuePolicyF220::IsPrimaryInputQueueEmpty()
{
    if (QUEUE(ByteQueueF220,0x154).Size()>0)
        return 0;
    return 1;
}
#undef QUEUE
