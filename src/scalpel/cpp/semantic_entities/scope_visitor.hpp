/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_SCOPE_VISITOR_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_SCOPE_VISITOR_HPP

namespace scalpel { namespace cpp { namespace semantic_entities
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

}}} //namespace scalpel::cpp::semantic_entities

#endif
