// F738 native R210/R211 authored prefix init policies; genuine used
// 16-byte record and conditional allocation. No full historical type claim.
#include <string.h>
#include <new>
struct RecordPrefix16F738 {
 unsigned char nativePrefix[8];
 unsigned char* owned36At8;
 unsigned char initializedFlagAt12;
 unsigned char nativeTail[3];
 RecordPrefix16F738* ZeroAndSetFlag();
 void ResetAllocation36();
};
typedef char AssertRecord16F738[(sizeof(RecordPrefix16F738)==16)?1:-1];
RecordPrefix16F738* RecordPrefix16F738::ZeroAndSetFlag() {
 memset(this,0,16);
 owned36At8=0;
 initializedFlagAt12=1;
 return this;
}
void RecordPrefix16F738::ResetAllocation36() {
 initializedFlagAt12=0;
 if (!owned36At8) {
   unsigned char* newOwned36=static_cast<unsigned char*>(::operator new(36));
   owned36At8=newOwned36;
 }
 // Original branch joins BEFORE memset: reused allocations are reset too.
 memset(owned36At8,0,36);
}
