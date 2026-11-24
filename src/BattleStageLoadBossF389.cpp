#include "BattleSessionState.hpp"
#include "BattleResourceLoaders.hpp"
#include "GameSharedState.hpp"
#include "DiagnosticLog.hpp"
#include "GameProgress.hpp"
#include "AudioControl.hpp"
#include "BackgroundStages.hpp"

extern unsigned char g_OptionsFlagAt00671604;
extern const char g_StartStageLogAt00657A4C[];
extern const char g_EndStageLogAt00657A5C[];
void BattleStageLoaderF389::LoadStage() {
    DiagnosticLog::AppendString(g_StartStageLogAt00657A4C);
    if(g_CurrentBattleStageAt00671424) {
        delete g_CurrentBattleStageAt00671424;
        g_CurrentBattleStageAt00671424=0;
    }
    switch(g_StageSelectionAt0067161D) {
    case 0:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new Background00aF376;
        else g_CurrentBattleStageAt00671424=new BackgroundBG00xF377;
        break;
    case 1:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG01aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG01xF377;
        break;
    case 2:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG02aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG02xF377;
        break;
    case 3:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG03aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG03xF377;
        break;
    case 4:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG04aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG04xF377;
        break;
    case 5:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG05aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG05xF377;
        break;
    case 6:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG06aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG06xF377;
        break;
    case 7:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG07aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG07xF377;
        break;
    case 8:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG08aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG08xF377;
        break;
    case 9:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG09aF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG09xF377;
        break;
    case 10:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new Background00bF376;
        else g_CurrentBattleStageAt00671424=new BackgroundBG00yF377;
        break;
    case 11:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG01bF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG01yF377;
        break;
    case 12:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG02bF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG02yF377;
        break;
    case 13:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG03bF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG03yF377;
        break;
    case 14:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG04bF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG04yF377;
        break;
    case 15:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG05bF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG05yF377;
        break;
    case 20:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG00cF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG00zF377;
        break;
    case 22:
        if(g_OptionsFlagAt00671604!=0) g_CurrentBattleStageAt00671424=new BackgroundBG02cF377;
        else g_CurrentBattleStageAt00671424=new BackgroundBG02zF377;
        break;
    }
    if(g_CombatMode!=3) MusicF204::PlayTrackByIndex(int(g_StageSelectionAt0067161D));
    if(g_ReplayModeAt0066C238!=2 && g_ReplayModeAt0066C238!=4)
        g_GameProgress.SetUnlockBit(int(g_StageSelectionAt0067161D)+200);
    DiagnosticLog::AppendString(g_EndStageLogAt00657A5C);
}
