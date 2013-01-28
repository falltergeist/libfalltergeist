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

#include "../src/MsgMessage.h"
#include <cstring>

namespace libfalltergeist
{

MsgMessage::MsgMessage()
{
    _number = 0;
    _sound = 0;
    _text = 0;
}

MsgMessage::~MsgMessage()
{
    delete [] _sound;
    delete [] _text;
}

void MsgMessage::setNumber(unsigned int number)
{
    _number = number;
}

unsigned int MsgMessage::number()
{
    return _number;
}

void MsgMessage::setSound(const char * sound)
{
    delete [] _sound;
    _sound = new char[strlen(sound) + 1]();
    strcpy(_sound, sound);
}

const char * MsgMessage::sound()
{
    return _sound;
}

void MsgMessage::setText(const char * text)
{
    delete [] _text;
    _text = new char[strlen(text)+1]();
    strcpy(_text, text);
}

const char * MsgMessage::text()
{
    return _text;
}

}
