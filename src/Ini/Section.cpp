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
#include "../Ini/Section.h"

// C++ standard includes
#include <algorithm>
#include <functional>

// Libfalltergeist includes
#include "../Exception.h"

// Third party includes


namespace libfalltergeist
{
namespace Ini
{

Section::Section(const std::string &name) : _name(name)
{
}

Section::~Section()
{
}

std::string Section::name()
{
    return _name;
}

Section::PropertyMap& Section::properties()
{
    return _properties;
}

bool Section::hasProperty(const std::string &name) const
{
    return _properties.find(name) != _properties.end();
}

const Value& Section::property(const std::string& name) const
{
    return _properties.at(name);
}

Value& Section::operator [] (const std::string& name)
{
    return _properties[name];
}

void Section::setProperty(const std::string& name, const Value& value)
{
    _properties[name] = value;
}

const std::string& Section::propertyString(const std::string &name, const std::string &def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.str();
}

int Section::propertyInt(const std::string &name, int def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toInt();
}

double Section::propertyDouble(const std::string &name, double def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toDouble();
}

bool Section::propertyBool(const std::string &name, bool def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toBool();
}

Array Section::propertyArray(const std::string& name) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter != _properties.end())
    {
        return iter->second.toArray();
    }
    return Array();
}

Section::PropertyRefs Section::listByMask(const std::string& mask, unsigned int start) const
{
    PropertyRefs vec;
    int i = start;
    char key[100];
    sprintf_s(key, 100, mask.c_str(), i);
    while (hasProperty(key))
    {
        vec.push_back(std::cref(property(key)));
        sprintf_s(key, 100, mask.c_str(), ++i);
    }
    return vec;
}

Section::iterator Section::begin()
{
    return _properties.begin();
}

Section::const_iterator Section::begin() const
{
    return _properties.begin();
}

Section::iterator Section::end()
{
    return _properties.end();
}

Section::const_iterator Section::end() const
{
    return _properties.end();
}

}
}
