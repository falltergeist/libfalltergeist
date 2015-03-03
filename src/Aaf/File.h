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

#ifndef LIBFALLTERGEIST_AAF_FILE_H
#define LIBFALLTERGEIST_AAF_FILE_H

// C++ standard includes
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Aaf
{

class Glyph;

class File : public Dat::Item
{

public:
    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    ~File();

    uint32_t* rgba();

    std::vector<Glyph*>* glyphs();

    uint16_t maximumHeight() const;
    uint16_t maximumWidth() const;
    uint16_t horizontalGap() const;
    uint16_t verticalGap() const;
    uint16_t spaceWidth() const;

protected:
    std::vector<Glyph*> _glyphs;
    uint32_t _signature;
    uint16_t _maximumHeight = 0;
    uint16_t _maximumWidth = 0;
    uint16_t _horizontalGap = 0;
    uint16_t _spaceWidth = 0;
    uint16_t _verticalGap = 0;
    uint32_t* _rgba = 0;
    virtual void _initialize();

};

}
}
#endif // LIBFALLTERGEIST_AAF_FILE_H
