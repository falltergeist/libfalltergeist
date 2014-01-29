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

#ifndef LIBFALLTERGEIST_RIXFILETYPE_H
#define	LIBFALLTERGEIST_RIXFILETYPE_H

// C++ standard includes

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{
    
class RixFileType : public DatFileItem
{
protected:
    std::string _signature = "????";
    unsigned short _width,
                   _height,
                   _unknown1;
    std::vector<unsigned int> _palette;
    std::vector<unsigned char> _data;
    virtual void _initialize();
    unsigned int* _rgba = 0;
public:
    RixFileType(DatFileEntry* datFileEntry);
    RixFileType(std::ifstream* stream);
    virtual ~RixFileType();
    unsigned short width();
    void setWidth(unsigned short value);
    unsigned short height();
    void setHeight(unsigned short value);
    std::vector<unsigned int>* palette();
    std::vector<unsigned char>* data();
    unsigned int* rgba();
};

}
#endif	/* LIBFALLTERGEIST_RIXFILETYPE_H */

