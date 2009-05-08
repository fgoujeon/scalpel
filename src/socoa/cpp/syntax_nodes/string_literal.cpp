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

#include "string_literal.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

string_literal::string_literal
(
	bool wide,
	std::string&& value
):
	wide_(wide),
	value_(value)
{
	update_node_list();
}

string_literal::string_literal(const string_literal& o):
	composite_node(),
	wide_(o.wide_),
	value_(o.value_)
{
	update_node_list();
}

string_literal::string_literal(string_literal&& o):
	composite_node(),
	wide_(std::move(o.wide_)),
	value_(std::move(o.value_))
{
	update_node_list();
}

const string_literal&
string_literal::operator=(const string_literal& o)
{
	wide_ = o.wide_;
	value_ = o.value_;

	update_node_list();

	return *this;
}

void
string_literal::update_node_list()
{
	clear();

	if(wide_) add(global_nodes::capital_l);
	add(global_nodes::double_quote);
	add(value_);
	add(global_nodes::double_quote);
}

}}} //namespace socoa::cpp::syntax_nodes

