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
// Complete original R065 1,958-CODE-byte battle input/replay dispatcher.
// The separately owned 28-byte native 7-entry switch table is validated in
// compare_size=1986 but earns zero additional authored CODE credit.
// The deque size is unsigned. The thiscall key scanner
// and positive cancel-flag condition preserve the native branch layout.
// firstRecord is physically read and stored in the original even though
// another front() reads the active command before dispatch.
// Observed original call ABIs and field offsets only, not a whole battle class.
void BattleScene::ApplySequence() {
    if(g_CombatMode==CombatMode::Practice) {
        ProcessDebugKeys();
    } else {
        if(g_ReplayModeAt0066C238==ReplayMode::Playback) {
            if(g_ReplayRecords.timedBattleCommands.size()>0) {
                int firstRecord=g_ReplayRecords.timedBattleCommands.front();
                while(field014==g_ReplayRecords.timedBattleCommands.front()) {
                    g_ReplayRecords.timedBattleCommands.pop_front();
                    int command=g_ReplayRecords.timedBattleCommands.front();
                    g_ReplayRecords.timedBattleCommands.pop_front();
                    switch(command) {
                    case 1: fighters[1]->health=1;break;
                    case 2: fighters[0]->field39D=2;fighters[1]->field39D=2;break;
                    case 3:
                        if(fighters[0]->field39D>1) --fighters[0]->field39D;
                        if(fighters[1]->field39D>1) --fighters[1]->field39D;
                        break;
                    case 4: field01C=0;break;
                    case 5: field01C=1;break;
                    case 6:
                        fighters[0]->spellPower=(fighters[0]->spellPower)+FloatConstants::Ten;
                        fighters[1]->spellPower=(fighters[1]->spellPower)+FloatConstants::Ten;
                        if((fighters[0]->spellPower)>GeometryConstants::NineHundred) fighters[0]->spellPower=900.0f;
                        if((fighters[1]->spellPower)>GeometryConstants::NineHundred) fighters[1]->spellPower=900.0f;
                        break;
                    case 7:
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
            if(!g_InputMappings[0].IsKeyDown(0x3D)) field110=0;
            if(g_CombatMode!=CombatMode::Story && g_CombatMode!=CombatMode::Arcade) {
                if(g_InputMappings[0].IsKeyDown(0x3C)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                        int action2=2;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action2));
                    }
                    fighters[0]->field39D=2;fighters[1]->field39D=2;
                }
                if(g_InputMappings[0].IsKeyDown(0x3D)) {
                    if(field110==0) {
                        if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                            g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                            int action3=3;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action3));
                        }
                        if(fighters[0]->field39D>1) --fighters[0]->field39D;
                        if(fighters[1]->field39D>1) --fighters[1]->field39D;
                    }
                    field110=field110+1;
                }
                if(g_InputMappings[0].IsKeyDown(0x3E)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                        int action4=4;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action4));
                    }
                    field01C=0;
                }
                if(g_InputMappings[0].IsKeyDown(0x3F)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                        int action5=5;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action5));
                    }
                    field01C=1;
                }
                if(g_InputMappings[0].IsKeyDown(0x40)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                        int action6=6;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action6));
                    }
                    fighters[0]->spellPower=(fighters[0]->spellPower)+FloatConstants::Ten;
                    fighters[1]->spellPower=(fighters[1]->spellPower)+FloatConstants::Ten;
                    if((fighters[0]->spellPower)>GeometryConstants::NineHundred) fighters[0]->spellPower=900.0f;
                    if((fighters[1]->spellPower)>GeometryConstants::NineHundred) fighters[1]->spellPower=900.0f;
                }
                if(g_InputMappings[0].IsKeyDown(0x41)) {
                    if(g_ReplayModeAt0066C238==ReplayMode::Recording) {
                        g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(field014));
                        int action7=7;g_ReplayRecords.timedBattleCommands.push_back(reinterpret_cast<const unsigned int&>(action7));
                    }
                    fighters[0]->spellPower=(fighters[0]->spellPower)-FloatConstants::Ten;
                    fighters[1]->spellPower=(fighters[1]->spellPower)-FloatConstants::Ten;
                    if((fighters[0]->spellPower)<FloatConstants::Zero) fighters[0]->spellPower=0.0f;
                    if((fighters[1]->spellPower)<FloatConstants::Zero) fighters[1]->spellPower=0.0f;
                }
            }
        }
        if(g_ReplayModeAt0066C238==ReplayMode::Playback && (g_InputMappings[0].IsKeyDown(0x1D) || g_InputMappings[0].IsKeyDown(0x9D))) {
            if(g_InputMappings[0].IsKeyDown(3)) SetClampedGameValue(8);
            else if(g_InputMappings[0].IsKeyDown(4)) SetClampedGameValue(6);
            else if(g_InputMappings[0].IsKeyDown(5)) SetClampedGameValue(4);
            else if(g_InputMappings[0].IsKeyDown(6)) SetClampedGameValue(3);
            else if(g_InputMappings[0].IsKeyDown(7)) SetClampedGameValue(2);
            else if(g_InputMappings[0].IsKeyDown(8)) SetClampedGameValue(1);
            else SetClampedGameValue(0x10);
        }
        if(g_ReplayModeAt0066C238==ReplayMode::Recording || g_ReplayModeAt0066C238==ReplayMode::LiveDialogue) {
            if(g_InputMappings[0].IsKeyDown(0x1D) || g_InputMappings[0].IsKeyDown(0x9D) || static_cast<unsigned int>(g_InputMappings[0].held.counts[InputControl::ButtonD])>5) g_InputCanCancelAt00671632=1;
            else g_InputCanCancelAt00671632=0;
        }
    }
}
