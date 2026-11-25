#include "battle/Actor.hpp"
#include <new>
#include <string.h>

FighterFrameInfoHeader::FighterFrameInfoHeader() {
 memset(this,0,16);
 pose=0;
 doubleScale=1;
}
void FighterFrameInfoHeader::ResetExtension() {
 doubleScale=0;
 if (!pose) {
   ActorPose* newPose=static_cast<ActorPose*>(::operator new(sizeof(ActorPose)));
   pose=newPose;
 }
 // Original branch joins BEFORE memset: reused allocations are reset too.
 memset(pose,0,36);
}

FighterFrameInfoHeader::~FighterFrameInfoHeader() {
    if (pose) {
        ActorPose* extension = pose;
        ::operator delete(extension);
    }
}
