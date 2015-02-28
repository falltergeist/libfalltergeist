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

#ifndef LIBFALLTERGEIST_MAP_ELEVATION_H
#define LIBFALLTERGEIST_MAP_ELEVATION_H

// C++ standard includes
#include <vector>
#include <memory>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Map
{
class Object;

class Elevation
{
protected:
    std::vector<unsigned short> _floorTiles;
    std::vector<unsigned short> _roofTiles;
    std::vector<std::shared_ptr<Object>> _objects;
public:
    std::vector<std::shared_ptr<Object>>* objects();
    std::vector<unsigned short>* floorTiles();
    std::vector<unsigned short>* roofTiles();
    Elevation();
    ~Elevation();
};

}
}
#endif // LIBFALLTERGEIST_MAP_ELEVATION_H
