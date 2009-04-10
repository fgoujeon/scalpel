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

#include "direct_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

direct_declarator::direct_declarator
(
    boost::optional<declarator_id>&& a_declarator_id,
    boost::optional<declarator>&& a_declarator,
    std::vector<other_part>&& other_parts
):
	/*
    declarator_id_(a_declarator_id),
    declarator_(a_declarator),*/
    other_parts_(std::move(other_parts))
{
	if(a_declarator_id)
		declarator_id_ = std::move(std::unique_ptr<declarator_id>(new declarator_id(std::move(*a_declarator_id))));
	if(a_declarator)
		declarator_ = std::move(std::unique_ptr<declarator>(new declarator(std::move(*a_declarator))));

	if(declarator_id_) add(*declarator_id_);
	if(declarator_) add(*declarator_);
	for(auto i = other_parts_.begin(); i != other_parts_.end(); ++i)
		add(*i);
}

direct_declarator::direct_declarator(direct_declarator&& o):
    declarator_id_(std::move(o.declarator_id_)),
    declarator_(std::move(o.declarator_)),
    other_parts_(std::move(o.other_parts_))
{
}

direct_declarator::function_part::function_part
(
    parameter_declaration_clause&& a_parameter_declaration_clause,
    boost::optional<cv_qualifier_seq>&& a_cv_qualifier_seq
):
    parameter_declaration_clause_(std::move(a_parameter_declaration_clause))/*,
    cv_qualifier_seq_(a_cv_qualifier_seq)*/
{
	if(a_cv_qualifier_seq)
		cv_qualifier_seq_ = std::move(std::unique_ptr<cv_qualifier_seq>(new cv_qualifier_seq(std::move(*a_cv_qualifier_seq))));

	add(parameter_declaration_clause_);
	if(cv_qualifier_seq_) add(*cv_qualifier_seq_);
}

direct_declarator::function_part::function_part(function_part&& o):
    parameter_declaration_clause_(std::move(o.parameter_declaration_clause_)),
    cv_qualifier_seq_(std::move(o.cv_qualifier_seq_))
{
}

}}} //namespace socoa::cpp::syntax_tree
