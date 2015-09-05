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

#ifndef LIBFALLTERGEIST_INI_SECTION_H
#define LIBFALLTERGEIST_INI_SECTION_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// Libfalltergeist includes
#include "../Ini/Value.h"

// Third party includes

namespace libfalltergeist
{
namespace Ini
{

typedef std::vector<std::pair<std::string, Value>> Array;

/**
 * @brief A section in INI file.
 * Basically a wrapper for map<string, string> with additional convenience functions.
 */
class Section
{
public:
    using PropertyMap = std::map<std::string, Value>;
    using PropertyMapConstIterator = PropertyMap::const_iterator;
    using iterator = PropertyMap::iterator;
    using const_iterator = PropertyMap::const_iterator;

    Section(const std::string &name = "");
    ~Section();

    PropertyMap& properties();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    std::string name();

    /**
     * Checks if property with given name exists in given section.
     */
    bool hasProperty(const std::string &name) const;

    /**
     * Returns value of property with given name.
     * @throws std::out_of_range if property doesn't exist
     */
    const Value& property(const std::string& name) const;

    /**
     * Returns reference to property with given name. If property doesn't exist, it will be created with empty string value.
     */
    Value& operator [] (const std::string& name);

    /**
     * Sets given value for property with given name
     */
    void setProperty(const std::string &name, const Value& value);

    /**
     * Returns value of property with given name, or a given default value if such property doesn't exist.
     */
    const std::string& propertyString(const std::string& name, const std::string& def = "") const;

    /**
     * Returns value of given property, converted to int.
     */
    int propertyInt(const std::string &name, int def) const;

    /**
     * Returns value of given property, converted to double.
     */
    double propertyDouble(const std::string &name, double def) const;

    /**
     * Returns value of given property, converted to bool.
     */
    bool propertyBool(const std::string &name, bool def) const;

    /**
     * Parse property with given name as array and return it.
     */
    Array propertyArray(const std::string &name) const;

private:

    PropertyMap _properties;
    std::string _name;

    void _trim(std::string& value) const;
};

}
}
#endif // LIBFALLTERGEIST_INI_SECTION_H
