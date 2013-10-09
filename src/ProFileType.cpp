#include "../src/ProFileType.h"
#include "../src/DatFileItem.h"

namespace libfalltergeist
{

ProFileType::ProFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    open();
}

ProFileType::~ProFileType()
{
}


DatFileItem * ProFileType::datFileItem()
{
    return _datFileItem;
}

void ProFileType::open()
{
    datFileItem()->setPosition(0);

    _objectTypeId = datFileItem()->readUint8();
    datFileItem()->skipBytes(1);
    _objectId = datFileItem()->readUint16();


}

}
