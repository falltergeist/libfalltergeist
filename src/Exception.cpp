#include "Exception.h"

namespace libfalltergeist
{

Exception::Exception(std::string message)
{
    _message = message;
}

std::string Exception::message()
{
    return _message;
}


}
