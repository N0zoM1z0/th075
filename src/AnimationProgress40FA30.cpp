#include "AnimationProgress40FA30.hpp"


short AnimationProgress40FA30::AdvanceNestedFrame() {
    ++animationFrame;
    if (animationFrame >= field072) {
        animationFrame = 0;
        ++animationStage;
        if (animationStage >= field070) {
            animationStage = 0;
            BindAnimation();
            return field070;
        }
        BindAnimation();
        return animationStage;
    }
    return 0;
}
