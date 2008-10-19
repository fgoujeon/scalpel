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

#include <boost/spirit.hpp>
#include "../scope_cursor.h"
#include "../program_tree/namespace_.h"
#include "../program_tree/class_.h"

namespace socoa { namespace cpp { namespace functor_parsers
{

template <class ScannerT, class IdentifierParserT>
class type_name
{
    public:
        typedef boost::spirit::nil_t result_t;

        type_name(const scope_cursor& scope_cursor, const IdentifierParserT& identifier_rule):
            scope_cursor_(scope_cursor),
            identifier_rule_(identifier_rule)
        {
        }

        std::ptrdiff_t
        operator()(ScannerT const& scan, result_t&) const
        {
            using namespace boost::spirit;

            //get identifier's name by parsing input with identifier rule
            parse_info<> info = parse
            (
                scan.first,
                scan.last,
                identifier_rule_
            );

            //not an identifier?
            if(!info.hit)
            {
                return -1; //tell the parser that this in an unsuccessful match
            }

            //create identifier string from begin and end pointers
            std::string identifier_name(scan.first, info.stop);

            //move the scanner forward to the end of identifier
            for(unsigned int i = 0; i < info.length; ++i)
            {
                ++scan;
            }

            //Check whether the identifier is really a type name
            //the identifier really designates the name of a class template only if a class of the same name has been declared.
            const std::shared_ptr<program_tree::named_scope> current_scope = scope_cursor_.get_current_scope();
            /*if(current_scope->find_member_by_name<program_tree::class_>(identifier_name))
            {
                return info.length; //successful match
            }

            return -1; //unsuccessful match
            */

            return info.length;
        }

    private:
        const scope_cursor& scope_cursor_;
        const IdentifierParserT& identifier_rule_;
};

}}} //namespace socoa::cpp::functor_parsers

#endif
