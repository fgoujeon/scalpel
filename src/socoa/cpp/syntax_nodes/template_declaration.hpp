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

#ifndef SOCOA_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP

#include <memory>
#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class declaration;

class template_declaration: public composite_node
{
	public:
		template_declaration
		(
			bool export_keyword,
			//template_parameter_list m_template_parameter_list;
			declaration&& a_declaration
		);

		template_declaration(const template_declaration& o);

		template_declaration(template_declaration&& o);

		const template_declaration&
		operator=(const template_declaration& o);

		inline
		bool
		has_export_keyword() const;

		inline
		const declaration&
		declaration_node() const;

	private:
		void
		update_node_list();

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
const declaration&
template_declaration::declaration_node() const
{
	return *declaration_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
