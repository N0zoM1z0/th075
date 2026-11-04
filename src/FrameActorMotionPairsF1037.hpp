#pragma once
#include <stddef.h>

// The original frame logic reads/writes both adjacent signed float axes.
// Treat them as borrowed two-field windows, not a reconstructed full actor.
// +0x44/+0x48 are current x/y positions; +0x50/+0x54 are two motion
// contributions. Their intervening +0x4C storage is still unknown.
struct FrameActorPositionPairF1037 {
    float xPosition;
    float yPosition;
};
struct FrameActorMotionPairF1037 {
    float xMotion;
    float yMotion;
};
typedef char F1037PositionPairSize[(sizeof(FrameActorPositionPairF1037)==8)?1:-1];
typedef char F1037PositionYOffset[(offsetof(FrameActorPositionPairF1037,yPosition)==4)?1:-1];
typedef char F1037MotionPairSize[(sizeof(FrameActorMotionPairF1037)==8)?1:-1];
typedef char F1037MotionYOffset[(offsetof(FrameActorMotionPairF1037,yMotion)==4)?1:-1];
#define F1037_POSITION(actor) (*reinterpret_cast<FrameActorPositionPairF1037*>(reinterpret_cast<unsigned char*>(actor)+0x44))
#define F1037_MOTION(actor) (*reinterpret_cast<FrameActorMotionPairF1037*>(reinterpret_cast<unsigned char*>(actor)+0x50))
