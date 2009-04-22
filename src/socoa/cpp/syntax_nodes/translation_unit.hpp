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

#ifndef SOCOA_CPP_SYNTAX_NODES_TRANSLATION_UNIT_HPP
#define SOCOA_CPP_SYNTAX_NODES_TRANSLATION_UNIT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "declaration_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
translation_unit
	= [declaration_seq]
;
\endverbatim
*/
class translation_unit: public composite_node
{
	public:
		translation_unit
		(
			boost::optional<space>&& first_space_node,
			boost::optional<declaration_seq>&& declaration_seq_node,
			boost::optional<space>&& post_declaration_seq_node
		);

		translation_unit(const translation_unit& o);

		translation_unit(translation_unit&& o);

		const translation_unit&
		operator=(const translation_unit& o);

		inline
		const boost::optional<const declaration_seq&>
		declaration_seq_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> first_space_;
		boost::optional<declaration_seq> declaration_seq_;
		boost::optional<space> post_declaration_seq_;
};

inline
const boost::optional<const declaration_seq&>
translation_unit::declaration_seq_node() const
{
	return boost::optional<const declaration_seq&>(declaration_seq_);
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
