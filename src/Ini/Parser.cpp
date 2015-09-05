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
        // check for associative
        size_t colon = value.find(':');
        if (colon != std::string::npos)
        {
            key = value.substr(0, colon);
            Parser::rtrim(key);
            value = value.substr(colon + 1);
            Parser::ltrim(value);
        }
        ret.push_back(std::make_pair(key, value));
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

/*+bool Parser::_tryBool(std::string &line, bool *val)
{
    auto maybeBool = line;
    toLower(maybeBool);

    if (maybeBool == "yes")
    {
        *val = true;
        return true;
    }
    else if (maybeBool == "no")
    {
        *val = false;
        return true;
    }
    return false;
}

bool Parser::_parseBool(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    bool value;
    if (_tryBool(line, &value))
    {
        ini->section(_section)->setPropertyBool(name, value);
        return true;
    }
    return false;
}

int Parser::_tryDecimal(std::string &line, int* intval,double* doubleval)
{
    std::istringstream ss(line);
    enum { BEGIN, SIGN, INTEGRAL, DOT, FRACTIONAL, EXP, EXP_SIGN, EXP_DIGITS, ERROR } state = BEGIN;

    for (std::string::const_iterator it = line.begin(); state != ERROR && it != line.end(); ++it)
    {
        char sym = *it;
        switch (state)
        {
            case BEGIN:
                if (sym == '+' || sym == '-')
                {
                    state = SIGN;
                }
                else if (isdigit(sym))
                {
                    state = INTEGRAL;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case SIGN:
                if (isdigit(sym))
                {
                    state = INTEGRAL;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case INTEGRAL:
                if (sym == '.')
                {
                    state = DOT;
                }
                else if (!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case DOT:
                if (isdigit(sym))
                {
                    state = FRACTIONAL;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case FRACTIONAL:
                if (sym == 'e' || sym == 'E')
                {
                    state = EXP;
                }
                else if(!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case EXP:
                if (sym == '+' || sym == '-')
                {
                    state = EXP_SIGN;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case EXP_SIGN:
                if (isdigit(sym))
                {
                    state = EXP_DIGITS;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case EXP_DIGITS:
                if (!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case ERROR:
                // do nothing, just suppress warning
                break;
        }
    }

    if (state == INTEGRAL)
    {
        ss >> *intval;
        return 1;
    }

    if (state == FRACTIONAL || state == EXP || state == EXP_DIGITS)
    {
        ss >> *doubleval;
        return -1;
    }

    return 0;
}


bool Parser::_parseDecimal(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    int intval;
    double doubleval;
    int ret = _tryDecimal(line, &intval, &doubleval);
    if (ret!=0)
    {
        if (ret > 0)
        {
            ini->section(_section)->setPropertyInt(name, intval);
            return  true;
        }

        else if (ret < 0)
        {
            ini->section(_section)->setPropertyDouble(name, doubleval);
            return true;
        }
    }

    return false;
}


bool Parser::_parseArrayBool(std::vector<Value> &vec, std::string val)
{
    bool value;
    if (_tryBool(val,&value))
    {
        vec.push_back(Value(value));
        return true;
    }

    return false;
}


bool Parser::_parseArrayDecimal(std::vector<Value> &vec, std::string val)
{
    int intval;
    double doubleval;
    int ret = _tryDecimal(val, &intval, &doubleval);
    if (ret!=0)
    {
        if (ret > 0)
        {
            vec.push_back(Value(intval));
            return true;
        }

        if (ret < 0)
        {
            vec.push_back(Value(doubleval));
            return true;
        }
    }
    return false;
}

bool Parser::_parseArray(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    auto ss = line;
    std::vector<Value> _vec;
    while (ss.find(",")!=std::string::npos)
    {
        std::string val=ss.substr(0,ss.find(","));
        ss.erase(0,ss.find(",")+1);
        if (_parseArrayDecimal(_vec,val)) continue;
        if (_parseArrayBool(_vec,val)) continue;
        //Logger::debug("INI") << "string value found for property `" << "`: " << val << std::endl;
        _vec.push_back(Value(val));
    }
    if (_vec.size()>0)
    {
        if (!_parseArrayDecimal(_vec,ss) && !_parseArrayBool(_vec,ss))
        {
            //Logger::debug("INI") << "string value found for property `" << "`: " << ss << std::endl;
            _vec.push_back(Value(ss));
        }
        ini->section(_section)->setPropertyArray(name, _vec);
        //Logger::debug("INI") << "array value found for property `" << name << "`: " << line << std::endl;
        return true;
    }
    return false;
}*/

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
            toLower(_section);

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
