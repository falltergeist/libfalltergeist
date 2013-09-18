#ifndef LIBFALLTERGEIST_EXCEPTION_H
#define LIBFALLTERGEIST_EXCEPTION_H

#include <string>

namespace libfalltergeist
{

class Exception
{
public:
    Exception(std::string message);
    std::string message();
protected:
    std::string _message;
};

}
#endif // LIBFALLTERGEIST_EXCEPTION_H
