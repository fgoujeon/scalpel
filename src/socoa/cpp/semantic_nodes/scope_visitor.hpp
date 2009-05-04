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

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_VISITOR_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_VISITOR_HPP

namespace socoa { namespace cpp { namespace semantic_nodes
{

class namespace_;
class class_;
class function;
class statement_block;

struct scope_visitor
{
	virtual
	~scope_visitor(){}

	virtual
	void
	visit(namespace_&) = 0;

	virtual
	void
	visit(class_&) = 0;

	virtual
	void
	visit(function&) = 0;

	virtual
	void
	visit(statement_block&) = 0;
};

}}} //namespace socoa::cpp::semantic_nodes

#endif
