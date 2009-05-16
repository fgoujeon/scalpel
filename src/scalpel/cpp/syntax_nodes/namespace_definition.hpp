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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP

#include <memory>
#include <string>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "identifier.hpp"
#include "list_node.hpp"
#include "declaration_fwd.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef list_node<declaration> declaration_seq;

/**
namespace_definition
	= "namespace", [identifier], "{", [declaration_seq], "}"
;
*/
class namespace_definition: public composite_node
{
	public:
		namespace_definition
		(
			optional_node<space>&& post_namespace_keyword_space_node,
			optional_node<identifier>&& identifier_node,
			optional_node<space>&& post_identifier_space_node,
			optional_node<space>&& post_opening_brace_space_node,
			optional_node<declaration_seq>&& declaration_seq_node,
			optional_node<space>&& post_declaration_seq_space_node
		);

		namespace_definition(const namespace_definition& o);

		namespace_definition(namespace_definition&& o);

		const namespace_definition&
		operator=(const namespace_definition& o);

		inline
		const optional_node<identifier>&
	   	identifier_node() const;

		inline
		const optional_node<list_node<declaration>>&
		declaration_seq_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_namespace_keyword_space_;
		optional_node<identifier> identifier_;
		optional_node<space> post_identifier_space_;
		optional_node<space> post_opening_brace_space_;
		std::unique_ptr<optional_node<declaration_seq>> declaration_seq_;
		optional_node<space> post_declaration_seq_space_;
};

inline
const optional_node<identifier>&
namespace_definition::identifier_node() const
{
	return identifier_;
}

inline
const optional_node<list_node<declaration>>&
namespace_definition::declaration_seq_node() const
{
	return *declaration_seq_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
