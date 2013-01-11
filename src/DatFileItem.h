#ifndef LIBFALLTERGEIST_DATFILEITEM_H
#define LIBFALLTERGEIST_DATFILEITEM_H

namespace Libfalltergeist
{

class DatFileItem
{
protected:
    char * _filename; // filename with path (path/to/file.ext)
    unsigned int _dataOffset; // data offset in the DAT file
    unsigned int _unpackedSize; // unpacked data size
    unsigned int _packedSize; // packed data size
    bool _packed; // is packed?
public:

    char * data; // file data

    DatFileItem();
    ~DatFileItem();

    void setFilename(char * filename);
    char * getFilename();

    void setDataOffset(unsigned int offset);
    unsigned int getDataOffset();

    void setUnpackedSize(unsigned int size);
    unsigned int getUnpackedSize();

    void setPackedSize(unsigned int size);
    unsigned int getPackedSize();

    void setPacked(bool packed);
    bool getPacked();
};

}
#endif //LIBFALLTERGEIST_DATFILEITEM_H
