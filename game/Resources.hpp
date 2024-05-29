#pragma once

#include <packer/Packer.h>
#include <memory>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
class PackerResources
{
public:
    static packer::Packer &get_packer()
    {
        static PackerResources instance;
        return *instance.packer_reader;
    }

private:
    std::unique_ptr<packer::Packer> packer_reader;
    PackerResources()
    {
        wchar_t szPath[MAX_PATH];
        GetModuleFileNameW(NULL, szPath, MAX_PATH);
        const std::filesystem::path exe_path(szPath);
        const auto exe_folder = exe_path.parent_path();
        const auto packer_path = exe_folder / "pack.db";
        packer_reader = std::make_unique<packer::Packer>(packer_path.generic_string());
    }

public:
    PackerResources(PackerResources const &) = delete;
    void operator=(PackerResources const &) = delete;
};
