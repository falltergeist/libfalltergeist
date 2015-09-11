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

#ifndef LIBFALLTERGEIST_TXT_LEXER_H
#define LIBFALLTERGEIST_TXT_LEXER_H

// C++ standard includes
#include <sstream>

// Libfalltergeist includes

// Third party includes


namespace libfalltergeist
{
namespace Txt
{

/**
 * A simple lexer for WorldmapFile parser
 */
class Lexer
{
public:
    enum Type : int
    {
        T_NONE = 0,
        T_CONSTANT = 256,
        T_IDENTIFIER,
        T_IF,
        T_AND,
        T_OR, // not used
        T_EQUAL,
        T_GREATER_EQUAL,
        T_LESS_EQUAL,
        T_EOF
    };

    struct Token
    {
        /**
         * Type of lexeme
         */
        int type = Type::T_NONE;

        /**
         * String data of lexeme
         */
        std::string data;

        /**
         * Integer data of lexeme
         */
        unsigned long intData = 0;
    };

    Lexer(const std::string& line);

    /**
     * Get next token from the stream
     */
    int lex();

    /**
     * "Unget" token. Next lex() call will return previous token instead.
     */
    void unLex();

    /**
     * Gets next token and returns true if it's of given type.
     *
     * @param type one of Token::Type constants or ASCII character.
     */
    bool expect(int type);

    const Token& last();

    bool eof();


private:
    std::istringstream _stream;
    Lexer::Token _lastToken;
    bool _recallToken = false;

    char _get(Token& token);
    Lexer::Token _nextToken();
};

}
}




#endif //LIBFALLTERGEIST_TXT_LEXER_H
