#include "input/InputControl.hpp"
#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"
#include <dinput.h>

namespace TimedBattleCommand {
    enum Value {
        SetOpponentHealthToOne = 1,
        RestoreRoundStock = 2,
        ReduceRoundStock = 3,
        DisableResourceRestore = 4,
        EnableResourceRestore = 5,
        AddSpellPower = 6,
        RemoveSpellPower = 7,
    };
}

void BattleScene::ApplySequence() {
    if(g_CombatMode==CombatMode::Practice) {
        ProcessDebugKeys();
    } else {
        if(g_ReplayModeAt0066C238==ReplayMode::Playback) {
            if(g_ReplayRecords.timedBattleCommands.size()>0) {
                int firstRecord=g_ReplayRecords.timedBattleCommands.front();
                while(replayFrame==g_ReplayRecords.timedBattleCommands.front()) {
                    g_ReplayRecords.timedBattleCommands.pop_front();
                    int command=g_ReplayRecords.timedBattleCommands.front();
                    g_ReplayRecords.timedBattleCommands.pop_front();
                    switch(command) {
                    case TimedBattleCommand::SetOpponentHealthToOne: fighters[1]->health=1;break;
                    case TimedBattleCommand::RestoreRoundStock: fighters[0]->roundsRemaining=2;fighters[1]->roundsRemaining=2;break;
                    case TimedBattleCommand::ReduceRoundStock:
                        if(fighters[0]->roundsRemaining>1) --fighters[0]->roundsRemaining;
                        if(fighters[1]->roundsRemaining>1) --fighters[1]->roundsRemaining;
                        break;
                    case TimedBattleCommand::DisableResourceRestore: restoreResources=0;break;
                    case TimedBattleCommand::EnableResourceRestore: restoreResources=1;break;
                    case TimedBattleCommand::AddSpellPower:
                        fighters[0]->spellPower=(fighters[0]->spellPower)+FloatConstants::Ten;
                        fighters[1]->spellPower=(fighters[1]->spellPower)+FloatConstants::Ten;
                        if((fighters[0]->spellPower)>GeometryConstants::NineHundred) fighters[0]->spellPower=900.0f;
                        if((fighters[1]->spellPower)>GeometryConstants::NineHundred) fighters[1]->spellPower=900.0f;
                        break;
                    case TimedBattleCommand::RemoveSpellPower:
                        fighters[0]->spellPower=(fighters[0]->spellPower)-FloatConstants::Ten;
                        fighters[1]->spellPower=(fighters[1]->spellPower)-FloatConstants::Ten;
                        if((fighters[0]->spellPower)<FloatConstants::Zero) fighters[0]->spellPower=0.0f;
                        if((fighters[1]->spellPower)<FloatConstants::Zero) fighters[1]->spellPower=0.0f;
                        break;
                    }
                    if(g_ReplayRecords.timedBattleCommands.size()<=0) break;
                }
            }
        } else {
            if(!g_InputMappings[0].IsKeyDown(DIK_F3)) reduceRoundStockKeyHeldFrames=0;
            if(g_CombatMode!=CombatMode::Story && g_CombatMode!=CombatMode::Arcade) {
                if(g_InputMappings[0].IsKeyDown(DIK_F2)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                        int command = TimedBattleCommand::RestoreRoundStock;
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                    }
                    fighters[0]->roundsRemaining=2;fighters[1]->roundsRemaining=2;
                }
                if(g_InputMappings[0].IsKeyDown(DIK_F3)) {
                    if(reduceRoundStockKeyHeldFrames==0) {
                        if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                            g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                            int command = TimedBattleCommand::ReduceRoundStock;
                            g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                        }
                        if(fighters[0]->roundsRemaining>1) --fighters[0]->roundsRemaining;
                        if(fighters[1]->roundsRemaining>1) --fighters[1]->roundsRemaining;
                    }
                    reduceRoundStockKeyHeldFrames=reduceRoundStockKeyHeldFrames+1;
                }
                if(g_InputMappings[0].IsKeyDown(DIK_F4)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                        int command = TimedBattleCommand::DisableResourceRestore;
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                    }
                    restoreResources=0;
                }
                if(g_InputMappings[0].IsKeyDown(DIK_F5)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                        int command = TimedBattleCommand::EnableResourceRestore;
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                    }
                    restoreResources=1;
                }
                if(g_InputMappings[0].IsKeyDown(DIK_F6)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                        int command = TimedBattleCommand::AddSpellPower;
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                    }
                    fighters[0]->spellPower=(fighters[0]->spellPower)+FloatConstants::Ten;
                    fighters[1]->spellPower=(fighters[1]->spellPower)+FloatConstants::Ten;
                    if((fighters[0]->spellPower)>GeometryConstants::NineHundred) fighters[0]->spellPower=900.0f;
                    if((fighters[1]->spellPower)>GeometryConstants::NineHundred) fighters[1]->spellPower=900.0f;
                }
                if(g_InputMappings[0].IsKeyDown(DIK_F7)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(replayFrame));
                        int command = TimedBattleCommand::RemoveSpellPower;
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(command));
                    }
                    fighters[0]->spellPower=(fighters[0]->spellPower)-FloatConstants::Ten;
                    fighters[1]->spellPower=(fighters[1]->spellPower)-FloatConstants::Ten;
                    if((fighters[0]->spellPower)<FloatConstants::Zero) fighters[0]->spellPower=0.0f;
                    if((fighters[1]->spellPower)<FloatConstants::Zero) fighters[1]->spellPower=0.0f;
                }
            }
        }
        if(g_ReplayModeAt0066C238==ReplayMode::Playback && (g_InputMappings[0].IsKeyDown(DIK_LCONTROL) || g_InputMappings[0].IsKeyDown(DIK_RCONTROL))) {
            if(g_InputMappings[0].IsKeyDown(DIK_2)) SetClampedGameValue(8);
            else if(g_InputMappings[0].IsKeyDown(DIK_3)) SetClampedGameValue(6);
            else if(g_InputMappings[0].IsKeyDown(DIK_4)) SetClampedGameValue(4);
            else if(g_InputMappings[0].IsKeyDown(DIK_5)) SetClampedGameValue(3);
            else if(g_InputMappings[0].IsKeyDown(DIK_6)) SetClampedGameValue(2);
            else if(g_InputMappings[0].IsKeyDown(DIK_7)) SetClampedGameValue(1);
            else SetClampedGameValue(0x10);
        }
        if(g_ReplayModeAt0066C238==ReplayMode::Recording || g_ReplayModeAt0066C238==ReplayMode::LiveDialogue) {
            if(g_InputMappings[0].IsKeyDown(DIK_LCONTROL) || g_InputMappings[0].IsKeyDown(DIK_RCONTROL) || static_cast<unsigned int>(g_InputMappings[0].held.counts[InputControl::ButtonD])>5) g_InputCanCancelAt00671632=1;
            else g_InputCanCancelAt00671632=0;
        }
    }
}
