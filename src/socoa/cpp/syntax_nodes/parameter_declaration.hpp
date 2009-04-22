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

#ifndef SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "declarator.hpp"
#include "decl_specifier_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
parameter_declaration
	= decl_specifier_seq >> !s >> declarator >> !s >> '=' >> !s >> assignment_expression
	| decl_specifier_seq >> !s >> declarator
	| decl_specifier_seq >> !s >> abstract_declarator >> !s >> '=' >> !s >> assignment_expression
	| decl_specifier_seq >> !(!s >> abstract_declarator)
	| decl_specifier_seq >> !s >> '=' >> !s >> assignment_expression
;
\endverbatim
*/
class parameter_declaration: public composite_node
{
	public:
		parameter_declaration
		(
			decl_specifier_seq&& a_decl_specifier_seq,
			boost::optional<space>&& pre_declarator_space_node,
			boost::optional<declarator>&& a_declarator,
			bool equal
		);

		parameter_declaration(const parameter_declaration& o);

		parameter_declaration(parameter_declaration&& o);

		const parameter_declaration&
		operator=(const parameter_declaration& o);

		inline
		const decl_specifier_seq&
		get_decl_specifier_seq() const;

		inline
		const boost::optional<const declarator&>
		get_declarator() const;

		inline
		bool
		has_equal() const;

	private:
		void
		update_node_list();

		decl_specifier_seq decl_specifier_seq_;
		boost::optional<space> pre_declarator_space_node_; //before declarator or before abstract_declarator
		boost::optional<declarator> declarator_;
		bool equal_;
};

inline
const decl_specifier_seq&
parameter_declaration::get_decl_specifier_seq() const
{
	return decl_specifier_seq_;
}

inline
const boost::optional<const declarator&>
parameter_declaration::get_declarator() const
{
	return boost::optional<const declarator&>(declarator_);
}

inline
bool
parameter_declaration::has_equal() const
{
	return equal_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
