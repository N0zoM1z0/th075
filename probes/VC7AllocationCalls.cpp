// Natural SDK call controls; no original game type or allocation outcome is inferred.
#include <new>
#include <stddef.h>
struct AllocationRecordObservation { unsigned char bytes[8]; };
char* AllocateByteArray(size_t count) { return new char[count]; }
unsigned long* AllocateWordArray(size_t count) { return new unsigned long[count]; }
AllocationRecordObservation* AllocateRecordArray(size_t count) {
    return new AllocationRecordObservation[count];
}
void ReleaseByteArray(char* value) { delete[] value; }
void ReleaseWordArray(unsigned long* value) { delete[] value; }
void ReleaseRecordArray(AllocationRecordObservation* value) { delete[] value; }
void* AllocateScalarStorage(size_t count) { return ::operator new(count); }
void ReleaseScalarStorage(void* value) { ::operator delete(value); }
extern "C" const unsigned long AllocationCallLayout[] = {
    sizeof(size_t), sizeof(void*), sizeof(AllocationRecordObservation), sizeof(unsigned long)
};
