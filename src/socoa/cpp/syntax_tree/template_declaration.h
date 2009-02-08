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

#ifndef SOCOA_CPP_SYNTAX_TREE_TEMPLATE_DECLARATION_H
#define SOCOA_CPP_SYNTAX_TREE_TEMPLATE_DECLARATION_H

#include <memory>
#include "visitor.h"
#include "declaration.h"
#include "member_declaration.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class template_declaration: public declaration, public member_declaration
{
	public:
		template_declaration
		(
			bool export_keyword,
			//template_parameter_list m_template_parameter_list;
			std::shared_ptr<declaration> a_declaration
		);

		inline
		bool
		has_export_keyword() const;

		inline
		const std::shared_ptr<const declaration>
		get_declaration() const;

		SOCOA_CPP_DEFINE_VISITABLE()

	private:
		bool export_keyword_;
		//template_parameter_list m_template_parameter_list;
		std::shared_ptr<declaration> declaration_;
};

inline
bool
template_declaration::has_export_keyword() const
{
	return export_keyword_;
}

inline
const std::shared_ptr<const declaration>
template_declaration::get_declaration() const
{
	return declaration_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
