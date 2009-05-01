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

#ifndef SOCOA_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP
#define SOCOA_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP

#include <boost/noncopyable.hpp>
#include <vector>
#include "../../semantic_nodes/scope.hpp"
#include "../../semantic_nodes/scope_visitor.hpp"
#include "../../semantic_nodes/namespace_.hpp"
#include "../../semantic_nodes/class_.hpp"
#include "../../semantic_nodes/function.hpp"

namespace socoa { namespace cpp { namespace detail { namespace semantic_analysis
{

class scope_cursor: public boost::noncopyable
{
	private:
		class namespace_adder;
		class class_adder;
		class function_adder;
		class variable_adder;

	public:
		scope_cursor();

		void
		initialize(semantic_nodes::scope& a_scope);

		semantic_nodes::scope&
		get_global_scope();

		semantic_nodes::scope&
		get_current_scope();

		void
		add_to_current_scope(semantic_nodes::namespace_&& o);

		void
		add_to_current_scope(semantic_nodes::class_&& o);

		void
		add_to_current_scope(semantic_nodes::function&& o);

		void
		add_to_current_scope(semantic_nodes::variable&& o);

		void
		enter_scope(semantic_nodes::scope& a_scope);

		void
		enter_last_added_scope();

		void
		leave_scope();

		const std::vector<semantic_nodes::scope*>&
		lastly_leaved_scopes() const;

	private:
		semantic_nodes::scope* global_scope_;
		semantic_nodes::scope* current_scope_;
		semantic_nodes::scope* last_added_scope_;
		std::vector<semantic_nodes::scope*> lastly_leaved_scopes_;
};

class scope_cursor::namespace_adder: public semantic_nodes::scope_visitor
{
	public:
		namespace_adder(semantic_nodes::namespace_&& n);

		void
		visit(semantic_nodes::namespace_& o);

		void
		visit(semantic_nodes::class_& o);

		void
		visit(semantic_nodes::function& o);

	private:
		semantic_nodes::namespace_ n_;
};

class scope_cursor::class_adder: public semantic_nodes::scope_visitor
{
	public:
		class_adder(semantic_nodes::class_&& c);

		void
		visit(semantic_nodes::namespace_& o);

		void
		visit(semantic_nodes::class_& o);

		void
		visit(semantic_nodes::function& o);

	private:
		semantic_nodes::class_ c_;
};

class scope_cursor::function_adder: public semantic_nodes::scope_visitor
{
	public:
		function_adder(semantic_nodes::function&& f);

		void
		visit(semantic_nodes::namespace_& o);

		void
		visit(semantic_nodes::class_& o);

		void
		visit(semantic_nodes::function& o);

	private:
		semantic_nodes::function f_;
};

class scope_cursor::variable_adder: public semantic_nodes::scope_visitor
{
	public:
		variable_adder(semantic_nodes::variable&& v);

		void
		visit(semantic_nodes::namespace_& o);

		void
		visit(semantic_nodes::class_& o);

		void
		visit(semantic_nodes::function& o);

	private:
		semantic_nodes::variable v_;
};

}}}} //namespace socoa::cpp::detail::semantic_analysis

#endif
