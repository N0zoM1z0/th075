// Remilia's seven switch tables route 239 action IDs to the default handler
// at 0x00551598. Reset the primary counters when the nested frame result
// equals the animation stage count.
default:
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    break;
