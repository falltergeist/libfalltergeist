/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBFALLTERGEIST_MSG_MESSAGE_H
#define LIBFALLTERGEIST_MSG_MESSAGE_H

// C++ standard includes
#include <string>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Msg
{

class Message
{

public:
    Message();
    ~Message();

    void setNumber(unsigned int number);
    unsigned int number();

    void setSound(std::string sound);
    std::string sound();

    void setText(std::string text);
    std::string text();
    std::string* textPointer();

    operator std::string();

protected:
    unsigned int _number = 0;
    std::string _sound;
    std::string _text;

};

}
}
#endif // LIBFALLTERGEIST_MSG_MESSAGE_H
