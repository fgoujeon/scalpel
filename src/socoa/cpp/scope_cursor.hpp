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
	private:
		class namespace_adder;
		class class_adder;
		class function_adder;
		class variable_adder;

	public:
		semantic_graph::scope&
		get_scope();

		void
		set_scope(semantic_graph::scope& a_scope);

		void
		add_to_current_scope(semantic_graph::namespace_&& o);

		void
		add_to_current_scope(semantic_graph::class_&& o);

		void
		add_to_current_scope(semantic_graph::function&& o);

		void
		add_to_current_scope(semantic_graph::variable&& o);

		void
		enter_last_added_scope();

		void
		leave_scope();

	private:
		semantic_graph::scope* current_scope_;
		semantic_graph::scope* last_added_scope_;
};

class scope_cursor::namespace_adder: public semantic_graph::scope_visitor
{
	public:
		namespace_adder(semantic_graph::namespace_&& n);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::namespace_ n_;
};

class scope_cursor::class_adder: public semantic_graph::scope_visitor
{
	public:
		class_adder(semantic_graph::class_&& c);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::class_ c_;
};

class scope_cursor::function_adder: public semantic_graph::scope_visitor
{
	public:
		function_adder(semantic_graph::function&& f);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::function f_;
};

class scope_cursor::variable_adder: public semantic_graph::scope_visitor
{
	public:
		variable_adder(semantic_graph::variable&& v);

		void
		visit(semantic_graph::namespace_& o);

		void
		visit(semantic_graph::class_& o);

		void
		visit(semantic_graph::function& o);

	private:
		semantic_graph::variable v_;
};

}} //namespace socoa::cpp

#endif
