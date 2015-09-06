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
#include "../Ini/Value.h"

// C++ standard includes
#include <sstream>
#include <algorithm>

// Libfalltergeist includes
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

Value::Value(const std::string& value) : _value(value)
{
}

void Value::operator =(const std::string& value)
{
    _value = value;
}

Value::operator std::string() const
{
    return _value;
}

const std::string& Value::str() const
{
    return _value;
}

/*template<class T>
explicit Value::operator T() const
{
    T ret;
    std::istringstream stream(_value);
    stream >> ret;
    return ret;
}*/

int Value::toInt() const
{
    try
    {
        return std::stoi(_value);
    }
    catch (std::invalid_argument)
    {
        return 0;
    }
}

double Value::toDouble() const
{
    try
    {
        return std::stod(_value);
    }
    catch (std::invalid_argument)
    {
        return 0.0;
    }
}

bool Value::toBool() const
{
    std::string lc = _value;
    Parser::toLower(lc);
    return (lc == "on" || lc == "true");
}

Array Value::toArray() const
{
    return Parser::parseArray(_value);
}

}
}
