#include <game/core/PackerProvider.hpp>
#include <miniz/miniz.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <game/resources.hpp>
#include <fstream>
std::filesystem::path get_packer_path()
{
    wchar_t szPath[MAX_PATH];
    GetModuleFileNameW(NULL, szPath, MAX_PATH);
    const std::filesystem::path exe_path(szPath);
    const auto exe_folder = exe_path.parent_path();
    const auto packer_path = exe_folder / "pack.db";
    return packer_path;
}

void remove_packer_if_exists(const std::filesystem::path packer_path)
{
    if (std::filesystem::exists(packer_path))
    {
        std::filesystem::remove(packer_path);
    }
}

static int tinfl_write_into_ofstream(const void *pBuf, int len, void *pUser)
{
    ((std::ofstream *)pUser)->write((char *)pBuf, len);
    return 1;
}

void extract_packer_from_executable(const std::filesystem::path packer_path)
{
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(IDR_SQLITE1), "sqlite");
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    DWORD dwSize = SizeofResource(hModule, hResource);
    LPVOID lpAddress = LockResource(hMemory);
    std::vector<char> bytes;
    bytes.reserve(dwSize);    
    memcpy(bytes.data(), lpAddress, dwSize);
    size_t in_buf_size = (size_t)dwSize;
    std::ofstream stream;
    stream.open(packer_path, std::ios::app | std::ios::binary);
    tinfl_decompress_mem_to_callback(bytes.data(), &in_buf_size, tinfl_write_into_ofstream, &stream, TINFL_FLAG_PARSE_ZLIB_HEADER);
    stream.close();
}
