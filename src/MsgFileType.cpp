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

namespace libfalltergeist
{

MsgFileType::MsgFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    open();
}

MsgFileType::~MsgFileType()
{

}

void MsgFileType::open()
{

}

/**
 * Alias to MsgFileType::getDatFileItem
 * @brief MsgFileType::datFileItem
 * @return
 */
DatFileItem * MsgFileType::datFileItem()
{
    return getDatFileItem();
}

DatFileItem * MsgFileType::getDatFileItem()
{
    return _datFileItem;
}

}
