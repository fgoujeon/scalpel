/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CPPPARSER_TEMPLATE_NAME_PARSER_H
#define CPPPARSER_TEMPLATE_NAME_PARSER_H

#include "../scope_cursor.h"
#include "../program_model/namespace_.h"
#include "../program_model/class_.h"

namespace cppparser
{

template <class ScannerT>
class template_name_parser
{
    public:
        typedef boost::spirit::nil_t result_t;

        template_name_parser(const scope_cursor& scope_cursor, const boost::spirit::rule<ScannerT>& identifier_rule):
            m_scope_cursor(scope_cursor),
            m_identifier_rule(identifier_rule)
        {
        }

        template <typename ScannerT2>
        std::ptrdiff_t
        operator()(ScannerT2 const& scan, result_t& result) const
        {
            using namespace boost::spirit;

            //get identifier's name by parsing input with identifier rule
            parse_info<> info = parse(scan.first, m_identifier_rule);

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

            //Check whether the input is really a template name
            //the input really designates the name of a class template only if a class of the same name has been declared.
            std::weak_ptr<program_model::namespace_> current_namespace = m_scope_cursor.current_namespace();
            if(current_namespace.lock()->find_member_by_name<program_model::class_>(identifier_name))
            {
                return info.length; //successful match
            }
            else
            {
                return -1; //unsuccessful match
            }

            return info.length;
        }

    private:
        const scope_cursor& m_scope_cursor;
        const boost::spirit::rule<ScannerT>& m_identifier_rule;
};

} //namespace cppparser

#endif
