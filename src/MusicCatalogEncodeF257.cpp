#include <windows.h>
#include <stdlib.h>
#include <new>

// Only the observed game-specific file converter and borrowed thiscall ABI
// are reconstructed here; the complete music-room scene layout is unknown.
extern const char g_MusicCatalogPlainAt00657C90[];
extern const char g_MusicCatalogEncodedAt00657CA0[];
class MusicCatalogEncoderF257 {
public:
    void EncodeCatalogFile();
};

void MusicCatalogEncoderF257::EncodeCatalogFile()
{
    HANDLE file;
    {
        DWORD transferred;
        {
            DWORD fileBytes;
            {
                char* content;
                file = CreateFileA(g_MusicCatalogPlainAt00657C90, GENERIC_READ,
                                   0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                if (file == INVALID_HANDLE_VALUE) return;
                fileBytes = GetFileSize(file, 0);
                {
                    unsigned char delta;
                    {
                        unsigned char key;
                        {
                            unsigned int index;
                            {
                                // Keep the actual allocation and byte-buffer
                                // pointers distinct, as observed in the PE.
                                char* allocation = reinterpret_cast<char*>(::operator new(fileBytes));
                                content = allocation;
                            }
                            ReadFile(file, content, fileBytes, &transferred, 0);
                            CloseHandle(file);
                            file = CreateFileA(g_MusicCatalogEncodedAt00657CA0, GENERIC_WRITE,
                                               0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
                            if (file != INVALID_HANDLE_VALUE) {
                                key = 0x5c;
                                delta = 0x5a;
                                for (index = 0; index < fileBytes; ++index) {
                                    content[index] = content[index] ^ key;
                                    key += delta;
                                    delta += '=';
                                }
                                WriteFile(file, content, fileBytes, &transferred, 0);
                                CloseHandle(file);
                            }
                        }
                    }
                }
                {
                    void* completedBuffer = content;
                    free(completedBuffer);
                }
            }
        }
    }
}
