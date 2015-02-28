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
    Dat::Item::setPosition(3);

    _colors.push_back(new Color(0, 0, 0, 0)); // zero color (transparent)

    for (unsigned int i = 1; i != 256; ++i)
    {
        unsigned char r, g, b;
        *this >> r >> g >> b;
        _colors.push_back(new Color(r, g, b));
    }
}

std::vector<Color*>* File::colors()
{
    _initialize();
    return &_colors;
}

Color* File::color(unsigned char index)
{
    _initialize();
    return _colors.at(index);
}

}
}
