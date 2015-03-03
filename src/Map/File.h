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

#ifndef LIBFALLTERGEIST_MAP_FILE_H
#define LIBFALLTERGEIST_MAP_FILE_H

// C++ standard includes
#include <string>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Pro
{
    class File;
}
namespace Map
{
class Elevation;
class Object;
class Script;

typedef std::shared_ptr<Pro::File> (*ProFileTypeLoaderCallback)(uint32_t);

class File : public Dat::Item
{

public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();

    File* setCallback(ProFileTypeLoaderCallback callback);
    ProFileTypeLoaderCallback callback() const;

    std::vector<Elevation*>* elevations();
    std::vector<Script*>* scripts();
    std::vector<int32_t>* LVARS();
    std::vector<int32_t>* MVARS();

    uint32_t defaultPosition() const;
    uint32_t defaultElevation() const;
    uint32_t defaultOrientation() const;
    uint32_t elevationFlags() const;
    uint32_t mapId() const;
    uint32_t version() const;
    uint32_t timeSinceEpoch() const;

    int32_t scriptId() const;
    int32_t unknown1() const;

    std::string name() const;

protected:
    ProFileTypeLoaderCallback _proFileTypeLoaderCallback = 0;

    std::vector<Elevation*> _elevations;
    std::vector<Script*> _scripts;
    std::vector<int32_t> _MVARS;
    std::vector<int32_t> _LVARS;

    uint32_t _version = 0;
    uint32_t _defaultPosition = 0;
    uint32_t _defaultElevation = 0;
    uint32_t _defaultOrientaion = 0;
    uint32_t _MVARsize = 0;
    uint32_t _LVARsize = 0;
    uint32_t _elevationFlags = 0;
    uint32_t _mapId = 0;
    uint32_t _timeSinceEpoch = 0;

    int32_t _unknown1 = 1;
    int32_t _scriptId = -1;

    std::string _name;

    Object* _readObject();
    virtual void _initialize();


};


}
}
#endif // LIBFALLTERGEIST_MAP_FILE_H
