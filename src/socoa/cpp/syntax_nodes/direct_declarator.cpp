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

namespace socoa { namespace cpp { namespace syntax_nodes
{

direct_declarator::direct_declarator
(
	first_part&& first_part_node,
	boost::optional<space>&& pre_last_part_seq_space_node,
    boost::optional<sequence_node<last_part>>&& a_last_part_seq
):
	first_part_(first_part_node),
	pre_last_part_seq_space_(pre_last_part_seq_space_node),
    last_part_seq_(std::move(a_last_part_seq))
{
	update_node_list();
}

direct_declarator::direct_declarator(const direct_declarator& o):
	composite_node(),
	first_part_(o.first_part_),
	pre_last_part_seq_space_(o.pre_last_part_seq_space_),
    last_part_seq_(o.last_part_seq_)
{
	update_node_list();
}

direct_declarator::direct_declarator(direct_declarator&& o):
	first_part_(std::move(o.first_part_)),
	pre_last_part_seq_space_(std::move(o.pre_last_part_seq_space_)),
    last_part_seq_(std::move(o.last_part_seq_))
{
	update_node_list();
}

const direct_declarator&
direct_declarator::operator=(const direct_declarator& o)
{
	direct_declarator copy(o);
	std::swap(copy, *this);
	return *this;
}

void
direct_declarator::update_node_list()
{
	clear();
	add(first_part_);
	if(pre_last_part_seq_space_) add(*pre_last_part_seq_space_);
	if(last_part_seq_) add(*last_part_seq_);
}


direct_declarator::function_part::function_part
(
	boost::optional<space>&& post_opening_bracket_space_node,
	boost::optional<parameter_declaration_clause>&& a_parameter_declaration_clause,
	boost::optional<space>&& post_parameter_declaration_clause_space_node,
	boost::optional<space>&& cv_qualifier_seq_space_node,
	boost::optional<cv_qualifier_seq>&& a_cv_qualifier_seq
):
	post_opening_bracket_space_(post_opening_bracket_space_node),
    parameter_declaration_clause_(std::move(a_parameter_declaration_clause)),
	post_parameter_declaration_clause_space_(post_parameter_declaration_clause_space_node),
	cv_qualifier_seq_space_(cv_qualifier_seq_space_node),
    cv_qualifier_seq_(a_cv_qualifier_seq)
{
	update_node_list();
}

direct_declarator::function_part::function_part(const function_part& o):
	composite_node(),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
    parameter_declaration_clause_(o.parameter_declaration_clause_),
	post_parameter_declaration_clause_space_(o.post_parameter_declaration_clause_space_),
	cv_qualifier_seq_space_(o.cv_qualifier_seq_space_),
    cv_qualifier_seq_(o.cv_qualifier_seq_)
{
	update_node_list();
}

direct_declarator::function_part::function_part(function_part&& o):
	composite_node(),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
    parameter_declaration_clause_(std::move(o.parameter_declaration_clause_)),
	post_parameter_declaration_clause_space_(o.post_parameter_declaration_clause_space_),
	cv_qualifier_seq_space_(o.cv_qualifier_seq_space_),
    cv_qualifier_seq_(std::move(o.cv_qualifier_seq_))
{
	update_node_list();
}

const direct_declarator::function_part&
direct_declarator::function_part::operator=(const function_part& o)
{
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
    parameter_declaration_clause_ = o.parameter_declaration_clause_;
	post_parameter_declaration_clause_space_ = o.post_parameter_declaration_clause_space_;
	cv_qualifier_seq_space_ = o.cv_qualifier_seq_space_;
    cv_qualifier_seq_ = o.cv_qualifier_seq_;

	update_node_list();

	return *this;
}

void
direct_declarator::function_part::update_node_list()
{
	clear();

	add(opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	if(parameter_declaration_clause_) add(*parameter_declaration_clause_);
	if(post_parameter_declaration_clause_space_) add(*post_parameter_declaration_clause_space_);
	add(closing_bracket);
	if(cv_qualifier_seq_space_) add(*cv_qualifier_seq_space_);
	if(cv_qualifier_seq_) add(*cv_qualifier_seq_);
}

}}} //namespace socoa::cpp::syntax_nodes
