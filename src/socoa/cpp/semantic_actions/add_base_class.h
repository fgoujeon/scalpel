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

#ifndef SOCOA_CPP_SEMANTIC_ACTIONS_ADD_BASE_CLASS_H
#define SOCOA_CPP_SEMANTIC_ACTIONS_ADD_BASE_CLASS_H

#include <iostream>
#include <boost/spirit/core.hpp>
#include "../grammar.h"

namespace socoa { namespace cpp { namespace semantic_actions
{

template <class IteratorT>
class add_base_class
{
    public:
        add_base_class
        (
            const grammar& cpp_grammar
        );

        void
        operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        const grammar& grammar_;
};

template <class IteratorT>
add_base_class<IteratorT>::add_base_class
(
    const grammar& cpp_grammar
):
    grammar_(cpp_grammar)
{
}

template <class IteratorT>
void
add_base_class<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    using namespace boost::spirit;

    std::cout << "base specifier: " << std::string(first, last) << '\n';

    pt_parse
    (
        first,
        last,
        grammar_.use_parser<grammar::START_BASE_SPECIFIER>(),
        space_p
    );
}

}}} //namespace socoa::cpp::semantic_actions

#endif
