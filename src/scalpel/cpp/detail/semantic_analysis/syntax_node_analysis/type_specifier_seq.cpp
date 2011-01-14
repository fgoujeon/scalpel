/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "type_specifier_seq.hpp"
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace syntax_node_analysis
{

using namespace syntax_nodes;

type_specifier_seq_type
get_type_specifier_seq_type(const syntax_nodes::type_specifier_seq& type_specifier_seq_node)
{
	//
	//node counters' declaration
	//

	unsigned int class_specifier_count = 0; //class XXX {...};
	unsigned int class_elaborated_specifier_count = 0; //class XXX;
	unsigned int simple_type_specifier_count = 0;



	//
	//node counting
	//

	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
	{
		auto type_specifier_node = i->main_node();

		if(get<simple_type_specifier>(&type_specifier_node))
		{
			++simple_type_specifier_count;
		}
		else if(get<class_specifier>(&type_specifier_node))
		{
			++class_specifier_count;
		}
		else if(get<enum_specifier>(&type_specifier_node))
		{
		}
		else if(auto opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node))
		{
			auto elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

			if(get<class_elaborated_specifier>(&elaborated_type_specifier_node))
			{
				++class_elaborated_specifier_count;
			}
			else if(get<enum_elaborated_specifier>(&elaborated_type_specifier_node))
			{
			}
			else if(get<typename_template_elaborated_specifier>(&elaborated_type_specifier_node))
			{
			}
			else if(get<typename_elaborated_specifier>(&elaborated_type_specifier_node))
			{
			}
		}
		else if(get<cv_qualifier>(&type_specifier_node))
		{
			//nothing
		}
	}



	//
	//result
	//

	if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count >= 1
	)
		return type_specifier_seq_type::SIMPLE_TYPE;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0
	)
		return type_specifier_seq_type::NO_TYPE;
	else if
	(
		class_specifier_count == 1 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0
	)
		return type_specifier_seq_type::CLASS_DECLARATION;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 1 &&
		simple_type_specifier_count == 0
	)
		return type_specifier_seq_type::CLASS_FORWARD_DECLARATION;

	throw std::runtime_error("get_type_specifier_seq_type error");
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::syntax_node_analysis

