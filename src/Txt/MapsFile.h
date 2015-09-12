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

#ifndef LIBFALLTERGEIST_TXT_MAPSFILE_H
#define LIBFALLTERGEIST_TXT_MAPSFILE_H

// C++ standard includes
#include <vector>

// Libfalltergeist includes
#include "../Txt/BaseFile.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

struct MapStartPoint
{
    int elevation = 0;
    int tileNum = 0;
};

/**
 * @brief Map information.
 */
struct Map
{
    static const char NUM_ELEVATIONS = 3;

    std::string name;
    std::string lookupName;
    std::string music;
    /**
     * Keys are sfx names, value - probability in %. Probabilities *should* sum up to 100.
     */
    std::map<std::string, unsigned char> ambientSfx;
    bool deadBodiesAge;
    /**
     * Flag for each elevation.
     */
    bool canRestHere[NUM_ELEVATIONS] = {true, true, true};
    bool saved;

    std::vector<MapStartPoint> randomStartPoints;
};

/**
 * @brief CITY.TXT
 */
class MapsFile : public BaseFile
{
public:
    MapsFile(std::ifstream* stream);
    MapsFile(Dat::Entry* datFileEntry);

    const std::vector<Map>& maps() const;

protected:
    std::vector<Map> _maps;

    virtual void _parseText(std::istream& istr) override;
};

}
}




#endif //LIBFALLTERGEIST_TXT_MAPSFILE_H
