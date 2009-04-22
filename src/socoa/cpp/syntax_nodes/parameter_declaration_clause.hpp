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

#ifndef SOCOA_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_CLAUSE_HPP
#define SOCOA_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_CLAUSE_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "parameter_declaration_list.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class parameter_declaration_clause: public composite_node
{
	public:
		parameter_declaration_clause
		(
			boost::optional<parameter_declaration_list>&& a_parameter_declaration_list,
			bool trailing_comma,
			bool ellipsis
		);

		parameter_declaration_clause(const parameter_declaration_clause& o);

		parameter_declaration_clause(parameter_declaration_clause&& o);

		const parameter_declaration_clause&
		operator=(const parameter_declaration_clause& o);

		inline
		const boost::optional<const parameter_declaration_list&>
		get_parameter_declaration_list() const;

		inline
		bool
		has_trailing_comma() const;

		inline
		bool
		has_ellipsis() const;

	private:
		void
		update_node_list();

		boost::optional<parameter_declaration_list> parameter_declaration_list_;
		bool trailing_comma_;
		bool ellipsis_;
};

inline
const boost::optional<const parameter_declaration_list&>
parameter_declaration_clause::get_parameter_declaration_list() const
{
	return boost::optional<const parameter_declaration_list&>(parameter_declaration_list_);
}

inline
bool
parameter_declaration_clause::has_trailing_comma() const
{
	return trailing_comma_;
}

inline
bool
parameter_declaration_clause::has_ellipsis() const
{
	return ellipsis_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
