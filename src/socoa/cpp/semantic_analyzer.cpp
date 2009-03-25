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

#include "semantic_analyzer.hpp"

#include <iostream>

namespace socoa { namespace cpp
{

using namespace syntax_tree;
using namespace semantic_graph;

semantic_analyzer::semantic_analyzer():
	conversion_helper_(*this)
{
}

semantic_graph_t
semantic_analyzer::operator()(const syntax_tree_t& tree)
{
	//reinit semantic graph
	semantic_graph_.clear();

	convert(tree);

	return semantic_graph_;
}

void
semantic_analyzer::convert(const class_head& item)
{
}

void
semantic_analyzer::convert(const class_specifier& item)
{
	boost::optional<const identifier&> id = item.get_class_head().get_identifier();

	if(id)
	{
		semantic_graph_.add(class_(id->get_value()));
	}
}

void
semantic_analyzer::convert(const conversion_function_id&)
{
}

void
semantic_analyzer::convert(const ctor_initializer& item)
{
}

void
semantic_analyzer::convert(const cv_qualifier& item)
{
}

void
semantic_analyzer::convert(const declarator& item)
{
}

void
semantic_analyzer::convert(const destructor_name&)
{
}

void
semantic_analyzer::convert(const direct_declarator& item)
{
}

void
semantic_analyzer::convert(const direct_declarator::array_part&)
{
}

void
semantic_analyzer::convert(const direct_declarator::function_part& item)
{
}

void
semantic_analyzer::convert(const elaborated_type_specifier& item)
{
	const boost::optional<const class_key&> a_class_key = item.get_class_key();
	const boost::optional<const identifier&> an_identifier = item.get_identifier();

	if(a_class_key && an_identifier)
	{
		semantic_graph_.add(class_(an_identifier->get_value()));
	}
}

void
semantic_analyzer::convert(const function_definition& item)
{
}

void
semantic_analyzer::convert(const identifier& item)
{
}

void
semantic_analyzer::convert(const init_declarator& item)
{
}

void
semantic_analyzer::convert(const mem_initializer& item)
{
}

void
semantic_analyzer::convert(const member_declaration_function_definition& item)
{
}

void
semantic_analyzer::convert(const member_declaration_member_declarator_list& item)
{
}

void
semantic_analyzer::convert(const member_declaration_unqualified_id& item)
{
}

void
semantic_analyzer::convert(const member_declarator_bit_field_member& item)
{
}

void
semantic_analyzer::convert(const member_declarator_declarator& item)
{
}

void
semantic_analyzer::convert(const member_specification& item)
{
}

void
semantic_analyzer::convert(const member_specification_access_specifier& item)
{
}

void
semantic_analyzer::convert(const namespace_definition& item)
{
	std::cout << "namespace\n";
}

void
semantic_analyzer::convert(const nested_identifier_or_template_id& item)
{
}

void
semantic_analyzer::convert(const nested_name_specifier& item)
{
}

void
semantic_analyzer::convert(const nested_name_specifier::second_part&)
{
}

void
semantic_analyzer::convert(const operator_function_id&)
{
}

void
semantic_analyzer::convert(const parameter_declaration& item)
{
}

void
semantic_analyzer::convert(const parameter_declaration_clause& item)
{
}

void
semantic_analyzer::convert(const ptr_operator& item)
{
}

void
semantic_analyzer::convert(const qualified_identifier& item)
{
}

void
semantic_analyzer::convert(const qualified_nested_id& item)
{
}

void
semantic_analyzer::convert(const qualified_operator_function_id&)
{
}

void
semantic_analyzer::convert(const qualified_template_id& item)
{
}

void
semantic_analyzer::convert(const simple_declaration& item)
{
	convert(item.get_decl_specifier_seq());
}

void
semantic_analyzer::convert(const simple_template_type_specifier& item)
{
}

void
semantic_analyzer::convert(const template_declaration& item)
{
}

void
semantic_analyzer::convert(const template_id& item)
{
}

void
semantic_analyzer::convert(const using_declaration& item)
{
}

void
semantic_analyzer::convert(const using_directive& item)
{
}

void
semantic_analyzer::convert_separator(const std::string& separator)
{
}

}} //namespace socoa::cpp

