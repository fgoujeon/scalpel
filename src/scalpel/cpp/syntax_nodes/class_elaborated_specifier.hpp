/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_ELABORATED_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_ELABORATED_SPECIFIER_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "class_key.hpp"
#include "space.hpp"
#include "nested_name_specifier.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
class_elaborated_specifier
	= class_key, ["::"], [nested_name_specifier], identifier
;
*/
class class_elaborated_specifier: public composite_node
{
	public:
		class_elaborated_specifier
		(
			class_key&& class_key_node,
			optional_node<space>&& post_class_key_space_node,
			bool double_colon,
			optional_node<space>&& post_double_colon_space_node,
			optional_node<nested_name_specifier>&& nested_name_specifier_node,
			optional_node<space>&& post_nested_name_specifier_space_node,
			identifier&& identifier_node
		);

		class_elaborated_specifier(const class_elaborated_specifier& o);

		class_elaborated_specifier(class_elaborated_specifier&& o);

		const class_elaborated_specifier&
		operator=(const class_elaborated_specifier& o);

		inline
		const identifier&
		identifier_node() const;

	private:
		void
		update_node_list();

		class_key class_key_;
		optional_node<space> post_class_key_space_;
		bool double_colon_;
		optional_node<space> post_double_colon_space_;
		optional_node<nested_name_specifier> nested_name_specifier_;
		optional_node<space> post_nested_name_specifier_space_;
		identifier identifier_;
};

inline
const identifier&
class_elaborated_specifier::identifier_node() const
{
	return identifier_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
