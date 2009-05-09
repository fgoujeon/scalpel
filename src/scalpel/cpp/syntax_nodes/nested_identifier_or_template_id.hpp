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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "nested_name_specifier.hpp"
#include "identifier_or_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class nested_identifier_or_template_id: public composite_node
{
	public:
		nested_identifier_or_template_id
		(
			bool leading_double_colon,
			boost::optional<nested_name_specifier>&& a_nested_name_specifier,
			identifier_or_template_id&& an_identifier_or_template_id
		);

		nested_identifier_or_template_id(const nested_identifier_or_template_id& o);

		nested_identifier_or_template_id(nested_identifier_or_template_id&& o);

		const nested_identifier_or_template_id&
		operator=(const nested_identifier_or_template_id& o);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const boost::optional<const nested_name_specifier&>
		nested_name_specifier_node() const;

		inline
		const identifier_or_template_id&
		identifier_or_template_id_node() const;

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		identifier_or_template_id identifier_or_template_id_;
};

inline
bool
nested_identifier_or_template_id::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const boost::optional<const nested_name_specifier&>
nested_identifier_or_template_id::nested_name_specifier_node() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const identifier_or_template_id&
nested_identifier_or_template_id::identifier_or_template_id_node() const
{
	return identifier_or_template_id_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
