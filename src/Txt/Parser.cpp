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
#include "../Txt/Parser.h"

// C++ standard includes
#include <algorithm>
#include <functional>

// Libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Txt
{


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

}
}
