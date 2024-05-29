#pragma once

#include <packer/Reader.h>
#include <memory>

class PackerResources
{
public:
    static packer::Reader &get_packer()
    {
        static PackerResources instance;
        return *instance.packer_reader;
    }

private:
    std::unique_ptr<packer::Reader> packer_reader;
    PackerResources()
    {
        packer_reader = std::make_unique<packer::Reader>("pack.db");
    }

public:
    PackerResources(PackerResources const &) = delete;
    void operator=(PackerResources const &) = delete;
};