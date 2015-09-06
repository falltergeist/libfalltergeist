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

#ifndef LIBFALLTERGEIST_INI_PARSER_H
#define LIBFALLTERGEIST_INI_PARSER_H

// C++ standard includes
#include <memory>
#include <string>
#include <vector>

// Libfalltergeist includes
#include "../Ini/Value.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

class File;
class Value;

/**
 * @brief Parser of INI files.
 * Parses INI-like TXT files, such as MAPS.TXT, CITY.TXT, etc.
 */
class Parser
{
public:
    Parser(std::istream &stream);
    ~Parser();

    std::unique_ptr<File> parse();

    static std::vector<std::string> split(char delim, const std::string& source);

    static void trim(std::string& value);

    static void rtrim(std::string& value);

    static void ltrim(std::string& value);

    static void toLower(std::string& value);

    static Array parseArray(const std::string& value);

private:
    std::istream &_stream; // stream to parse
    std::string  _section; // current section

protected:

    void _stripComments(std::string& line);

};

}
}
#endif // LIBFALLTERGEIST_INI_PARSER_H
