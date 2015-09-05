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

#ifndef LIBFALLTERGEIST_TXT_CITYFILE_H
#define LIBFALLTERGEIST_TXT_CITYFILE_H

// C++ standard includes
#include <vector>

// Libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

/**
 * @brief City entrance information.
 */
struct CityEntrance
{
    /**
     * Start state of entrance (visible or not)
     */
    bool startState;
    /**
     * X coordinate on town map
     */
    int townMapX;
    /**
     * Y coordinate on town map
     */
    int townMapY;
    /**
     * Name of associated map
     */
    std::string mapName;
    /**
     * Starting elevation
     */
    int elevation;
    /**
     * Starting tile number
     */
    int tileNum;
    /**
     * Starting orientation
     */
    int orientation;
};

/**
 * @brief City information.
 */
struct City
{
    enum class Size
    {
        Small = 1, Medium, Large
    };

    std::string name;
    int worldX = 0;
    int worldY = 0;
    bool startState;
    Size size;

    int townMapArtIdx;
    int townMapLabelArtIdx;

    std::vector<CityEntrance> entrances;
};

/**
 * @brief CITY.TXT
 */
class CityFile : public Dat::Item
{
public:
    CityFile(std::ifstream* stream);
    CityFile(Dat::Entry* datFileEntry);

    const std::vector<City>& cities() const;

protected:
    std::vector<City> _cities;

    void _initialize() override;
    City::Size _sizeByName(std::string name) const;
};

}
}




#endif //LIBFALLTERGEIST_TXT_CITYFILE_H
