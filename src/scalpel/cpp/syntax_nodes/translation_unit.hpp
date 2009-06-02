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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TRANSLATION_UNIT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TRANSLATION_UNIT_HPP

#include "common.hpp"
#include "declaration_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
translation_unit
	= [declaration_seq]
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<space>,
		optional_node<declaration_seq>,
		optional_node<space>
	>
	translation_unit_t
;

class translation_unit: public composite_node
{
	public:
		typedef translation_unit_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		translation_unit
		(
			optional_node<space>&& o0,
			optional_node<declaration_seq>&& o1,
			optional_node<space>&& o2
		);

		translation_unit
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		translation_unit(const translation_unit& o);

		translation_unit(translation_unit&& o);

		const translation_unit&
		operator=(const translation_unit& o);

		inline
		const optional_node<declaration_seq>&
		declaration_seq_node() const;

	private:
		type impl_;
};

const optional_node<declaration_seq>&
translation_unit::declaration_seq_node() const
{
	return get<1>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
