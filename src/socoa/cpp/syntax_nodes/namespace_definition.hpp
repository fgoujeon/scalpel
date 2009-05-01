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

#ifndef SOCOA_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP
#define SOCOA_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP

#include <memory>
#include <string>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "identifier.hpp"
#include "sequence_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class declaration;
typedef sequence_node<declaration> declaration_seq;

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
			boost::optional<space>&& post_namespace_keyword_space_node,
			boost::optional<identifier>&& identifier_node,
			boost::optional<space>&& post_identifier_space_node,
			boost::optional<space>&& post_opening_brace_space_node,
			boost::optional<declaration_seq>&& declaration_seq_node,
			boost::optional<space>&& post_declaration_seq_space_node
		);

		namespace_definition(const namespace_definition& o);

		namespace_definition(namespace_definition&& o);

		const namespace_definition&
		operator=(const namespace_definition& o);

		inline
		const boost::optional<const identifier&>
	   	identifier_node() const;

		inline
		const boost::optional<const sequence_node<declaration>&>
		declaration_seq_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> post_namespace_keyword_space_;
		boost::optional<identifier> identifier_;
		boost::optional<space> post_identifier_space_;
		boost::optional<space> post_opening_brace_space_;
		std::unique_ptr<declaration_seq> declaration_seq_;
		boost::optional<space> post_declaration_seq_space_;
};

inline
const boost::optional<const identifier&>
namespace_definition::identifier_node() const
{
	return boost::optional<const identifier&>(identifier_);
}

inline
const boost::optional<const sequence_node<declaration>&>
namespace_definition::declaration_seq_node() const
{
	if(declaration_seq_)
		return boost::optional<const sequence_node<declaration>&>(*declaration_seq_);
	else
		return boost::optional<const sequence_node<declaration>&>();
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
