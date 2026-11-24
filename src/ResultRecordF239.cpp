#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>
#include "ResultListScene.hpp"


// Borrowed original record selection and deque access interfaces. No full
// nominal class/allocator ownership layout is reconstructed in this source.
class ResultRecordProgressF239 {public:
    void Select(unsigned char first, unsigned char second);
    void* GetSelectedRecordAddress();
};
extern ResultRecordProgressF239 g_RecordProgressAt006718F8;
extern const char g_RecordEmptyAt006580B1[];
extern const char g_RecordEmptyNameAt006580B4[];
extern const char g_RecordMissingFormatAt006580D8[];
extern const char g_RecordFullFormatAt006580F4[];
extern const char g_RecordFontAt00658110[];
#define META(index,offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(selectedRecord)+(offset)+2*(index)))
void ResultListScene::BuildRecordPage()
{
    g_RecordProgressAt006718F8.Select((static_cast<unsigned char>(selectedCharacter)),0);
    (selectedRecord)=g_RecordProgressAt006718F8.GetSelectedRecordAddress();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[2000];
            strcpy(message,g_RecordEmptyAt006580B1);
            for (int i=(pageIndex)*10;
                 i<(pageIndex)*10+10 && i<records.Size(); ++i) {
                if (META(i,0x394)==0)
                    sprintf(line,g_RecordMissingFormatAt006580D8,i+1,g_RecordEmptyNameAt006580B4,0,0);
                else
                    sprintf(line,g_RecordFullFormatAt006580F4,i+1,*records.Entry(i),
                            static_cast<unsigned int>(META(i,0x268)),static_cast<unsigned int>(META(i,0x394)));
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
#undef META
