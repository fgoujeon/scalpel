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

#ifndef SOCOA_CPP_SYNTAX_NODES_MEM_INITIALIZER_HPP
#define SOCOA_CPP_SYNTAX_NODES_MEM_INITIALIZER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "mem_initializer_id.hpp"
#include "expression_list.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
mem_initializer
	= mem_initializer_id >> !s >> '(' >> !s >> !(expression_list >> !s) >> ')'
;
*/
class mem_initializer: public composite_node
{
	public:
		explicit
		mem_initializer
		(
			mem_initializer_id&& mem_initializer_id_node,
			boost::optional<space>&& post_mem_initializer_id_space_node,
			boost::optional<space>&& post_opening_bracket_space_node,
			boost::optional<expression_list>&& expression_list_node,
			boost::optional<space>&& post_expression_list_space_node
		);

		mem_initializer(const mem_initializer& o);

		mem_initializer(mem_initializer&& o);

		const mem_initializer&
		operator=(const mem_initializer& o);

		inline
		const mem_initializer_id&
		get_mem_initializer_id() const;

	private:
		void
		update_node_list();

		mem_initializer_id mem_initializer_id_;
		boost::optional<space> post_mem_initializer_id_space_;
		boost::optional<space> post_opening_bracket_space_;
		boost::optional<expression_list> expression_list_;
		boost::optional<space> post_expression_list_space_;
};

inline
const mem_initializer_id&
mem_initializer::get_mem_initializer_id() const
{
	return mem_initializer_id_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
