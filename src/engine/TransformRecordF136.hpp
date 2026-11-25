#ifndef TH075_TRANSFORM_RECORD_F136_HPP
#define TH075_TRANSFORM_RECORD_F136_HPP

#include <stddef.h>

// Native 36-byte transform packet copied from Fighter+0x2F0 into Actor+0x10
// when a linked effect inherits its owner's transform. Both owners expose
// this record as an overlapping union member while retaining their individual
// field names. The compiler supplies alignment after the five leading bytes;
// the alignment byte remains unclaimed. This is a packet, not an owner layout.
struct TransformRecordF136 {
    unsigned char flag;
    unsigned char alpha;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    short word06;
    short word08;
    short word0A;
    float scaleX;
    float scaleY;
    float scaleZ;
    float rotationX;
    float rotationY;
    float rotationZ;
};

typedef char TransformRecordExtentF136[(sizeof(TransformRecordF136) == 36) ? 1 : -1];
typedef char TransformRecordWordF136[(offsetof(TransformRecordF136, word06) == 6) ? 1 : -1];
typedef char TransformRecordScaleF136[(offsetof(TransformRecordF136, scaleX) == 12) ? 1 : -1];
typedef char TransformRecordLastF136[(offsetof(TransformRecordF136, rotationZ) == 32) ? 1 : -1];

#endif
