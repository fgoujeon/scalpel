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

#ifndef SOCOA_CPP_SYNTAX_TREE_TEMPLATE_DECLARATION_IMPL_H
#define SOCOA_CPP_SYNTAX_TREE_TEMPLATE_DECLARATION_IMPL_H

#include "declaration.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class template_declaration_impl
{
	public:
		template_declaration_impl
		(
			bool export_keyword,
			//template_parameter_list m_template_parameter_list;
			declaration&& a_declaration
		);

		inline
		bool
		has_export_keyword() const;

		inline
		const declaration&
		get_declaration() const;

	private:
		bool export_keyword_;
		//template_parameter_list m_template_parameter_list;
		declaration declaration_;
};

inline
bool
template_declaration_impl::has_export_keyword() const
{
	return export_keyword_;
}

inline
const declaration&
template_declaration_impl::get_declaration() const
{
	return declaration_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
