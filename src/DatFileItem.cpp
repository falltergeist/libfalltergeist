#include "DatFileItem.h"

#include "string.h"

namespace Libfalltergeist
{

DatFileItem::DatFileItem()
{
    data = 0;
    _filename = 0;
    _dataOffset = 0;
    _unpackedSize = 0;
    _packedSize = 0;
    _packed = false;
}

DatFileItem::~DatFileItem()
{
    delete [] data;
    delete [] _filename;
}

/**
 * Sets filename with path
 * @brief DatFileItem::setFilename
 * @param filename
 */
void DatFileItem::setFilename(char * filename)
{
    delete [] _filename;
    _filename = new char[strlen(filename) + 1]();
    strcpy(_filename,filename);
}

/**
 * Returns filename with path
 * @brief DatFileItem::getFilename
 */
char * DatFileItem::getFilename()
{
    return _filename;
}


}
