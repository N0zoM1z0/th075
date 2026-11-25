#include "engine/GameProgress.hpp"
#include "graphics/FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>
#include "ui/ResultListScene.hpp"


extern const char g_ResultCounterEmptyAt0065811E[] = "";
extern const char g_ResultCounterFormat0At00658120[] = "%5d\\n";
extern const char g_ResultCounterFormat1At00658128[] = "%5d\\n";
extern const char g_ResultCounterFormat2At00658130[] = "%5d\\n";
extern const char g_ResultCounterFormat3At00658138[] = "%5d\\n";
extern const char g_ResultCounterFontAt00658140[];
void ResultListScene::BuildCounterPage()
{
    g_GameProgress.SetSelection((static_cast<unsigned char>(selectedCharacter)),(static_cast<unsigned char>(difficultyIndex)));
    selectedRecord=g_GameProgress.GetSelectedDifficultyRecord();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[500];
            strcpy(message,g_ResultCounterEmptyAt0065811E);
            sprintf(line,g_ResultCounterFormat0At00658120,selectedRecord->storyAttempts);
            strcat(message,line);
            sprintf(line,g_ResultCounterFormat1At00658128,static_cast<int>(selectedRecord->storyClears));
            strcat(message,line);
            sprintf(line,g_ResultCounterFormat2At00658130,selectedRecord->maxComboHits);
            strcat(message,line);
            sprintf(line,g_ResultCounterFormat3At00658138,selectedRecord->maxComboDamage);
            strcat(message,line);
            if (canvas->LockRect(0,&locked,0,0)==D3D_OK) {
                FontSurface *glyph=new FontSurface(0);
                glyph->ConfigureFont(g_ResultCounterFontAt00658140,16,255,255,255);
                glyph->RasterizeText(message,locked.pBits,1024,512,560,0,8,4,40);
                delete glyph;
                canvas->UnlockRect(0);
            }
        }
    }
}
