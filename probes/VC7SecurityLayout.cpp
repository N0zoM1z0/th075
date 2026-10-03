#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <stddef.h>

extern "C" const unsigned long SecurityLayoutProbe[] = {
    sizeof(NT_TIB), offsetof(NT_TIB, StackBase),
    offsetof(NT_TIB, StackLimit), offsetof(NT_TIB, Self),
    sizeof(MEMORY_BASIC_INFORMATION),
    offsetof(MEMORY_BASIC_INFORMATION, AllocationBase),
    offsetof(MEMORY_BASIC_INFORMATION, Protect),
    offsetof(MEMORY_BASIC_INFORMATION, Type), MEM_IMAGE,
    PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY,
    sizeof(IMAGE_DOS_HEADER), offsetof(IMAGE_DOS_HEADER, e_lfanew),
    offsetof(IMAGE_NT_HEADERS, Signature),
    offsetof(IMAGE_NT_HEADERS, FileHeader.NumberOfSections),
    offsetof(IMAGE_NT_HEADERS, FileHeader.SizeOfOptionalHeader),
    offsetof(IMAGE_NT_HEADERS, OptionalHeader),
    IMAGE_DOS_SIGNATURE, IMAGE_NT_SIGNATURE, IMAGE_NT_OPTIONAL_HDR32_MAGIC,
    sizeof(IMAGE_SECTION_HEADER), offsetof(IMAGE_SECTION_HEADER, Misc.VirtualSize),
    offsetof(IMAGE_SECTION_HEADER, VirtualAddress),
    offsetof(IMAGE_SECTION_HEADER, Characteristics), IMAGE_SCN_MEM_WRITE,
    sizeof(FILETIME), offsetof(FILETIME, dwLowDateTime), offsetof(FILETIME, dwHighDateTime),
    sizeof(LARGE_INTEGER), offsetof(LARGE_INTEGER, LowPart), offsetof(LARGE_INTEGER, HighPart)
};
