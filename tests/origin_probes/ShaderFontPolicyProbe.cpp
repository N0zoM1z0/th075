// Original public SDK, Win32 resource, font and dynamic-storage declarations.
// No private assembler, file, resource, font or text class layout is declared.
#include <initguid.h>
#include <d3dx8.h>
#include <malloc.h>
#include <stddef.h>

HRESULT ProbeShaderFileA(const char *path, DWORD flags, ID3DXBuffer **constants,
    ID3DXBuffer **shader, ID3DXBuffer **errors)
{
    return D3DXAssembleShaderFromFileA(path, flags, constants, shader, errors);
}

HRESULT ProbeShaderFileW(const WCHAR *path, DWORD flags, ID3DXBuffer **constants,
    ID3DXBuffer **shader, ID3DXBuffer **errors)
{
    return D3DXAssembleShaderFromFileW(path, flags, constants, shader, errors);
}

HRESULT ProbeShaderResourceA(HMODULE owner, const char *name, DWORD flags,
    ID3DXBuffer **constants, ID3DXBuffer **shader, ID3DXBuffer **errors)
{
    return D3DXAssembleShaderFromResourceA(owner, name, flags, constants, shader, errors);
}

HRESULT ProbeShaderResourceW(HMODULE owner, const WCHAR *name, DWORD flags,
    ID3DXBuffer **constants, ID3DXBuffer **shader, ID3DXBuffer **errors)
{
    return D3DXAssembleShaderFromResourceW(owner, name, flags, constants, shader, errors);
}

HRESULT ProbeErrorTextW(HRESULT code, WCHAR *buffer, UINT count)
{
    return D3DXGetErrorStringW(code, buffer, count);
}

HRESULT ProbeCreateFont(IDirect3DDevice8 *device, const LOGFONTA *description,
    ID3DXFont **font)
{
    return D3DXCreateFontIndirect(device, description, font);
}

INT ProbeFontTextW(ID3DXFont *font, const WCHAR *text, INT count,
    RECT *rect, DWORD format, D3DCOLOR color)
{
    return font->DrawTextW(text, count, rect, format, color);
}

extern "C" void ProbeUseWideStorage(WCHAR *, UINT);
void ProbeWideStorage(UINT count)
{
    WCHAR *buffer = static_cast<WCHAR *>(_alloca(count * sizeof(WCHAR)));
    ProbeUseWideStorage(buffer, count);
}

HRSRC ProbeResourceA(HMODULE owner, const char *name, const char *type)
{
    return FindResourceA(owner, name, type);
}

HRSRC ProbeResourceW(HMODULE owner, const WCHAR *name, const WCHAR *type)
{
    return FindResourceW(owner, name, type);
}

HGLOBAL ProbeResourceLoad(HMODULE owner, HRSRC resource)
{
    return LoadResource(owner, resource);
}

DWORD ProbeResourceSize(HMODULE owner, HRSRC resource)
{
    return SizeofResource(owner, resource);
}

void *ProbeResourceLock(HGLOBAL resource)
{
    return LockResource(resource);
}

HFONT ProbeGdiFont(const LOGFONTA *description)
{
    return CreateFontIndirectA(description);
}

BOOL ProbeGdiDelete(HGDIOBJ item)
{
    return DeleteObject(item);
}

int ProbeToWide(UINT page, const char *input, int input_size, WCHAR *output,
    int output_size)
{
    return MultiByteToWideChar(page, 0, input, input_size, output, output_size);
}

int ProbeToAnsi(UINT page, const WCHAR *input, int input_size, char *output,
    int output_size)
{
    return WideCharToMultiByte(page, 0, input, input_size, output, output_size, 0, 0);
}

extern const GUID ShaderFontIUnknown = __uuidof(IUnknown);
extern const unsigned int ShaderFontPublicLayout[] = {
    sizeof(GUID), sizeof(WCHAR), sizeof(LOGFONTA), sizeof(RECT), sizeof(void *),
    offsetof(LOGFONTA, lfHeight), offsetof(LOGFONTA, lfWidth),
    offsetof(LOGFONTA, lfEscapement), offsetof(LOGFONTA, lfOrientation),
    offsetof(LOGFONTA, lfWeight), offsetof(LOGFONTA, lfItalic),
    offsetof(LOGFONTA, lfUnderline), offsetof(LOGFONTA, lfStrikeOut),
    offsetof(LOGFONTA, lfCharSet), offsetof(LOGFONTA, lfOutPrecision),
    offsetof(LOGFONTA, lfClipPrecision), offsetof(LOGFONTA, lfQuality),
    offsetof(LOGFONTA, lfPitchAndFamily), offsetof(LOGFONTA, lfFaceName),
    LF_FACESIZE, CP_ACP, D3DXASM_DEBUG
};
