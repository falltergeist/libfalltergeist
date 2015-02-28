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

typedef std::shared_ptr<Pro::File> (*ProFileTypeLoaderCallback)(unsigned int);

class File : public Dat::Item
{
protected:
    ProFileTypeLoaderCallback _proFileTypeLoaderCallback = 0;

    std::vector<std::shared_ptr<Elevation>> _elevations;
    std::vector<std::shared_ptr<Script>> _scripts;
    std::vector<int> _MVARS;
    std::vector<int> _LVARS;
    unsigned int _version;
    std::string _name;
    unsigned int _defaultPosition;
    unsigned int _defaultElevation;
    unsigned int _defaultOrientaion;
    unsigned int _MVARsize;
    unsigned int _LVARsize;
    unsigned int _elevationFlags;
    unsigned int _mapId;
    unsigned int _timeSinceEpoch;
    int _unknown1;

    int _scriptId = -1;

    std::shared_ptr<Object> _readObject();
    virtual void _initialize();


public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();

    File* setCallback(ProFileTypeLoaderCallback callback);
    ProFileTypeLoaderCallback callback();

    unsigned int version();

    std::vector<std::shared_ptr<Elevation>>* elevations();
    std::vector<std::shared_ptr<Script>>* scripts();
    unsigned int defaultPosition();
    unsigned int defaultElevation();
    unsigned int defaultOrientation();
    int scriptId();

    std::string name();

    unsigned int elevationFlags();
    int unknown1();
    unsigned int mapId();
    unsigned int timeSinceEpoch();

    std::vector<int>* LVARS();
    std::vector<int>* MVARS();

};


}
}
#endif // LIBFALLTERGEIST_MAP_FILE_H
