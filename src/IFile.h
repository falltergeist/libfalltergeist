#pragma once

#include <cstdint>

namespace libfalltergeist {
    class IFile {
    public:
        virtual ~IFile() = default;
        virtual void seek(uint32_t position) = 0;
        virtual uint32_t position() = 0;
        virtual uint32_t readBytes(uint8_t* destination, uint32_t count) = 0;
        virtual uint32_t size() = 0;
    };
}