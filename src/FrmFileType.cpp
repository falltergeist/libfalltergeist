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
#include "../src/FrmFrame.h"
#include <iostream>

namespace libfalltergeist
{

FrmFileType::FrmFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _directions = 0;
    open();
}

FrmFileType::~FrmFileType()
{
    delete _directions;
}

DatFileItem * FrmFileType::datFileItem()
{
    return _datFileItem;
}

void FrmFileType::open()
{
    // initialization
//!    _datFileItem->setPosition(0);

    // Frm file version
//!    _version = _datFileItem->readUint32();

    // Frames per second rate
//!    _framesPerSecond = _datFileItem->readUint16();

    // Frame number on which action is occurs
//!    _actionFrame = _datFileItem->readUint16();

    // Frames per one direction
//!    _framesPerDirection = _datFileItem->readUint16();

    // directions data...

    // X shift
    for (unsigned int i = 0; i != 6; ++i)
    {
        FrmDirection * direction = new FrmDirection();
//!        direction->setShiftX(_datFileItem->readUint16());
        directions()->push_back(direction);
    }

    // Y shift
    for (unsigned int i = 0; i != 6; ++i)
    {
//!        directions()->at(i)->setShiftY(_datFileItem->readInt16());
    }

    // Data offset
    for (unsigned int i = 0; i != 6; ++i)
    {
//!        directions()->at(i)->setDataOffset(_datFileItem->readUint32());
    }

    // for each direction
    for (unsigned int i = 0; i!= 6; ++i)
    {
        // jump to frames data at frames area
//!        _datFileItem->setPosition(directions()->at(i)->dataOffset() + 62);

        // read all frames
        for (unsigned int j = 0; j != _framesPerDirection; ++j)
        {
            FrmFrame * frame = new FrmFrame();

            // Frame width
//!            frame->setWidth(_datFileItem->readUint16());

            // Frame height
//!            frame->setHeight(_datFileItem->readUint16());

            //Number of pixels for this frame

//!            unsigned int dataSize = _datFileItem->readUint32();

            // X offset
//!            frame->setOffsetX(_datFileItem->readInt16());

            // Y offset
            frame->setOffsetY(_datFileItem->readInt16());

            for (unsigned int n = 0; n != dataSize; ++n)
            {
                // Pixel color index
                frame->colorIndexes()->push_back(_datFileItem->readUint8());
            }
            // Appending frame to direction
            directions()->at(i)->frames()->push_back(frame);
        }

    }

}

unsigned int FrmFileType::version()
{
    return _version;
}

void FrmFileType::setVersion(unsigned int version)
{
    _version = version;
}

unsigned short FrmFileType::framesPerSecond()
{
    return _framesPerSecond;
}

void FrmFileType::setFramesPerSecond(unsigned short fps)
{
    _framesPerSecond = fps;
}

unsigned short FrmFileType::framesPerDirection()
{
    return _framesPerDirection;
}

void FrmFileType::setFramesPerDirection(unsigned short fpd)
{
    _framesPerDirection = fpd;
}

unsigned short FrmFileType::actionFrame()
{
    return _actionFrame;
}

void FrmFileType::setActionFrame(unsigned short number)
{
    _actionFrame = number;
}

std::vector<FrmDirection *> * FrmFileType::directions()
{
    if (_directions != 0) return _directions;
    _directions = new std::vector<FrmDirection *>;
    return _directions;
}

}
