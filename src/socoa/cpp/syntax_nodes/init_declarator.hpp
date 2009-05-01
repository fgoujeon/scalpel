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

#ifndef SOCOA_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP
#define SOCOA_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "declarator.hpp"
#include "space.hpp"
#include "initializer.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
init_declarator
	= declarator, [initializer]
;
\endverbatim
*/
class init_declarator: public composite_node
{
	public:
		init_declarator
		(
			declarator&& a_declarator,
			boost::optional<space>&& space_node,
			boost::optional<initializer>&& initializer_node
		);

		init_declarator(const init_declarator& o);

		init_declarator(init_declarator&& o);

		const init_declarator&
		operator=(const init_declarator& o);

		inline
		const declarator&
		declarator_node() const;

	private:
		void
		update_node_list();

		declarator declarator_;
		boost::optional<space> space_;
		boost::optional<initializer> initializer_;
};

inline
const declarator&
init_declarator::declarator_node() const
{
	return declarator_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
