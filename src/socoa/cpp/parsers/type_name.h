/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_FUNCTOR_PARSERS_TEMPLATE_NAME_H
#define SOCOA_CPP_FUNCTOR_PARSERS_TEMPLATE_NAME_H

#include <iostream>
#include "../name_lookup.h"
#include "../scanner.h"
#include "../grammar.h"

namespace socoa { namespace cpp { namespace parsers
{

class type_name: public grammar::type_name_parser
{
    public:
        void
        set_input(const std::string& input);

        std::ptrdiff_t
        operator()(const scanner_t& scan) const;

    private:
        /**
        Replace string literal content by white spaces
        */
        inline
        void
        purify_string_literals(std::string& str) const;

		const std::string* input_;
};

inline
void
type_name::purify_string_literals(std::string& str) const
{
    bool in_string_literal = false;
    bool in_char_literal = false;
    bool previous_char_was_espace_char = false;
    for
    (
        std::string::iterator i = str.begin();
        i != str.end();
        ++i
    )
    {
        bool replace_by_white_space = false;

        if(in_string_literal)
        {
            if(*i == '"' && !previous_char_was_espace_char)
            {
                in_string_literal = false;
            }
            else
                replace_by_white_space = true;
        }
        else if(in_char_literal)
        {
            if(*i == '\'' && !previous_char_was_espace_char)
            {
                in_char_literal = false;
            }
            else
                replace_by_white_space = true;
        }
        else
        {
            if(*i == '"') in_string_literal = true;
            else if(*i == '\'') in_char_literal = true;
        }

        previous_char_was_espace_char = (*i == '\\' && !previous_char_was_espace_char);

        if(replace_by_white_space) *i = ' ';
    }
}

}}} //namespace socoa::cpp::parsers

#endif
