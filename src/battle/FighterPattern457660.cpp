#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"
#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <vector>

#include "battle/Fighter.hpp"

#define FRAME (sequenceSlots[patternId]->frames[index])
#define EXTENSION (*reinterpret_cast<FighterPatternExtensionBorrowF1035*>(FRAME.pose))

void Fighter::LoadPattern() {
    unsigned int nRectangles;
    RECT boxData;
    FighterFrameInfo defaultFrame;
    unsigned int nBox;
    short packedValue;
    char szFilename[MAX_PATH];
    int frameTotal;
    char frameType;
    int index;
    unsigned int patternId;
    int count;
    HANDLE sourceFile;
    DWORD nRead;
    int iItem;

    sprintf(szFilename, "data\\character\\%s\\%s.pat", name, name);
    sourceFile = ResourceLookupF217::FindByName("datab")->SeekNamedEntry(szFilename);
    for (patternId = 0; patternId < sequenceSlots.size(); patternId++) {
        if (sequenceSlots[patternId]) {
            sequenceSlots[patternId]->frames.clear();
            delete sequenceSlots[patternId];
        }
    }
    sequenceSlots.clear();
    ReadFile(sourceFile, &patternId, 4, &nRead, 0);
    sequenceSlots.assign(patternId, 0);
    ReadFile(sourceFile, &count, 4, &nRead, 0);
    for (iItem = 0; iItem < count; iItem++) {
        ReadFile(sourceFile, &patternId, 4, &nRead, 0);
        if (!sequenceSlots[patternId])
            sequenceSlots[patternId] = new FighterSequenceInfo;
        ReadFile(sourceFile, &sequenceSlots[patternId]->targetPriority, 2, &nRead, 0);
        ReadFile(sourceFile, &sequenceSlots[patternId]->priority, 2, &nRead, 0);
        ReadFile(sourceFile, &frameTotal, 4, &nRead, 0);
        sequenceSlots[patternId]->frames.assign(frameTotal, defaultFrame);
        for (index = 0; index < frameTotal; index++) {
            ReadFile(sourceFile, &FRAME.textureIndex, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.originX, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.originY, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.unknown04, 2, &nRead, 0);
            ReadFile(sourceFile, &frameType, 1, &nRead, 0);
            if (frameType == 0) {
                FRAME.doubleScale = 1;
            } else if (frameType == 1) {
                FRAME.doubleScale = 0;
            } else if (frameType == 2) {
                // Declare this borrowed type at its real use site. Earlier
                // native filename literals keep their original COFF symbols.
#include "battle/FighterPatternExtensionBorrowF1035.hpp"
                FRAME.ResetExtension();
                ReadFile(sourceFile, &EXTENSION.firstWord.wordAt00, 2, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.firstWord.flagBytesAt00[1], 1, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.byteAt02, 1, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.byteAt03, 1, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.byteAt04, 1, &nRead, 0);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXTENSION.scaledAt0C = packedValue * 0.01f;
                EXTENSION.scaledAt10 = packedValue * 0.01f;
                EXTENSION.scaledAt14 = packedValue * 0.01f;
                ReadFile(sourceFile, &EXTENSION.wordAt06, 2, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.wordAt08, 2, &nRead, 0);
                ReadFile(sourceFile, &EXTENSION.wordAt0A, 2, &nRead, 0);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXTENSION.valueAt18 = static_cast<float>(packedValue);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXTENSION.valueAt1C = static_cast<float>(packedValue);
                ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
                EXTENSION.valueAt20 = static_cast<float>(packedValue);
            }
            ReadFile(sourceFile, &FRAME.damage, 2, &nRead, 0);
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.comboRateScale = packedValue * 0.001f;
            ReadFile(sourceFile, &FRAME.guardDamage, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.baseHitstun, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.attackerHitStop, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.defenderHitStop, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.guardAttackerHitStop, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.guardDefenderHitStop, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.meterGain, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.guardSpellCharge, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.airHitAction, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.groundHitAction, 2, &nRead, 0);
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.reactionVelocityX = packedValue * 0.01f;
            ReadFile(sourceFile, &packedValue, 2, &nRead, 0);
            FRAME.reactionVelocityY = packedValue * 0.01f;
            ReadFile(sourceFile, &FRAME.hitSound, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.hitEffect, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.reactionVariant, 2, &nRead, 0);
            ReadFile(sourceFile, &FRAME.flags, 4, &nRead, 0);
            ReadFile(sourceFile, &FRAME.attackFlags, 4, &nRead, 0);
            ReadFile(sourceFile, &FRAME.bodyBox, 16, &nRead, 0);
            ReadFile(sourceFile, &nRectangles, 4, &nRead, 0);
            for (nBox = 0; nBox < nRectangles; nBox++) {
                ReadFile(sourceFile, &boxData, 16, &nRead, 0);
                FRAME.hurtBoxes.push_back(boxData);
            }
            ReadFile(sourceFile, &nRectangles, 4, &nRead, 0);
            for (nBox = 0; nBox < nRectangles; nBox++) {
                ReadFile(sourceFile, &boxData, 16, &nRead, 0);
                FRAME.hitBoxes.push_back(boxData);
            }
        }
    }
}

#undef EXTENSION
#undef FRAME
