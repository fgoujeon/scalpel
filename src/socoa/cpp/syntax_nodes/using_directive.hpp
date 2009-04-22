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

#ifndef SOCOA_CPP_SYNTAX_TREE_USING_DIRECTIVE_HPP
#define SOCOA_CPP_SYNTAX_TREE_USING_DIRECTIVE_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "identifier.hpp"
#include "nested_name_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class using_directive: public composite_node
{
	public:
		using_directive
		(
			bool leading_double_colon,
			boost::optional<nested_name_specifier>&& a_nested_name_specifier,
			identifier&& an_identifier
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
		get_nested_name_specifier() const;

		inline
		const identifier&
	   	get_identifier() const;

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		identifier identifier_;
};

inline
bool
using_directive::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const boost::optional<const nested_name_specifier&>
using_directive::get_nested_name_specifier() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const identifier&
using_directive::get_identifier() const
{
	return identifier_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
