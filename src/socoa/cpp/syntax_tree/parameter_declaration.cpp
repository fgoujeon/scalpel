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

#include "parameter_declaration.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

parameter_declaration::parameter_declaration
(
	decl_specifier_seq&& a_decl_specifier_seq,
	boost::optional<declarator>&& a_declarator,
	bool equal
):
	decl_specifier_seq_(a_decl_specifier_seq),
	declarator_(a_declarator),
	equal_(equal)
{
	update_node_list();
}

parameter_declaration::parameter_declaration(const parameter_declaration& o):
	composite_node(),
	decl_specifier_seq_(o.decl_specifier_seq_),
	declarator_(o.declarator_),
	equal_(o.equal_)
{
	update_node_list();
}

parameter_declaration::parameter_declaration(parameter_declaration&& o):
	decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
	declarator_(std::move(o.declarator_)),
	equal_(o.equal_)
{
	update_node_list();
}

const parameter_declaration&
parameter_declaration::operator=(const parameter_declaration& o)
{
	decl_specifier_seq_ = o.decl_specifier_seq_;
	declarator_ = o.declarator_;
	equal_ = o.equal_;
	update_node_list();

	return *this;
}

void
parameter_declaration::update_node_list()
{
	clear();
	add(decl_specifier_seq_);
	if(declarator_) add(*declarator_);
}

}}} //namespace socoa::cpp::syntax_tree
