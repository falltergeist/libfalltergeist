
#include "FileWrapper.h"

namespace libfalltergeist {
    FileWrapper::FileWrapper(std::shared_ptr<IFile> file) {
        _file = std::move(file);
    }

    void FileWrapper::seek(uint32_t position) {
        _file->seek(position);
    }

    uint32_t FileWrapper::position() {
        return _file->position();
    }

    uint32_t FileWrapper::readBytes(uint8_t* destination, uint32_t count) {
        return _file->readBytes(destination, count);
    }

    uint32_t FileWrapper::size() {
        return _file->size();
    }

    FileWrapper& FileWrapper::operator>>(uint32_t &value) {
        readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
        return *this;
    }

    FileWrapper& FileWrapper::operator>>(int32_t &value) {
        return *this >> (uint32_t&) value;
    }

    FileWrapper& FileWrapper::operator>>(uint16_t &value) {
        readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
        return *this;
    }

    FileWrapper& FileWrapper::operator>>(int16_t &value) {
        return *this >> (uint16_t&) value;
    }

    FileWrapper& FileWrapper::operator>>(uint8_t &value) {
        readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
        return *this;
    }

    FileWrapper& FileWrapper::operator>>(int8_t &value) {
        return *this >> (uint8_t&) value;
    }

    uint32_t FileWrapper::uint32() {
        uint32_t value;
        *this >> value;
        return value;
    }

    int32_t FileWrapper::int32() {
        return uint32();
    }

    uint16_t FileWrapper::uint16() {
        uint16_t value;
        *this >> value;
        return value;
    }

    int16_t FileWrapper::int16() {
        return uint16();
    }

    uint8_t FileWrapper::uint8() {
        uint8_t value;
        *this >> value;
        return value;
    }

    int8_t FileWrapper::int8() {
        return uint8();
    }
}
