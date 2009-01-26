/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008, 2009  Florian Goujeon

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
#include "../name_lookup.h"

namespace socoa { namespace cpp { namespace semantic_actions
{

template <class IteratorT>
class add_base_class
{
    public:
        add_base_class
        (
            const grammar& grammar,
            const scope_cursor& scope_cursor,
            std::shared_ptr<program_tree::class_>& base_class_reference
        );

        void
        operator()(IteratorT first, IteratorT last) const;

    private:
        std::shared_ptr<generic_syntax_analyzer> analyzer_;
        const scope_cursor& scope_cursor_;
        std::shared_ptr<program_tree::class_>& base_class_reference_;
};

template <class IteratorT>
add_base_class<IteratorT>::add_base_class
(
    const grammar& grammar,
    const scope_cursor& scope_cursor,
    std::shared_ptr<program_tree::class_>& base_class_reference
):
    analyzer_(std::make_shared<generic_syntax_analyzer>(grammar)),
    scope_cursor_(scope_cursor),
    base_class_reference_(base_class_reference)
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
    const std::shared_ptr<program_syntax_tree::base_specifier> base_specifier = analyzer_->analyze
    <
        program_syntax_tree::base_specifier,
        grammar::start_parser_id::START_BASE_SPECIFIER
    >
    (
        base_specifier_str,
        &generic_syntax_analyzer::evaluate_base_specifier
    );
    assert(base_specifier);

    //get access specifier
    const std::shared_ptr<program_syntax_tree::access_specifier> access_specifier = base_specifier->access_specifier_;
    assert(access_specifier);

    //get base class' name
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
        const std::string& base_class_name = identifier->value_;

        std::cout << "base class: " << base_class_name << '\n';

        const std::shared_ptr<program_tree::name_tree_component> base_name = find_unqualified_name(scope_cursor_.get_current_scope(), base_class_name);
        if(!base_name) return; ///@todo throw an exception
        std::cout << "base name found: " << base_name->get_full_name() << '\n';

        const std::shared_ptr<program_tree::class_> base_class = std::dynamic_pointer_cast<program_tree::class_>(base_name);
        if(!base_class) return; ///@todo throw an exception

        //create base specifier and add it to the targeted class
        program_tree::base_specifier base_specifier(base_class, *access_specifier);
        assert(base_class_reference_);
        base_class_reference_->add(base_specifier);
    }
}

}}} //namespace socoa::cpp::semantic_actions

#endif
