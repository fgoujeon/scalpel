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

#ifndef SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_CLAUSE_H
#define SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_CLAUSE_H

#include <memory>
#include <boost/optional.hpp>
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class parameter_declaration;

class parameter_declaration_clause
{
	public:
		parameter_declaration_clause
		(
			std::shared_ptr<util::sequence<parameter_declaration, util::extern_strings::comma>> a_parameter_declaration_list,
			bool trailing_comma,
			bool ellipsis
		);

		inline
		const boost::optional<const util::sequence<parameter_declaration, util::extern_strings::comma>&>
		get_parameter_declaration_list() const;

		inline
		bool
		has_trailing_comma() const;

		inline
		bool
		has_ellipsis() const;

	private:
		boost::optional<util::sequence<parameter_declaration, util::extern_strings::comma>> parameter_declaration_list_;
		bool trailing_comma_;
		bool ellipsis_;
};

inline
const boost::optional<const util::sequence<parameter_declaration, util::extern_strings::comma>&>
parameter_declaration_clause::get_parameter_declaration_list() const
{
	return boost::optional<const util::sequence<parameter_declaration, util::extern_strings::comma>&>(parameter_declaration_list_);
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

}}} //namespace socoa::cpp::syntax_tree

#endif
