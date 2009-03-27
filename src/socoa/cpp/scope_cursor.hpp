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

#ifndef SOCOA_CPP_SCOPE_CURSOR_HPP
#define SOCOA_CPP_SCOPE_CURSOR_HPP

#include "semantic_graph/scope.hpp"
#include "semantic_graph/scope_visitor.hpp"
#include "semantic_graph/namespace_.hpp"
#include "semantic_graph/class_.hpp"
#include "semantic_graph/function.hpp"

namespace socoa { namespace cpp
{

class scope_cursor
{
	public:
		class scope_visitor_namespace;
		class scope_visitor_class;
		class scope_visitor_function;

		semantic_graph::scope&
		get_scope();

		void
		set_scope(semantic_graph::scope& a_scope);

		void
		add_to_scope(semantic_graph::namespace_&& o);

		void
		add_to_scope(semantic_graph::class_&& o);

		void
		add_to_scope(semantic_graph::function&& o);

	private:
		semantic_graph::scope* scope_;
};

class scope_cursor::scope_visitor_namespace: public semantic_graph::scope_visitor
{
	public:
		scope_visitor_namespace(semantic_graph::namespace_&& n);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::namespace_ n_;
};

class scope_cursor::scope_visitor_class: public semantic_graph::scope_visitor
{
	public:
		scope_visitor_class(semantic_graph::class_&& c);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::class_ c_;
};

class scope_cursor::scope_visitor_function: public semantic_graph::scope_visitor
{
	public:
		scope_visitor_function(semantic_graph::function&& f);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::function f_;
};

}} //namespace socoa::cpp

#endif
