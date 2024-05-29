#pragma once

#include <packer/Packer.h>
#include <memory>

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
        packer_reader = std::make_unique<packer::Packer>("pack.db");
    }

public:
    PackerResources(PackerResources const &) = delete;
    void operator=(PackerResources const &) = delete;
};