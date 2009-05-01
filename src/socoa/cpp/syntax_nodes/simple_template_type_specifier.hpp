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

#ifndef SOCOA_CPP_SYNTAX_NODES_SIMPLE_TEMPLATE_TYPE_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_SIMPLE_TEMPLATE_TYPE_SPECIFIER_HPP

#include <memory>
#include "composite_node.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class simple_template_type_specifier: public composite_node
{
	public:
		simple_template_type_specifier
		(
			bool leading_double_colon,
			nested_name_specifier&& a_nested_name_specifier,
			template_id&& a_template_id
		);

		simple_template_type_specifier(const simple_template_type_specifier& o);

		simple_template_type_specifier(simple_template_type_specifier&& o);

		const simple_template_type_specifier&
		operator=(const simple_template_type_specifier& o);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const nested_name_specifier&
		nested_name_specifier_node() const;

		inline
		const template_id&
		template_id_node() const;

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		nested_name_specifier nested_name_specifier_;
		template_id template_id_;
};

inline
bool
simple_template_type_specifier::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const nested_name_specifier&
simple_template_type_specifier::nested_name_specifier_node() const
{
	return nested_name_specifier_;
}

inline
const template_id&
simple_template_type_specifier::template_id_node() const
{
	return template_id_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
