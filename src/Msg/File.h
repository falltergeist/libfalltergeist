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

#ifndef LIBFALLTERGEIST_MSG_FILE_H
#define LIBFALLTERGEIST_MSG_FILE_H

// C++ standard includes
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Msg
{

class Message;

class File : public Dat::Item
{

public:
    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    ~File();

    std::vector<Message*>* messages();
    Message* message(unsigned int number);

protected:
    std::vector<Message*> _messages;
    virtual void _initialize();

};

}
}
#endif // LIBFALLTERGEIST_MSG_FILE_H
