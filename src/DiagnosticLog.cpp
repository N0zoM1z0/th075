#include "DiagnosticLog.hpp"
#include <windows.h>
#include <stdio.h>
#include <string.h>

namespace DiagnosticLog
{
    extern char g_Path[];

    void InitializeFile(const char *path)
    {
        strcpy(g_Path, path);
        HANDLE file = CreateFileA(g_Path, GENERIC_WRITE, 0, 0,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        CloseHandle(file);
    }

    void AppendString(const char *message)
    {
        HANDLE handle;
        {
            size_t byteCount = strlen(message);
            DWORD bytesWritten;
            handle = CreateFileA(g_Path, GENERIC_WRITE, 0, 0,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            if (handle == INVALID_HANDLE_VALUE)
                return;
            SetFilePointer(handle, 0, 0, FILE_END);
            WriteFile(handle, message, byteCount, &bytesWritten, 0);
        }
        CloseHandle(handle);
    }

    void AppendInteger(int value)
    {
        HANDLE handle;
        {
            size_t byteCount;
            {
                char message[20];
                DWORD bytesWritten;
                sprintf(message, "%d", value);
                byteCount = strlen(message);
                handle = CreateFileA(g_Path, GENERIC_WRITE, 0, 0,
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                if (handle == INVALID_HANDLE_VALUE)
                    return;
                SetFilePointer(handle, 0, 0, FILE_END);
                WriteFile(handle, message, byteCount, &bytesWritten, 0);
            }
        }
        CloseHandle(handle);
    }

    void AppendFloat(float value)
    {
        HANDLE handle;
        {
            size_t byteCount;
            {
                char message[100];
                DWORD bytesWritten;
                sprintf(message, "%f", value);
                byteCount = strlen(message);
                handle = CreateFileA(g_Path, GENERIC_WRITE, 0, 0,
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                if (handle == INVALID_HANDLE_VALUE)
                    return;
                SetFilePointer(handle, 0, 0, FILE_END);
                WriteFile(handle, message, byteCount, &bytesWritten, 0);
            }
        }
        CloseHandle(handle);
    }
}
