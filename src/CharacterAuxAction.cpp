#include "CharacterAuxAction.hpp"

void CharacterAuxObject::Advance()
{
    switch (action) {
    case 1:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = ChooseIntegerRange(0, 45);
            rotationY = ChooseIntegerRange(0, 45);
            rotationZ = ChooseIntegerRange(0, 45);
            field074 = 0;
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.035f);
        scaleY += (0.3f - field074 * 0.035f);
        if (animationStage > 0) {
            if (color[0] > 30) {
                color[0] -= 30;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 2:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = ChooseIntegerRange(0, 45);
            rotationY = ChooseIntegerRange(0, 45);
            rotationZ = ChooseIntegerRange(0, 45);
            field074 = 0;
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnPeer(101, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
            SpawnPeer(102, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.035f);
        scaleY += (0.3f - field074 * 0.035f);
        if (animationStage > 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 3:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = ChooseIntegerRange(0, 45);
            rotationY = ChooseIntegerRange(0, 45);
            rotationZ = ChooseIntegerRange(0, 45);
            field074 = 0;
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnPeer(103, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.035f);
        scaleY += (0.3f - field074 * 0.035f);
        if (animationStage > 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 5:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 100 - ChooseIntegerRange(0, 20);
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        scaleX += 0.5f - field074 * 0.035f;
        scaleY *= 0.75f;
        if (animationStage > 0) {
            if (color[0] > 60) {
                color[0] -= 60;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 60) color[1] -= 60;
            if (color[2] > 60) color[2] -= 60;
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 6:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = -35 - ChooseIntegerRange(0, 20);
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        scaleX += 0.5f - field074 * 0.035f;
        scaleY *= 0.75f;
        if (animationStage > 0) {
            if (color[0] > 60) {
                color[0] -= 60;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 60) color[1] -= 60;
            if (color[2] > 60) color[2] -= 60;
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 7:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 10 - ChooseIntegerRange(0, 20);
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        scaleX += 0.5f - field074 * 0.035f;
        scaleY *= 0.75f;
        if (animationStage > 0) {
            if (color[0] > 60) {
                color[0] -= 60;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 60) color[1] -= 60;
            if (color[2] > 60) color[2] -= 60;
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 8:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 55 - ChooseIntegerRange(0, 20);
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        scaleX += 0.5f - field074 * 0.035f;
        scaleY *= 0.75f;
        if (animationStage > 0) {
            if (color[0] > 60) {
                color[0] -= 60;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 60) color[1] -= 60;
            if (color[2] > 60) color[2] -= 60;
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 13:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = ChooseIntegerRange(0, 10) * 0.1f + 3.0f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(138, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 14:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(105, x - facing * 60, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.02f);
        scaleY += (0.3f - field074 * 0.02f);
        if (animationStage > 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 15:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(139, x, y, 1, 1);
            SpawnPeer(140, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        scaleX += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        scaleY += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[1] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        ++field074;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 50:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 60.0f;
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        scaleY += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[1] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 51:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 60.0f;
            field074 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
            SpawnPeer(105, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        scaleY += (0.2f - field074 * 0.02f) * ((0.2f - field074 * 0.02f) > 0.0f);
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[3] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 52:
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
            SpawnPeer(107, x, y, 1, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 53:
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(108, x, y, 1, 1);
            SpawnPeer(109, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(110, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
            SpawnPeer(104, x, y, 1, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 54:
        if (animationStage == 0 && animationFrame == 0) {
            SpawnPeer(137, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
            SpawnPeer(111, x, y, 1, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 55:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnPeer(112, x, y, 1, 1);
            SpawnPeer(113, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
            SpawnPeer(114, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.5f - field074 * 0.035f) * ((0.5f - field074 * 0.035f) > 0.0f);
        scaleY += (0.5f - field074 * 0.035f) * ((0.5f - field074 * 0.035f) > 0.0f);
        if (animationStage > 0 && animationFrame > 3) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 56:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
            SpawnPeer(57, x, y, 1, 1);
        }
        ++field074;
        scaleX += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        scaleY += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[1] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 57:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
            field074 = 0;
        }
        x += velocityX;
        y -= velocityY;
        ++field074;
        if (animationStage > 0) {
            scaleX += 0.1f;
            scaleY *= 0.9f;
            if (color[0] < 8) {
                color[0] = 0;
            }
            else {
                color[0] -= 8;
            }
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 60:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 75.0f;
            field01A = facing * 350;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.015f);
        scaleY += (0.2f - field074 * 0.015f);
        if (animationStage >= 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 62:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = static_cast<short>(ChooseIntegerRange(0, 359));
            reinterpret_cast<float&>(field080) = field074 + 180;
            SetPolarVelocity(field074, 500.0f);
            SpawnPeer(63, x + velocityX, y + velocityY, 1, 1);
        }
        ++field074;
        scaleX -= 0.03f;
        scaleY -= 0.03f;
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[1] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 63:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
            SetPolarVelocity(reinterpret_cast<float&>(field080), 15.0f);
        }
        if (field074 == 0) {
            if (color[0] < 215) {
                color[0] += 40;
            }
            else {
                color[0] = 255;
                field074 = 1;
            }
        }
        if (field074 == 0) {
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                color[0] = 0;
                field074 = 2;
            }
        }
        rotationZ += 5.0f;
        x += velocityX;
        y += velocityY;
        scaleX -= 0.033f;
        scaleY -= 0.033f;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 64:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = static_cast<short>(ChooseIntegerRange(0, 359));
            reinterpret_cast<float&>(field080) = field074 + 180;
            SetPolarVelocity(field074, 500.0f);
            SpawnPeer(65, x + velocityX, y + velocityY, 1, 1);
        }
        ++field074;
        scaleX -= 0.03f;
        scaleY -= 0.03f;
        if (animationStage > 0) {
            if (color[0] > 25) {
                color[0] -= 25;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 25) color[1] -= 25;
            if (color[2] > 25) color[2] -= 25;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 65:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
            SetPolarVelocity(reinterpret_cast<float&>(field080), 15.0f);
        }
        if (field074 == 0) {
            if (color[0] < 215) {
                color[0] += 40;
            }
            else {
                color[0] = 255;
                field074 = 1;
            }
        }
        if (field074 == 0) {
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                color[0] = 0;
                field074 = 2;
            }
        }
        rotationZ += 5.0f;
        x += velocityX;
        y += velocityY;
        scaleX -= 0.033f;
        scaleY -= 0.033f;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 100:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(rand(), rand() * 0.0005);
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        x += velocityX;
        y += velocityY;
        ++field074;
        scaleX *= 0.85f;
        scaleY *= 0.85f;
        if (color[0] < 15) {
            color[0] = 0;
        }
        else {
            color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 101:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.7f;
            scaleY = 0.7f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.02f);
        scaleY += (0.2f - field074 * 0.02f);
        if (color[0] > 30) {
            color[0] -= 15;
        }
        else {
            color[0] = 0;
        }
        if (color[1] > 20) color[1] -= 15;
        if (color[2] > 20) color[2] -= 15;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 102:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            field076 = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        field074 = static_cast<short>(field074 * 0.95f);
        SetPolarVelocity(field076, field074 * 0.01f);
        x += velocityX;
        y += velocityY;
        rotationZ += 5.0f;
        if (animationFrame > 5) {
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 10) color[1] -= 10;
            if (color[2] > 10) color[2] -= 10;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 103:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.7f;
            scaleY = 0.7f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.02f);
        scaleY += (0.3f - field074 * 0.02f);
        if (color[0] > 30) {
            color[0] -= 15;
        }
        else {
            color[0] = 0;
        }
        if (color[1] > 20) color[1] -= 15;
        if (color[2] > 20) color[2] -= 15;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 104:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
            field074 = 0;
        }
        x += velocityX;
        y -= velocityY;
        ++field074;
        if (animationStage > 0) {
            scaleY *= 0.85f;
            if (color[0] < 15) {
                color[0] = 0;
            }
            else {
                color[0] -= 15;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 105:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
            field074 = 0;
        }
        x += velocityX;
        y -= velocityY;
        ++field074;
        if (animationStage > 0) {
            scaleY *= 0.85f;
            if (color[0] < 15) {
                color[0] = 0;
            }
            else {
                color[0] -= 15;
            }
            if (color[1] > 20) color[3] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 106:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 65.0f;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.015f);
        scaleY += (0.2f - field074 * 0.015f);
        if (animationStage >= 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 107:
        if (animationStage == 0 && animationFrame == 0) {
            field078 = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = field078 * 0.01f;
            scaleY = field078 * 0.01f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            field076 = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        field074 = static_cast<short>(field074 * 0.96f);
        SetPolarVelocity(field076, field074 * 0.01f);
        x += velocityX;
        y += velocityY;
        if (animationFrame > 2) {
            scaleX *= 0.85f;
            scaleY *= 0.85f;
            if (color[0] < 15) {
                color[0] = 0;
            }
            else {
                color[0] -= 15;
            }
            if (color[1] > 20) color[1] -= 15;
            if (color[2] > 20) color[2] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 108:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 0.0f;
            field074 = 0;
        }
        rotationZ += 5.0f;
        ++field074;
        scaleX += (0.4f - field074 * 0.01f);
        scaleY += (0.4f - field074 * 0.01f);
        if (animationFrame >= 30) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 109:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 45.0f;
            field074 = 0;
        }
        rotationZ += 5.0f;
        ++field074;
        scaleX += (0.4f - field074 * 0.01f);
        scaleY += (0.4f - field074 * 0.01f);
        if (animationFrame >= 30) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 110:
        if (animationStage == 0 && animationFrame == 0) {
            field078 = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = static_cast<short>(ChooseIntegerRange(0, 500) + 1500);
            field076 = static_cast<short>(ChooseIntegerRange(0, 360));
            rotationZ = field076 - 90;
        }
        field074 = static_cast<short>(field074 * 0.97f);
        SetPolarVelocity(field076 - 180, field074 * 0.01f);
        x += velocityX;
        y += velocityY;
        scaleY += 0.05f;
        if (animationFrame > 15) {
            if (color[0] < 10) {
                color[0] = 0;
            }
            else {
                color[0] -= 10;
            }
            if (color[1] > 20) color[1] -= 5;
            if (color[2] > 20) color[2] -= 5;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 111:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = ChooseIntegerRange(20, 100) * 0.01f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(ChooseIntegerRange(-155, -25), ChooseIntegerRange(100, 250) * 0.1f);
            rotationZ = ChooseIntegerRange(0, 360);
        }
        velocityY -= 0.75f;
        x += velocityX;
        y += velocityY;
        rotationZ += 5.0f;
        if (y < 40.0f && velocityY < 0.0f && ChooseIntegerRange(0, 100) < 10) {
            velocityY = -velocityY;
        }
        if (animationStage > 0) {
            if (color[0] < 10) {
                color[0] = 0;
            }
            else {
                color[0] -= 10;
            }
            if (color[1] > 20) color[1] -= 5;
            if (color[2] > 20) color[2] -= 5;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 112:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 65.0f;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.5f - field074 * 0.04f) * ((0.5f - field074 * 0.04f) > 0.0f) + 0.02f;
        scaleY += (0.5f - field074 * 0.04f) * ((0.5f - field074 * 0.04f) > 0.0f) + 0.02f;
        if (animationFrame >= 10) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 113:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.7f;
            scaleY = 0.7f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.02f);
        scaleY += (0.3f - field074 * 0.02f);
        if (color[0] > 30) {
            color[0] -= 15;
        }
        else {
            color[0] = 0;
        }
        if (color[1] > 20) color[1] -= 15;
        if (color[2] > 20) color[2] -= 15;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 114:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = ChooseIntegerRange(50, 120) * 1.0f * 0.01f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = static_cast<short>(ChooseIntegerRange(0, 1000) + 4000);
            field076 = static_cast<short>(ChooseIntegerRange(0, 360));
        }
        field074 = static_cast<short>(field074 * 0.9f);
        SetPolarVelocity(field076 - 180, field074 * 0.01f);
        x += velocityX;
        y += velocityY;
        if (animationFrame > 20) {
            scaleX *= 0.9f;
            scaleY *= 0.9f;
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 115:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
            for (int particle = 0; particle < 25; ++particle)
                SpawnPeer(122, x, y, 1, 1);
            SpawnPeer(141, x, y, 1, 1);
            SpawnPeer(142, x, y, 1, 1);
            SpawnPeer(143, x, y, 1, 1);
            SpawnPeer(144, x, y, 1, 1);
            SpawnPeer(145, x, y, 1, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 116:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
            SpawnPeer(131, x, y, 1, 1);
            SpawnPeer(132, x, y, 1, 1);
            SpawnPeer(133, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(134, x, y, 1, 1);
            SpawnPeer(135, x, y, 1, 1);
            SpawnPeer(135, x, y, 1, 1);
            SpawnPeer(136, x, y, 1, 1);
            SpawnPeer(136, x, y, 1, 1);
            SpawnPeer(136, x, y, 1, 1);
            SpawnPeer(136, x, y, 1, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 117:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.2f;
            scaleY = 1.2f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = -80.0f;
            field074 = 0;
        }
        field01A = 1500;
        field016 = 0;
        rotationZ += 3.0f;
        scaleX += 0.02f;
        scaleY += 0.02f;
        if (animationStage > 0) color[0] -= 6;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 118:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.4f;
            scaleY = 1.4f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = -80.0f;
            field074 = 0;
        }
        field01A = 1500;
        field016 = 0;
        rotationZ += 3.0f;
        scaleX += 0.02f;
        scaleY += 0.02f;
        if (animationStage > 0) color[0] -= 6;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 119:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        scaleY += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 120:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.03f) * ((0.3f - field074 * 0.03f) > 0.0f) + 0.03f;
        scaleY += (0.3f - field074 * 0.03f) * ((0.3f - field074 * 0.03f) > 0.0f) + 0.03f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 121:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        scaleY += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 122:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
            field074 = 0;
        }
        x += velocityX;
        y -= velocityY;
        ++field074;
        if (animationStage > 0) {
            scaleX += 0.3f;
            scaleY *= 0.9f;
            if (color[0] < 8) {
                color[0] = 0;
            }
            else {
                color[0] -= 8;
            }
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 123:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.5f;
            scaleY = 10.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        rotationZ += 1.0f;
        scaleX += 0.01f;
        scaleY *= 0.9f;
        if (field074 > 1) {
            if (color[0] < 15) {
                color[0] = 0;
                ClearField8();
                return;
            }
            color[0] -= 15;
            if (color[1] > 10) color[1] -= 10;
            if (color[2] > 10) color[2] -= 10;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounters(1);
            ++field074;
        }
        break;
    case 124:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.5f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        rotationZ -= 1.0f;
        scaleX += 0.01f;
        scaleY *= 0.95f;
        if (field074 > 1) {
            if (color[0] < 20) {
                color[0] = 0;
                ClearField8();
                return;
            }
            color[0] -= 20;
            if (color[1] > 10) color[1] -= 10;
            if (color[2] > 10) color[2] -= 10;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounters(1);
            ++field074;
        }
        break;
    case 125:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 65.0f;
            field01A = facing * 350;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.2f - field074 * 0.015f);
        scaleY += (0.2f - field074 * 0.015f);
        if (animationStage >= 0) {
            if (color[0] > 30) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 126:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 127:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 128:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 129:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 130:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 131:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        scaleY += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 132:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.3f - field074 * 0.03f) * ((0.3f - field074 * 0.03f) > 0.0f) + 0.03f;
        scaleY += (0.3f - field074 * 0.03f) * ((0.3f - field074 * 0.03f) > 0.0f) + 0.03f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 133:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        scaleY += (0.5f - field074 * 0.05f) * ((0.5f - field074 * 0.05f) > 0.0f) + 0.05f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 134:
        if (animationStage == 0 && animationFrame == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
            field074 = 0;
        }
        x += velocityX;
        y -= velocityY;
        ++field074;
        if (animationStage > 0) {
            scaleX += 0.1f;
            scaleY *= 0.9f;
            if (color[0] < 8) {
                color[0] = 0;
            }
            else {
                color[0] -= 8;
            }
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 135:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.5f;
            scaleY = 10.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        rotationZ += 1.0f;
        scaleX += 0.01f;
        scaleY *= 0.9f;
        if (field074 > 1) {
            if (color[0] < 15) {
                color[0] = 0;
                ClearField8();
                return;
            }
            color[0] -= 15;
            if (color[1] > 10) color[1] -= 10;
            if (color[2] > 10) color[2] -= 10;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounters(1);
            ++field074;
        }
        break;
    case 136:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.5f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            field074 = 0;
        }
        rotationZ -= 1.0f;
        scaleX += 0.01f;
        scaleY *= 0.95f;
        if (field074 > 1) {
            if (color[0] < 20) {
                color[0] = 0;
                ClearField8();
                return;
            }
            color[0] -= 20;
            if (color[1] > 10) color[1] -= 10;
            if (color[2] > 10) color[2] -= 10;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounters(1);
            ++field074;
        }
        break;
    case 137:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
        }
        scaleX += 0.05f;
        scaleY += 0.05f;
        if (color[0] > 15) {
            color[0] -= 15;
        }
        else {
            ClearField8();
            break;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 138:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = -40.0f;
            field01A = facing * 350;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.4f - field074 * 0.015f);
        scaleY += (0.4f - field074 * 0.015f);
        if (animationStage > 0) {
            if (color[0] > 30) {
                color[0] -= 30;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 139:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field074 = 0;
        }
        ++field074;
        scaleX += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        scaleY += (0.1f - field074 * 0.01f) * ((0.1f - field074 * 0.01f) > 0.0f) + 0.01f;
        if (animationStage > 0) {
            if (color[0] < 20) {
                color[0] = 0;
            }
            else {
                color[0] -= 20;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 140:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = facing * -60;
            rotationX = ChooseIntegerRange(0, 180);
            field074 = 0;
        }
        ++field074;
        rotationZ += 5.0f;
        scaleX += (0.6f - field074 * 0.02f);
        scaleY += (0.6f - field074 * 0.02f);
        if (animationStage > 0) {
            if (color[0] > 20) {
                color[0] -= 20;
            }
            else {
                color[0] = 0;
            }
            if (color[1] > 20) color[1] -= 20;
            if (color[2] > 20) color[2] -= 20;
        }
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 141:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
        }
        scaleX += 0.45f;
        scaleY += 0.45f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            color[0] = 0;
            ClearField8();
            break;
        }
        if (color[1] > 10) color[1] -= 10;
        if (color[2] > 10) color[2] -= 10;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 142:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
        }
        scaleX += 0.25f;
        scaleY += 0.25f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            color[0] = 0;
            ClearField8();
            break;
        }
        if (color[1] > 10) color[1] -= 10;
        if (color[2] > 10) color[2] -= 10;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 143:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            rotationX = ChooseIntegerRange(0, 60) - 30;
            rotationY = ChooseIntegerRange(0, 60) - 30;
        }
        rotationZ += 15.0f;
        rotationX += 4.0f;
        rotationY += 4.0f;
        scaleX += 0.14f;
        scaleY += 0.14f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            color[0] = 0;
            ClearField8();
            break;
        }
        if (color[1] > 10) color[1] -= 10;
        if (color[2] > 10) color[2] -= 10;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 144:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            rotationX = ChooseIntegerRange(0, 60) - 30;
            rotationY = ChooseIntegerRange(0, 60) - 30;
        }
        rotationZ -= 12.0f;
        scaleX += 0.12f;
        scaleY += 0.12f;
        rotationX -= 4.0f;
        rotationY -= 4.0f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            color[0] = 0;
            ClearField8();
            break;
        }
        if (color[1] > 10) color[1] -= 10;
        if (color[2] > 10) color[2] -= 10;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    case 145:
        if (animationStage == 0 && animationFrame == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = ChooseIntegerRange(0, 360);
            rotationX = ChooseIntegerRange(0, 60) - 30;
            rotationY = ChooseIntegerRange(0, 60) - 30;
        }
        rotationZ -= 10.0f;
        scaleX += 0.1f;
        scaleY += 0.1f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            color[0] = 0;
            ClearField8();
            break;
        }
        if (color[1] > 10) color[1] -= 10;
        if (color[2] > 10) color[2] -= 10;
        if (AdvanceNestedFrame() == field070) ClearField8();
        break;
    }
}

#undef F1135_POSITION_X
#undef F1135_POSITION_Y
#undef F1135_MOTION_X
#undef F1135_MOTION_Y

#undef F1136_ACTION_STAGE
#undef F1136_ACTION_FRAME
#undef F1136_ANIMATION_ACTION
#undef F1136_ACTION_TICK

#undef F1139_SCALE_X
#undef F1139_SCALE_Y
#undef F1139_ROTATE_AT28
#undef F1139_ROTATE_AT2C
#undef F1139_ROTATE_AT30
