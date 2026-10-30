// F739: natural original game record constructors with real member
// lifetime and EH cleanup. Private member type/layout names unproved.
class VectorBase20F739 {
 unsigned int nativeWords[4];
public:
 VectorBase20F739();
 ~VectorBase20F739();
 void Clear();
};
class VectorBase16F739 {
 unsigned int nativeWords[4];
public:
 VectorBase16F739();
 ~VectorBase16F739();
 void Clear();
};
class Record20F739 {
 VectorBase20F739 child;
 unsigned short xAt16;
 unsigned short yAt18;
public:
 Record20F739();
 ~Record20F739();
};
Record20F739::Record20F739() {
 child.Clear();
 xAt16=0;
 yAt18=0;
}
Record20F739::~Record20F739() {child.Clear();}
class Record16F739 {
 VectorBase16F739 child;
public:
 Record16F739();
 ~Record16F739();
};
Record16F739::Record16F739() {child.Clear();}
Record16F739::~Record16F739() {child.Clear();}
