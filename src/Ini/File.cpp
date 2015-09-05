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

// Related headers
#include "../Ini/File.h"

// C++ standard includes
#include <algorithm>

// Libfalltergeist includes
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

File::File()
{
}

File::~File()
{
}

Section& File::section(const std::string &name)
{
    auto it = _sections.find(name);
    if (it == _sections.end())
    {
        _sections[name] = std::move(Section(name));
        return _sections.at(name);
    }
    return it->second;
}

Section& File::operator [] (const std::string &name)
{
    return section(name);
}

bool File::hasSection(const std::string &name) const
{
    return _sections.find(name) != _sections.end();
}

const File::SectionMap& File::sections()
{
    return _sections;
}

File::iterator File::begin()
{
    return _sections.begin();
}

File::const_iterator File::begin() const
{
    return _sections.begin();
}

File::iterator File::end()
{
    return _sections.end();
}

File::const_iterator File::end() const
{
    return _sections.end();
}

}
}
