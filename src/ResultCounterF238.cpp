#include "GameProgress.hpp"
#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>
#include "ResultListScene.hpp"


// This side-only view represents observed calls and physical fields, not a
// complete original game scene or named original class layout.
extern const char g_ResultCounterEmptyAt0065811E[] = "";
extern const char g_ResultCounterFormat0At00658120[];
extern const char g_ResultCounterFormat1At00658128[];
extern const char g_ResultCounterFormat2At00658130[];
extern const char g_ResultCounterFormat3At00658138[];
extern const char g_ResultCounterFontAt00658140[];
void ResultListScene::BuildCounterPage()
{
    g_GameProgress.SetSelection((static_cast<unsigned char>(selectedCharacter)),(static_cast<unsigned char>(difficultyIndex)));
    selectedRecord=&g_GameProgress.GetSelectedRecordAddress()->field000;
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[500];
    strcpy(message,g_ResultCounterEmptyAt0065811E);
    sprintf(line,g_ResultCounterFormat0At00658120,reinterpret_cast<int*>(selectedRecord)[0]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat1At00658128,reinterpret_cast<int*>(selectedRecord)[1]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat2At00658130,reinterpret_cast<int*>(selectedRecord)[2]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat3At00658138,reinterpret_cast<int*>(selectedRecord)[3]);
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
