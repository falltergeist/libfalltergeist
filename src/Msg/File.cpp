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

// C++ standard includes
#include <string>
#include <cstdlib>

// libfalltergeist includes
#include "../Msg/File.h"
#include "../Msg/Message.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Msg
{

File::File(std::shared_ptr<Dat::Entry> datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    for (auto message : _messages)
    {
        delete message;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    /*
     * Because of bug in CMBATAI2.MSG in messages #1382 and #32020 we need to explode each line with '{' symbol
     * Any extra '}' symbols must be trimed from exploded parts
     */

    while (this->position() < this->size())
    {
        uint8_t chr = uint8();
        if (chr == '{')
        {
            std::string number;
            std::string sound;
            std::string text;
            chr = 0;
            // number
            while (chr != '{')
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    number += chr;
                }
            }

            // sound
            chr = 0;
            while (chr != '{')
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    sound += chr;
                }
            }

            chr = 0;
            // text
            while (chr != '}' && chr != '{' && this->position() < this->size())
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    text += chr;
                }
            }

            // "put back" last character
            this->setPosition(this->position() - 1);

            while (text.find("\n") != std::string::npos)
            {
                text.replace(text.find("\n"), 1, "");
            }

            auto message = new Message();
            message->setNumber(std::stoi(number));
            message->setSound(sound);
            message->setText(text);
            _messages.push_back(message);
        }
    }
}

std::vector<Message*>* File::messages()
{
    return &_messages;
}

Message* File::message(unsigned int number)
{
    for (auto message : _messages)
    {
        if (message->number() == number)
        {
            return message;
        }
    }
    throw Exception("File::message() - number is out of range: " + std::to_string(number));
}

}
}
