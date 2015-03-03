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

// C++ standard includes
#include <algorithm>

// libfalltergeist includes
#include "../Lst/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Lst
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::string line;
    unsigned char ch;
    for(unsigned int i = 0; i != this->size(); ++i)
    {
        *this >> ch;
        if (ch == 0x0D) // \r
        {
            // do nothing
        }
        else if (ch == 0x0A) // \n
        {
            _addString(line);
            line.clear();
        }
        else
        {
            line += ch;
        }
    }
    if (line.size() != 0)
    {
        _addString(line);
    }
}

void File::_addString(std::string line)
{
    // strip comments
    if (auto pos = line.find(";")) line = line.substr(0, pos);

    // rtrim
    line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());

    // replace slashes
    std::replace(line.begin(),line.end(),'\\','/');

    // to lower
    std::transform(line.begin(),line.end(),line.begin(), ::tolower);

    _strings.push_back(line);
}

std::vector<std::string>* File::strings()
{
    _initialize();
    return &_strings;
}

}
}
