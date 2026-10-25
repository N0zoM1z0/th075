#ifndef TH075_TRANSFORM_RECORD_F136_HPP
#define TH075_TRANSFORM_RECORD_F136_HPP

#include <stddef.h>

// Bounded view of the independently cleared/copied 36-byte data window.
// Every explicit field has observed byte/word/float accesses. The compiler
// supplies alignment after the five bytes; no padding or array is declared.
// Original names and whether the alignment byte was a field are unknown.
// This is not a complete game owner and must never be used to size one.
struct TransformRecordF136 {
    unsigned char flag;
    unsigned char alpha;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    short word06;
    short word08;
    short word0A;
    float scalar0C;
    float scalar10;
    float scalar14;
    float scalar18;
    float scalar1C;
    float scalar20;
};

typedef char TransformRecordExtentF136[(sizeof(TransformRecordF136) == 36) ? 1 : -1];
typedef char TransformRecordWordF136[(offsetof(TransformRecordF136, word06) == 6) ? 1 : -1];
typedef char TransformRecordScalarF136[(offsetof(TransformRecordF136, scalar0C) == 12) ? 1 : -1];
typedef char TransformRecordLastF136[(offsetof(TransformRecordF136, scalar20) == 32) ? 1 : -1];

#endif
