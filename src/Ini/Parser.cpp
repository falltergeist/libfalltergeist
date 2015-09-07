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
#include "../Ini/Parser.h"

// C++ standard includes
#include <algorithm>
#include <sstream>

// Libfalltergeist includes
#include "../Ini/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

Parser::Parser(std::istream &stream) : _stream(stream), _section("")
{
}

Parser::~Parser()
{
}

std::vector<std::string> Parser::split(char delim, const std::string& source)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = source.find(delim, start)) != std::string::npos)
    {
        tokens.push_back(source.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(source.substr(start));
    return tokens;
}

void Parser::trim(std::string& line)
{
    ltrim(line);
    rtrim(line);
}

void Parser::rtrim(std::string& line)
{
    line.erase(find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), line.end());
}

void Parser::ltrim(std::string& line)
{
    line.erase(line.begin(), find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
}

void Parser::toLower(std::string& line)
{
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
}

Array Parser::parseArray(const std::string& str)
{
    Array ret;
    for (std::string& value : Parser::split(',', str))
    {
        std::string key = "";
        Parser::trim(value);
        // skip empty values
        if (value.size() == 0)
        {
            continue;
        }
        // check for associative
        size_t colon = value.find(':');
        if (colon != std::string::npos)
        {
            key = value.substr(0, colon);
            Parser::rtrim(key);
            value = value.substr(colon + 1);
            Parser::ltrim(value);
        }
        if (value.size() > 0)
        {
            ret.push_back(std::make_pair(key, value));
        }
    }
    return ret;
}

void Parser::_stripComments(std::string& line)
{
    unsigned pos = line.find(";");
    if (pos != std::string::npos)
    {
        line.erase(pos);
    }
}

std::unique_ptr<File> Parser::parse()
{
    auto ini = std::unique_ptr<File>(new File());
    std::string line;

    while (std::getline(_stream, line))
    {
        // Lines starting with "#" or ";" are treated as comments and ignored
        if (line[0] == '#' || line[0] == ';') continue;

        // Prepare line
        _stripComments(line);
        trim(line);

        // Skip empty lines
        if (line.length() == 0) continue;

        // Found section
        if (*line.begin() == '[' && *line.rbegin() == ']')
        {
            _section = line.substr(1, line.length() - 2);

            continue;
        }

        auto eqPos = line.find('=');
        if (eqPos == std::string::npos)
        {
            continue;
        }

        auto name  = line.substr(0, eqPos);
        auto value = line.substr(eqPos + 1);
        rtrim(name);
        ltrim(value);

        // Property names are case-insensitive
        toLower(name);

        ini->section(_section).setProperty(name, value);
    }

    return ini;
}

}
}
