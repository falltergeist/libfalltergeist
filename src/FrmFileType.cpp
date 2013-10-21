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
#include <iostream>

// libfalltergeist includes
#include "../src/FrmFileType.h"
#include "../src/DatFileItem.h"
#include "../src/FrmDirection.h"
#include "../src/FrmFrame.h"

// Third party includes

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
    DatFileItem &item = * datFileItem();
    // initialization
    //item.setPosition(0);

    item.pubseekpos(0);

    // Frm file version
    item >> _version;

    // Frames per second rate
    item >> _framesPerSecond;

    // Frame number on which action is occurs
    item >> _actionFrame;

    // Frames per one direction
    item >> _framesPerDirection;



    // directions data...

    // X shift
    unsigned short shift;
    FrmDirection * direction;

    for (unsigned int i = 0; i != 6; ++i)
    {
        direction = new FrmDirection();
        item >> shift;
        direction->setShiftX(shift);
        directions()->push_back(direction);
    }

    // Y shift
    for (unsigned int i = 0; i != 6; ++i)
    {
        item >> shift;
        directions()->at(i)->setShiftY(shift);
    }

    // Data offset
    for (unsigned int i = 0; i != 6; ++i)
    {
        unsigned int offset;
        item >> offset;
        directions()->at(i)->setDataOffset(offset);
    }

    // for each direction
    for (unsigned int i = 0; i!= 6; ++i)
    {
        // jump to frames data at frames area
        item.setPosition(directions()->at(i)->dataOffset() + 62);

        // read all frames
        for (unsigned int j = 0; j != _framesPerDirection; ++j)
        {
            FrmFrame * frame = new FrmFrame();

            unsigned short width, height;

            item >> width >> height;

            // Frame width
            frame->setWidth(width);

            // Frame height
            frame->setHeight(height);

            //Number of pixels for this frame

            unsigned int dataSize;
            item >> dataSize;

            short offsetX, offsetY;
            item >> offsetX >> offsetY;

            // X offset
            frame->setOffsetX(offsetX);

            // Y offset
            frame->setOffsetY(offsetY);


            for (unsigned int n = 0; n != dataSize; ++n)
            {
                // Pixel color index
                unsigned char color;
                item >> color;
                frame->colorIndexes()->push_back(color);
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
