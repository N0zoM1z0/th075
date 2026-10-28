#include <windows.h>
// Complete native 161-byte original R177 destructor of four borrowed
// 20-byte game queues, not a full private owner allocation. Real /GX
// compiler EH and reverse-order child destructors are generated naturally.
// The native handle field is addressed directly: a temporary HANDLE&
// changes the original stack frame and is not native-faithful.
// Actual 20-byte members at original physically observed offsets, with real
// per-member construction/destruction and compiler-managed /GX EH.
class ByteQueueF426 { public: ByteQueueF426(); ~ByteQueueF426(); private: unsigned char nativeFootprint[20]; };
class WordQueueF426 { public: WordQueueF426(); ~WordQueueF426(); private: unsigned char nativeFootprint[20]; };
class DwordQueueF426 { public: DwordQueueF426(); ~DwordQueueF426(); private: unsigned char nativeFootprint[20]; };
class StaticResourceQueueF426 {
  unsigned char originalUnobservedPrefix[0x154];
  ByteQueueF426 first;
  WordQueueF426 second;
  ByteQueueF426 third;
  DwordQueueF426 fourth;
public:
  ~StaticResourceQueueF426();
  void ReleaseOwnedQueueItems();
};
typedef char VerifyByteF426[(sizeof(ByteQueueF426)==20)?1:-1];
typedef char VerifyWordF426[(sizeof(WordQueueF426)==20)?1:-1];
typedef char VerifyDwordF426[(sizeof(DwordQueueF426)==20)?1:-1];
StaticResourceQueueF426::~StaticResourceQueueF426() {
  ReleaseOwnedQueueItems();
  if(*reinterpret_cast<HANDLE*>(this)) {CloseHandle(*reinterpret_cast<HANDLE*>(this)); *reinterpret_cast<HANDLE*>(this)=0;}
}
