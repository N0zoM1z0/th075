// Reuse complete observations; none are original game class declarations.
#include "VC7SDKDependencyContexts.cpp"

template<class T> struct OrdinaryAllocatorObservation {
    void destroy(T* value) { std::_Destroy(value); }
};
void ObserveOrdinaryQueueAllocator(OrdinaryAllocatorObservation<Queue20Observation>& allocator,
                                   Queue20Observation* value) { allocator.destroy(value); }
void ObserveOrdinaryFileAllocator(OrdinaryAllocatorObservation<File60Observation>& allocator,
                                  File60Observation* value) { allocator.destroy(value); }
void OrdinaryQueueDestroy(Queue20Observation* value) { value->~Queue20Observation(); }
void OrdinaryFileDestroy(File60Observation* value) { value->~File60Observation(); }

extern "C" const unsigned long AllocatorDestroyLayout[] = {
    sizeof(OrdinaryAllocatorObservation<Queue20Observation>),
    sizeof(OrdinaryAllocatorObservation<File60Observation>)
};
