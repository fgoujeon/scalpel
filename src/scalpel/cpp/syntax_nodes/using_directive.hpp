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

#ifndef SCALPEL_CPP_SYNTAX_NODES_USING_DIRECTIVE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_USING_DIRECTIVE_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "identifier.hpp"
#include "nested_name_specifier.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
using_directive
	= "using" >> !s >> "namespace" >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier >> !s >> ch_p(';')
;
\endverbatim
*/
class using_directive: public composite_node
{
	public:
		using_directive
		(
			boost::optional<space>&& post_using_keyword_space_node,
			boost::optional<space>&& post_namespace_keyword_space_node,
			bool leading_double_colon,
			boost::optional<space>&& post_leading_double_colon_space_node,
			boost::optional<nested_name_specifier>&& nested_name_specifier_node,
			boost::optional<space>&& post_nested_name_specifier_space_node,
			identifier&& identifier_node,
			boost::optional<space>&& post_identifier_space_node
		);

		using_directive(const using_directive& o);

		using_directive(using_directive&& o);

		const using_directive&
		operator=(const using_directive& o);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const boost::optional<const nested_name_specifier&>
		nested_name_specifier_node() const;

		inline
		const identifier&
	   	identifier_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> post_using_keyword_space_;
		boost::optional<space> post_namespace_keyword_space_;
		bool leading_double_colon_;
		boost::optional<space> post_leading_double_colon_space_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<space> post_nested_name_specifier_space_;
		identifier identifier_;
		boost::optional<space> post_identifier_space_;
};

inline
bool
using_directive::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const boost::optional<const nested_name_specifier&>
using_directive::nested_name_specifier_node() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const identifier&
using_directive::identifier_node() const
{
	return identifier_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
