/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include <boost/spirit/core.hpp>
#include "../scope_cursor.h"
#include "../name_lookup.h"

namespace socoa { namespace cpp { namespace functor_parsers
{

class type_name
{
    public:
        typedef boost::spirit::nil_t result_t;

        type_name(const scope_cursor& scope_cursor, const std::string& last_parsed_identifier):
            scope_cursor_(scope_cursor),
            last_parsed_identifier_(last_parsed_identifier)
        {
        }

        template <class ScannerT>
        std::ptrdiff_t
        operator()(ScannerT const& scan, result_t&) const
        {
            //Check whether the identifier really designates a type name.
            //It does only if a type of the same name has been declared.
            const std::shared_ptr<program_tree::name_tree_composite> current_scope = scope_cursor_.get_current_scope(); //get current scope
            const std::shared_ptr<program_tree::name_tree_component> found_symbol = find_unqualified_name(current_scope, last_parsed_identifier_); //find the name from the current scope
            if(found_symbol && found_symbol->is_a_type()) //if a type with that name has been found
            {
                //move the scanner forward to the end of identifier
                for(unsigned int i = 0; i < last_parsed_identifier_.size(); ++i)
                {
                    ++scan;
                }

                return last_parsed_identifier_.size(); //successful match
            }

            return -1; //unsuccessful match
        }

    private:
        const scope_cursor& scope_cursor_;
        const std::string& last_parsed_identifier_;
};

}}} //namespace socoa::cpp::functor_parsers

#endif
