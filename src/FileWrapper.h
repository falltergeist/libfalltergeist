#pragma once

#include <memory>
#include "IFile.h"

namespace libfalltergeist {
    class FileWrapper : public IFile {
    public:
        explicit FileWrapper(std::shared_ptr<IFile> file);
        ~FileWrapper() override = default;
        void seek(uint32_t position) override;
        uint32_t position() override;
        uint32_t readBytes(uint8_t* destination, uint32_t count) override;
        uint32_t size() override;
        uint32_t uint32();
        int32_t int32();
        uint16_t uint16();
        int16_t int16();
        uint8_t uint8();
        int8_t int8();
        FileWrapper& operator>>(uint32_t &value);
        FileWrapper& operator>>(int32_t &value);
        FileWrapper& operator>>(uint16_t &value);
        FileWrapper& operator>>(int16_t &value);
        FileWrapper& operator>>(uint8_t &value);
        FileWrapper& operator>>(int8_t &value);
    private:
        std::shared_ptr<IFile> _file;
    };
}
