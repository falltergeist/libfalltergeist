/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// C++ standard includes
#include <string>
#include <cstdlib>

// libfalltergeist includes
#include "../src/MsgFileType.h"
#include "../src/DatFileEntry.h"
#include "../src/MsgMessage.h"

// Third party includes

namespace libfalltergeist
{

MsgFileType::MsgFileType(DatFileEntry * datFileEntry) : DatFileItem(datFileEntry)
{
    _messages = 0;
}

MsgFileType::MsgFileType(std::ifstream * stream) : DatFileItem(stream)
{
    _messages = 0;
}

MsgFileType::~MsgFileType()
{
    if (_messages != 0)
    {
        while(!_messages->empty())
        {
            delete _messages->back();
            _messages->pop_back();
        }
        delete _messages;
    }
}

void MsgFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    _messages = new std::vector<MsgMessage *>;

    unsigned int i = 0;
    unsigned char chr = 0;
    while (chr != '{' && i < this->size())
    {
        *this >> chr;
        i++;
        if (chr == '{')
        {
            std::string number = "";
            std::string sound = "";
            std::string text = "";

            // number
            while (chr != '}')
            {
                *this >> chr;
                i++;
                if (chr != '}') number += chr;
            }

            // sound
            while (chr != '{')
            {
                *this >> chr;
                i++;
            }

            while (chr != '}')
            {
                *this >> chr;
                i++;
                if (chr != '}') sound += chr;
            }

            // text
            while (chr != '{')
            {
                *this >> chr;
                i++;
            }

            while (chr != '}')
            {
                *this >> chr;
                i++;
                if (chr != '}') text += chr;
            }

            MsgMessage * message = new MsgMessage();
            message->setNumber(atoi(number.c_str()));
            message->setSound(sound);
            message->setText(text);
            _messages->push_back(message);
        }
    }
}

std::vector<MsgMessage *> * MsgFileType::messages()
{
    _initialize();
    return _messages;
}

MsgMessage * MsgFileType::message(unsigned int number)
{
    _initialize();
    std::vector<MsgMessage *>::iterator it;
    for (it = this->messages()->begin(); it != this->messages()->end(); ++it)
    {
        if ((*it)->number() == number)
        {
            return *it;
        }
    }
    return 0;
}

}
