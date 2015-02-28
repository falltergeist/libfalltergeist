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

#ifndef LIBFALLTERGEIST_LIP_FILE_H
#define LIBFALLTERGEIST_LIP_FILE_H

// C++ standard includes
#include <string>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Lip
{

class File : public Dat::Item
{
protected:
    virtual void _initialize();
public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();
    void init();
    std::string acmName();
    uint32_t pcount();
    uint32_t mcount();
    uint32_t acmSize();
    std::vector<uint32_t>* timestamps();
private:
    uint32_t _version;
    uint32_t _unknown1;
    uint32_t _unknown2;
    uint32_t _unknown3;
    uint32_t _acm_size;
    uint32_t _phonems_count;
    uint32_t _unknown4;
    uint32_t _markers_count;
    char  _acm_name[8];
    char  _unknown5[4];
    std::vector<uint8_t> _phonems;
    std::vector<uint32_t> _marker_samples;
    std::vector<uint32_t> _marker_timestamps;

};

}
}
#endif // LIBFALLTERGEIST_LIP_FILE_H
