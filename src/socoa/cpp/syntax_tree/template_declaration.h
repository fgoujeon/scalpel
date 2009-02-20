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

namespace socoa { namespace cpp { namespace syntax_tree
{

class template_declaration_impl;
class declaration;

class template_declaration
{
	public:
		template_declaration
		(
			bool export_keyword,
			//template_parameter_list m_template_parameter_list;
			declaration&& a_declaration
		);

		~template_declaration();

		bool
		has_export_keyword() const;

		const declaration&
		get_declaration() const;

	private:
		template_declaration_impl* pimpl_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
