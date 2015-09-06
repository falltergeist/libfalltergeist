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

#ifndef LIBFALLTERGEIST_INI_VALUE_H
#define LIBFALLTERGEIST_INI_VALUE_H

// C++ standard includes
#include <ostream>
#include <string>

// Libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

class Value;

typedef std::vector<std::pair<std::string, Value>> Array;

/**
 * @brief A value in INI file.
 * A wrapper for std::string with conversion functions to various types.
 */
class Value
{
public:
    Value(const std::string &value = "");

    void operator =(const std::string&);

    /*template <class T>
    explicit operator T() const;*/

    operator std::string() const;

    const std::string& str() const;

    int toInt() const;

    double toDouble() const;

    bool toBool() const;

    Array toArray() const;


private:
    std::string _value;

};

inline std::ostream& operator <<(std::ostream& stream, const Value& value)
{
    stream << value.str();
    return stream;
}

}
}
#endif // LIBFALLTERGEIST_INI_VALUE_H
