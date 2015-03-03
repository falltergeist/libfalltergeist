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

// libfalltergeist includes
#include "../Pal/Color.h"
#include "../Pal/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Pal
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    for (auto color : _colors)
    {
        delete color;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(3);

    _colors.push_back(new Color(0, 0, 0, 0)); // zero color (transparent)

    for (unsigned i = 1; i != 256; ++i)
    {
        _colors.push_back(new Color(uint8(), uint8(), uint8()));
    }
}

std::vector<Color*>* File::colors()
{
    return &_colors;
}

Color* File::color(unsigned index) const
{
    return _colors.at(index);
}

}
}
