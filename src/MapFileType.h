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

#ifndef LIBFALLTERGEIST_MAPFILETYPE_H
#define LIBFALLTERGEIST_MAPFILETYPE_H

// C++ standard includes
#include <string>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{

class DatFileItem;
class MapElevation;
class ProFileType;
class MapObject;

typedef ProFileType * (*ProFileTypeLoaderCallback)(unsigned int);

class MapFileType
{
protected:
    ProFileTypeLoaderCallback _proFileTypeLoaderCallback;

    DatFileItem * _datFileItem;
    std::vector<MapElevation *> * _elevations;
    unsigned int _version;
    std::string _name;
    unsigned int _defaultPosition;
    unsigned int _defaultElevation;
    unsigned int _defaultOrientaion;
    unsigned int _localVarsNumber;
    unsigned int _globalVarsNumber;
    unsigned int _elevationsFlag;
    unsigned int _mapId;
    unsigned int _timeTicks;

    int _scriptId;

    MapObject * _readObject();

public:
    MapFileType(DatFileItem * datFileItem, ProFileTypeLoaderCallback callback);
    ~MapFileType();

    void open();

    DatFileItem * datFileItem();
    std::vector<MapElevation *> * elevations();
    unsigned int defaultPosition();
    unsigned int defaultElevation();
    unsigned int defaultOrientation();
};


}

#endif // LIBFALLTERGEIST_MAPFILETYPE_H
