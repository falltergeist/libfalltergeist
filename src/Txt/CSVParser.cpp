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
#include "CSVParser.h"

// C++ standard includes
#include <algorithm>
#include <sstream>

// Libfalltergeist includes
#include "../Txt/CSVParser.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

CSVParser::CSVParser(std::istream &stream) : _stream(stream)
{
}

CSVParser::~CSVParser()
{
}


void CSVParser::_stripComments(std::string& line)
{
    unsigned pos = line.find(";"), pos2 = line.find("#");
    if (pos != std::string::npos)
    {
        if (pos2 != std::string::npos)
        {
            line.erase(std::min(pos, pos2));
        }
        else
        {
            line.erase(pos);
        }
    }
    else if (pos2 != std::string::npos)
    {
        line.erase(pos2);
    }
}

std::unique_ptr<CSVFile> CSVParser::parse()
{
    auto csv = std::unique_ptr<CSVFile>(new CSVFile());
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

        std::vector<Ini::Value> values;
        auto splitLine = split(',', line);

        // trim and copy values
        for (auto& val : splitLine)
        {
            trim(val);
            values.push_back(val);
        }

        csv->push_back(std::move(values));
    }

    return csv;
}

}
}
