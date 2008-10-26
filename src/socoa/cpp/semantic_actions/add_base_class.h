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
#include <memory>
#include <boost/spirit/core.hpp>
#include "../grammar.h"
#include "../generic_syntax_analyzer.h"

namespace socoa { namespace cpp { namespace semantic_actions
{

template <class IteratorT>
class add_base_class
{
    public:
        add_base_class(const grammar& grammar);

        void
        operator()(IteratorT first, IteratorT last) const;

    private:
        std::shared_ptr<generic_syntax_analyzer> analyzer_;
};

template <class IteratorT>
add_base_class<IteratorT>::add_base_class(const grammar& grammar):
    analyzer_(std::make_shared<generic_syntax_analyzer>(grammar))
{
}

template <class IteratorT>
void
add_base_class<IteratorT>::operator()(IteratorT first, IteratorT last) const
{
    using namespace boost::spirit;

    std::string base_specifier_str(first, last);

    std::cout << "base specifier: " << base_specifier_str << '\n';

    //analyze base specifier
    const std::shared_ptr<program_syntax_tree::base_specifier> base_specifier = analyzer_->convert
    <
        program_syntax_tree::base_specifier,
        grammar::start_parser_id::START_BASE_SPECIFIER
    >
    (
        base_specifier_str,
        &generic_syntax_analyzer::evaluate_base_specifier
    );


    const std::shared_ptr
    <
        program_syntax_tree::nested_identifier_or_template_id
    > nested_identifier_or_template_id = base_specifier->nested_identifier_or_template_id_;
    if(!nested_identifier_or_template_id) return;

    const std::shared_ptr
    <
        program_syntax_tree::identifier_or_template_id
    > identifier_or_template_id = nested_identifier_or_template_id->identifier_or_template_id_;
    if(!identifier_or_template_id) return;

    const std::shared_ptr
    <
        program_syntax_tree::identifier
    > identifier = std::dynamic_pointer_cast<program_syntax_tree::identifier>(identifier_or_template_id);
    if(identifier)
    {
        const std::string& value = identifier->value_;

        std::cout << "base class: " << value << '\n';
    }
}

}}} //namespace socoa::cpp::semantic_actions

#endif
