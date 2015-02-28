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
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    unsigned int i = 0;
    unsigned char chr = 0;
    while (chr != '{' && i < this->size())
    {
        *this >> chr;
        i++;
        if (chr == '{')
        {
            std::string number;
            std::string sound;
            std::string text;

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

            while (text.find("\n") != std::string::npos)
            {
                text.replace(text.find("\n"), 1, "");
            }

            auto message = std::shared_ptr<Message>(new Message());
            message->setNumber(std::stoi(number));
            message->setSound(sound);
            message->setText(text);
            _messages.push_back(message);
        }
    }
}

std::vector<std::shared_ptr<Message>>* File::messages()
{
    _initialize();
    return &_messages;
}

std::shared_ptr<Message> File::message(unsigned int number)
{
    _initialize();
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
