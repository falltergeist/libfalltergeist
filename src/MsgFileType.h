// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for libfalltergeist. All credit goes to the original authors.

#ifndef LIBFALLTERGEIST_MSGFILETYPE_H
#define LIBFALLTERGEIST_MSGFILETYPE_H

// C++ standard includes
#include <vector>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{
class MsgMessage;

class MsgFileType : public DatFileItem
{
protected:
    std::vector<std::shared_ptr<MsgMessage>> _messages;
    virtual void _initialize();
public:
    MsgFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    MsgFileType(std::ifstream* stream);
    ~MsgFileType();

    std::vector<std::shared_ptr<MsgMessage>>* messages();

    std::shared_ptr<MsgMessage> message(unsigned int number);

};

}
#endif // LIBFALLTERGEIST_MSGFILETYPE_H
