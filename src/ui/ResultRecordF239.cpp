#include "engine/GameProgress.hpp"
#include "graphics/FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>
#include "ui/ResultListScene.hpp"


extern const char g_RecordEmptyAt006580B1[] = "";
extern const char g_RecordEmptyNameAt006580B4[] = "\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48";
extern const char g_RecordMissingFormatAt006580D8[] = " No.%03d  %-59s %03d/%03d\\n";
extern const char g_RecordFullFormatAt006580F4[] = " No.%03d  %-59s %03d/%03d\\n";
extern const char g_RecordFontAt00658110[];
void ResultListScene::BuildRecordPage()
{
    g_GameProgress.SetSelection((static_cast<unsigned char>(selectedCharacter)),0);
    selectedRecord = g_GameProgress.GetSelectedDifficultyRecord();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[2000];
            strcpy(message,g_RecordEmptyAt006580B1);
            for (int i=(pageIndex)*10;
                 i<(pageIndex)*10+10 && i<static_cast<int>(records.size()); ++i) {
                if (selectedRecord->spellAttempts[i]==0)
                    sprintf(line,g_RecordMissingFormatAt006580D8,i+1,g_RecordEmptyNameAt006580B4,0,0);
                else
                    sprintf(line,g_RecordFullFormatAt006580F4,i+1,records[i],
                            static_cast<unsigned int>(selectedRecord->spellBonusClears[i]),static_cast<unsigned int>(selectedRecord->spellAttempts[i]));
                strcat(message,line);
            }
            if ((canvas)->LockRect(0,&locked,0,0)==D3D_OK) {
                FontSurface* glyph=new FontSurface(0);
                glyph->ConfigureFont(g_RecordFontAt00658110,16,120,120,255);
                glyph->RasterizeText(message,locked.pBits,1024,512,640,0,16,4,40);
                delete glyph;
                (canvas)->UnlockRect(0);
            }
        }
    }
}
