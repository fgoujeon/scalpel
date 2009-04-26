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

#ifndef SOCOA_CPP_SYNTAX_NODES_QUALIFIED_NESTED_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_QUALIFIED_NESTED_ID_HPP

#include <memory>
#include "composite_node.hpp"
#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
qualified_nested_id
	= ["::"], nested_name_specifier, ["template"], unqualified_id
;
\endverbatim
*/
class qualified_nested_id: public composite_node
{
	public:
		qualified_nested_id
		(
			bool leading_double_colon,
			boost::optional<space>&& post_double_colon_space_node,
			nested_name_specifier&& a_nested_name_specifier,
			boost::optional<space>&& post_nested_name_specifier_space_node,
			bool template_keyword,
			boost::optional<space>&& post_template_keyword_space_node,
			unqualified_id&& an_unqualified_id
		);

		qualified_nested_id(const qualified_nested_id& o);

		qualified_nested_id(qualified_nested_id&& o);

		const qualified_nested_id&
		operator=(const qualified_nested_id& o);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const nested_name_specifier&
		get_nested_name_specifier() const;

		inline
		bool
		has_template_keyword() const;

		inline
		const unqualified_id&
		get_unqualified_id() const;

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		boost::optional<space> post_double_colon_space_;
		nested_name_specifier nested_name_specifier_;
		boost::optional<space> post_nested_name_specifier_space_;
		bool template_keyword_;
		boost::optional<space> post_template_keyword_space_;
		unqualified_id unqualified_id_;
};

inline
bool
qualified_nested_id::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const nested_name_specifier&
qualified_nested_id::get_nested_name_specifier() const
{
	return nested_name_specifier_;
}

inline
bool
qualified_nested_id::has_template_keyword() const
{
	return template_keyword_;
}

inline
const unqualified_id&
qualified_nested_id::get_unqualified_id() const
{
	return unqualified_id_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
