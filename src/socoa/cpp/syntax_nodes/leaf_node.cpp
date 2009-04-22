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

#include "leaf_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

leaf_node::leaf_node(const std::string& raw_code):
	raw_code_(raw_code)
{
}

leaf_node::leaf_node(std::string&& raw_code):
	raw_code_(std::move(raw_code))
{
}

leaf_node::leaf_node(const leaf_node& n):
	raw_code_(n.raw_code_)
{
}

leaf_node::leaf_node(leaf_node&& n):
	raw_code_(std::move(n.raw_code_))
{
}

leaf_node::~leaf_node()
{
}

const std::string
leaf_node::raw_code() const
{
	return raw_code_;
}

void
leaf_node::raw_code(const std::string& code)
{
	raw_code_ = code;
}

void
leaf_node::raw_code(std::string&& code)
{
	raw_code_ = std::move(code);
}

}}} //namespace socoa::cpp::syntax_nodes
