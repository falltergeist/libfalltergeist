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

#include "../src/FrmFileType.h"
#include "../src/DatFileItem.h"
#include "../src/FrmDirection.h"

namespace libfalltergeist
{

FrmFileType::FrmFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _directions = 0;
}

FrmFileType::~FrmFileType()
{
    delete _directions;
}

void FrmFileType::open()
{
    // initialization
    _datFileItem->setPosition(0);
    _version = _datFileItem->readUint32();
    _framesPerSecond = _datFileItem->readUint16();
    _actionFrame = _datFileItem->readUint16();
    _framesPerDirection = _datFileItem->readUint16();

    _directions = new std::vector<FrmDirection *>;
    for (unsigned int i = 0; i != 6; ++i)
    {
        FrmDirection * direction = new FrmDirection();
        direction->setShiftX(_datFileItem->readUint16());
        _directions->push_back(direction);
    }

    for (unsigned int i = 0; i != 6; ++i)
    {
        _directions->at(i)->setShiftY(_datFileItem->readInt16());
    }

    for (unsigned int i = 0; i != 6; ++i)
    {
        _directions->at(i)->setDataOffset(_datFileItem->readInt32());
    }
    // size of frame area
    _datFileItem->skipBytes(4);

}

}
