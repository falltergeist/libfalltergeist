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

#ifndef LIBFALLTERGEIST_INI_FILE_H
#define	LIBFALLTERGEIST_INI_FILE_H

// C++ standard includes
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <algorithm>

// Libfalltergeist includes
#include "../Ini/Parser.h"
#include "../Ini/Section.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

/**
 * @brief A regular INI file.
 */
class File
{
public:
    using SectionMap = std::map<std::string, Section>;
    using iterator = SectionMap::iterator;
    using const_iterator = SectionMap::const_iterator;

    File();
    ~File();

    /**
     * Returns reference to section with given name. If it's not exist, empty section will be created automatically.
     */
    Section& section(const std::string &name);
    /**
     * An alias for section()
     */
    Section& operator [] (const std::string &name);

    const SectionMap& sections();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    bool hasSection(const std::string &name) const;

private:
    SectionMap _sections;

};

}
}
#endif	// LIBFALLTERGEIST_INI_FILE_H
