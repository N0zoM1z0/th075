// Whole native-authored R177 132-byte replay/static queues constructor.
// Four original 20-byte member constructors and each actual native EH
// lifetime come directly from C++ member default construction under /GX.
// This is a borrowed size-only aggregate, not an asserted private layout.
// Native-authored R177 replay/static resource queue constructor. Four
// independently observed 20-byte queue storage extents (not private fields).
class NativeByteQueueF414 {
public: NativeByteQueueF414(); ~NativeByteQueueF414();
private: unsigned char nativeObservedFootprint[20];
};
class NativeWordQueueF414 {
public: NativeWordQueueF414(); ~NativeWordQueueF414();
private: unsigned char nativeObservedFootprint[20];
};
class NativeDwordQueueF414 {
public: NativeDwordQueueF414(); ~NativeDwordQueueF414();
private: unsigned char nativeObservedFootprint[20];
};
class ReplayStaticQueuesF414 {
private:
 unsigned char borrowedUnobservedPrefix[0x154];
 NativeByteQueueF414 first;
 NativeWordQueueF414 second;
 NativeByteQueueF414 third;
 NativeDwordQueueF414 fourth;
public: ReplayStaticQueuesF414();
};
typedef char CheckQueueOffsetsF414[(sizeof(NativeByteQueueF414)==20 && sizeof(NativeWordQueueF414)==20 && sizeof(NativeDwordQueueF414)==20) ? 1 : -1];
ReplayStaticQueuesF414::ReplayStaticQueuesF414() {
 *reinterpret_cast<unsigned int*>(this)=0;
}
