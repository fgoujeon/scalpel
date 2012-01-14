/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;

type_specifier_seq_type
get_type_specifier_seq_type(const syntax_nodes::type_specifier_seq& type_specifier_seq_node)
{
	//
	//node counters' declaration
	//

	unsigned int class_specifier_count = 0; //class/struct XXX {...};
	unsigned int union_specifier_count = 0; //union XXX {...};
	unsigned int enum_specifier_count = 0; //enum XXX {...};
	unsigned int class_elaborated_specifier_count = 0; //class/struct XXX;
	unsigned int union_elaborated_specifier_count = 0; //union XXX;
	unsigned int simple_type_specifier_count = 0;



	//
	//node counting
	//

	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
	{
		const type_specifier& type_specifier_node = *i;

		if(get<simple_type_specifier>(&type_specifier_node))
		{
			++simple_type_specifier_count;
		}
		else if(boost::optional<const class_specifier&> opt_class_specifier_node = get<class_specifier>(&type_specifier_node))
		{
			const class_head& class_head_node = get_class_head(*opt_class_specifier_node);
			const class_key& class_key_node = get_class_key(class_head_node);

			if(get<predefined_text_node<str::class_>>(&class_key_node))
				++class_specifier_count;
			else if(get<predefined_text_node<str::struct_>>(&class_key_node))
				++class_specifier_count;
			else if(get<predefined_text_node<str::union_>>(&class_key_node))
				++union_specifier_count;
			else
				assert(false);
		}
		else if(get<enum_specifier>(&type_specifier_node))
		{
			++enum_specifier_count;
		}
		else if(auto opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node))
		{
			auto elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

			if(boost::optional<const class_elaborated_specifier&> opt_class_elaborated_specifier_node = get<class_elaborated_specifier>(&elaborated_type_specifier_node))
			{
				const class_key& class_key_node = get_class_key(*opt_class_elaborated_specifier_node);

				if(get<predefined_text_node<str::class_>>(&class_key_node))
					++class_elaborated_specifier_count;
				else if(get<predefined_text_node<str::struct_>>(&class_key_node))
					++class_elaborated_specifier_count;
				else if(get<predefined_text_node<str::union_>>(&class_key_node))
					++union_elaborated_specifier_count;
				else
					assert(false);
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
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count >= 1 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::SIMPLE_TYPE;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::NO_TYPE;
	else if
	(
		class_specifier_count == 1 &&
		class_elaborated_specifier_count == 0 &&
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::CLASS_DECLARATION;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 1 &&
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::CLASS_FORWARD_DECLARATION;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		union_specifier_count == 1 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::UNION_DECLARATION;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 1 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 0
	)
		return type_specifier_seq_type::UNION_FORWARD_DECLARATION;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		union_specifier_count == 0 &&
		union_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		enum_specifier_count == 1
	)
		return type_specifier_seq_type::ENUMERATION_DECLARATION;

	throw std::runtime_error("get_type_specifier_seq_type error");
}

syntax_nodes::decl_specifier_seq
to_decl_specifier_seq(const syntax_nodes::type_specifier_seq& type_specifier_seq_node)
{
	decl_specifier_seq decl_specifier_seq_node;

	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
		decl_specifier_seq_node.push_back(*i);

	return decl_specifier_seq_node;
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

