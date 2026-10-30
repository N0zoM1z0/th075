// F741: complete original 145-byte nested-record constructor source.
// All three actual member subobjects have genuine lifetime and EH
// cleanup; original 116-byte prefix/vector layout is provisional.
#include <string.h>
class Prefix16F741 {
  unsigned char originalWordBytes[8];
public:
  unsigned char* bufferAt8;
private:
  unsigned int originalFlagAt12;
public:
  Prefix16F741();
  ~Prefix16F741();
};
class Vector16F741 {
  unsigned int genuineNativeWords[4];
public:
  Vector16F741();
  ~Vector16F741();
  void Clear();
};
class NestedRecord116F741 {
  Prefix16F741 originalPrefixAt0;
  unsigned char otherActualClearedMembers[0x44];
  Vector16F741 firstVectorAt54;
  Vector16F741 secondVectorAt64;
public:
  NestedRecord116F741();
  ~NestedRecord116F741();
};
typedef char F741SizeCheck[(sizeof(NestedRecord116F741)==0x74)?1:-1];
NestedRecord116F741::NestedRecord116F741() {
  memset(this,0,sizeof(*this));
  firstVectorAt54.Clear();
  secondVectorAt64.Clear();
  originalPrefixAt0.bufferAt8=0;
}

NestedRecord116F741::~NestedRecord116F741() {
  firstVectorAt54.Clear();
  secondVectorAt64.Clear();
}
