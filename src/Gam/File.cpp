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
#include <vector>
#include <algorithm>

// libfalltergeist includes
#include "../Gam/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Gam
{

File::File(std::shared_ptr<Dat::Entry> datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    unsigned int i = 0;
    unsigned char ch;
    std::string line;
    while (i != this->size())
    {
        *this >> ch; i++;
        if (ch != 0x0D) // \r
        {
            line += ch;
        }
        else
        {
            this->skipBytes(1); i++;// 0x0A \n
            _parseLine(line);
            line.clear();
        }
    }
    if (line.length() != 0)
    {
        _parseLine(line);
    }

}

void File::_parseLine(std::string line)
{
    // отрезаем всё что после комментариев
    if(line.find("//") != std::string::npos)
    {
        line = line.substr(0, line.find("//"));
    }

    // rtrim
    line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());

    if (line.length() == 0) return;

    if (line == "GAME_GLOBAL_VARS:")
    {
        _GVARmode = true;
        return;
    }
    if (line == "MAP_GLOBAL_VARS:")
    {
        _MVARmode = true;
        return;
    }

    std::string name = line.substr(0, line.find(":="));
    std::string value = line.substr(line.find(":=")+2,line.find(";")-line.find(":=")-2);
    // rtrim
    name.erase(std::find_if(name.rbegin(), name.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), name.end());

    if (_GVARmode)
    {
        _GVARS.insert(std::make_pair(name, std::stoi(value)));
        return;
    }
    else if(_MVARmode)
    {
        _MVARS.insert(std::make_pair(name, std::stoi(value)));
        return;
    }
    else
    {
        throw Exception("File::_initialize() - unknown mode");
    }
}

std::map<std::string, int>* File::GVARS()
{
    _initialize();
    return &_GVARS;
}

std::map<std::string, int>* File::MVARS()
{
    _initialize();
    return &_MVARS;
}

int File::GVAR(std::string name)
{
    if (_GVARS.find(name) != _GVARS.end())
    {
        return _GVARS.at(name);
    }
    throw Exception("File::GVAR(name) - GVAR not found:" + name);
}

int File::MVAR(std::string name)
{
    if (_MVARS.find(name) != _MVARS.end())
    {
        return _MVARS.at(name);
    }
    throw Exception("File::MVAR(name) - MVAR not found:" + name);
}

int File::GVAR(unsigned int number)
{
    unsigned int i = 0;
    for (auto gvar : _GVARS)
    {
        if (i == number) return gvar.second;
        i++;
    }
    throw Exception("File::GVAR(number) - not found: " + std::to_string(number));
}

int File::MVAR(unsigned int number)
{
    unsigned int i = 0;
    for (auto mvar : _MVARS)
    {
        if (i == number) return mvar.second;
        i++;
    }
    throw Exception("File::MVAR(number) - not found: " + std::to_string(number));
}

}
}
