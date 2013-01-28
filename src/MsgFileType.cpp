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

#include "../src/MsgFileType.h"
#include "../src/DatFileItem.h"
#include "../src/MsgMessage.h"
#include <string>
#include <cstdlib>

namespace libfalltergeist
{

MsgFileType::MsgFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _messages = 0;
    open();
}

MsgFileType::~MsgFileType()
{
    delete _messages;
}

void MsgFileType::open()
{
    _messages = new std::vector<MsgMessage *>;

    datFileItem()->setPosition(0);

    unsigned int i = 0;
    unsigned char chr;
    while (i < datFileItem()->size())
    {
        chr = datFileItem()->readUint8();
        // = 0;
        std::string line = "";
        while (chr != 0x0D)
        {
            chr = datFileItem()->readUint8();
            if (chr != 0x0D && chr != 0x0A) line.push_back(chr);
            i++;
        }
        // \r\n
        i++;
        if (line.c_str()[0] == '{')
        {
            std::string code = "";
            std::string sound = "";
            std::string text = "";

            const char * data = line.c_str();
            unsigned int j = 1;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                code.push_back(data[j]);
                j++;
            }
            j++; j++;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                sound.push_back(data[j]);
                j++;
            }
            j++; j++;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                text.push_back(data[j]);
                j++;
            }

            MsgMessage * message = new MsgMessage();
            message->setNumber(atoi(code.c_str()));
            message->setSound(sound.c_str());
            message->setText(text.c_str());

            _messages->push_back(message);
        }
    }

}

DatFileItem * MsgFileType::datFileItem()
{
    return _datFileItem;
}

std::vector<MsgMessage *> * MsgFileType::messages()
{
    return _messages;
}

}
