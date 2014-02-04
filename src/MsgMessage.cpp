/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// libfalltergeist includes
#include "../src/MsgMessage.h"

// Third party includes

namespace libfalltergeist
{

MsgMessage::MsgMessage()
{
}

MsgMessage::~MsgMessage()
{
}

void MsgMessage::setNumber(unsigned int number)
{
    _number = number;
}

unsigned int MsgMessage::number()
{
    return _number;
}

void MsgMessage::setSound(std::string sound)
{
    _sound = sound;
}

std::string MsgMessage::sound()
{
    return _sound;
}

void MsgMessage::setText(std::string text)
{
    _text = text;
}

std::string MsgMessage::text()
{
    return _text;
}

std::string* MsgMessage::textPointer()
{
    return &_text;
}

MsgMessage::operator std::string ()
{
    return _text;
}

}
