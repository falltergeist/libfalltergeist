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
#include <algorithm>

// libfalltergeist includes
#include "../Lip/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Lip
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
    *this >> _version;
    if (_version != 2)
    {
        throw Exception("Invalid LIP file.");
    }
    *this >> _unknown1 >> _unknown2 >> _unknown3;
    *this >> _acm_size >> _phonems_count;
    *this >> _unknown4;
    *this >> _markers_count;
    this->readBytes(_acm_name, 8);
    this->readBytes(_unknown5, 4);

    for (uint32_t i=0; i < _phonems_count; i++)
    {
        uint8_t phonem;
        *this >> phonem;
        _phonems.push_back(phonem);
    }

    for (uint32_t i=0; i < _markers_count; i++)
    {
        uint32_t stype, smarker;
        *this >> stype >> smarker;
        _marker_samples.push_back(smarker);
        _marker_timestamps.push_back(smarker*1000 / 22050 /2); //ms
    }

}

void File::init()
{
    _initialize();
}

std::string File::acmName()
{
    _initialize();
    return std::string(_acm_name)+std::string(_unknown5);
}

uint32_t File::pcount()
{
    _initialize();
    return _phonems_count;
}

uint32_t File::mcount()
{
    _initialize();
    return _markers_count;
}

uint32_t File::acmSize()
{
    _initialize();
    return _acm_size;
}

std::vector<uint32_t>* File::timestamps()
{
    _initialize();
    return &_marker_timestamps;
}

}
}
