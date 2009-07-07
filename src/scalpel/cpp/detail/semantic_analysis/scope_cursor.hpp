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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class scope_cursor: public boost::noncopyable
{
	private:
		class namespace_adder;
		class class_adder;
		class function_adder;
		class statement_block_adder;
		class variable_adder;

	public:
		typedef std::vector<semantic_entities::scope*> scopes_t;

		typedef scopes_t::const_iterator scope_const_iterator;
		typedef boost::indirect_iterator<scope_const_iterator, const semantic_entities::scope&> scope_const_indirect_iterator;
		typedef boost::iterator_range<scope_const_indirect_iterator> scope_const_iterator_range;

		typedef scopes_t::iterator scope_iterator;
		typedef boost::indirect_iterator<scope_iterator, semantic_entities::scope&> scope_indirect_iterator;
		typedef boost::iterator_range<scope_indirect_iterator> scope_iterator_range;

		scope_cursor();

		void
		initialize(semantic_entities::scope& global_scope);

		scope_const_iterator_range
		scope_stack() const;

		scope_iterator_range
		scope_stack();

		scope_const_iterator_range
		global_scope_stack() const;

		scope_iterator_range
		global_scope_stack();

		semantic_entities::scope&
		global_scope();

		semantic_entities::scope&
		current_scope();

		void
		add_to_current_scope(semantic_entities::namespace_&& o);

		void
		add_to_current_scope(semantic_entities::class_&& o);

		void
		add_to_current_scope(semantic_entities::function&& o);

		void
		add_to_current_scope(semantic_entities::statement_block&& o);

		void
		add_to_current_scope(semantic_entities::variable&& o);

		void
		enter_scope(semantic_entities::scope& a_scope);

		void
		enter_last_added_scope();

		void
		leave_scope();

	private:
		scopes_t scope_stack_;
};

class scope_cursor::namespace_adder: public semantic_entities::scope_visitor
{
	public:
		namespace_adder(semantic_entities::namespace_&& o);

		void
		visit(semantic_entities::namespace_& scope);

		void
		visit(semantic_entities::class_& scope);

		void
		visit(semantic_entities::function& scope);

		void
		visit(semantic_entities::statement_block& scope);

	private:
		semantic_entities::namespace_ o_;
};

class scope_cursor::class_adder: public semantic_entities::scope_visitor
{
	public:
		class_adder(semantic_entities::class_&& o);

		void
		visit(semantic_entities::namespace_& scope);

		void
		visit(semantic_entities::class_& scope);

		void
		visit(semantic_entities::function& scope);

		void
		visit(semantic_entities::statement_block& scope);

	private:
		semantic_entities::class_ o_;
};

class scope_cursor::function_adder: public semantic_entities::scope_visitor
{
	public:
		function_adder(semantic_entities::function&& o);

		void
		visit(semantic_entities::namespace_& scope);

		void
		visit(semantic_entities::class_& scope);

		void
		visit(semantic_entities::function& scope);

		void
		visit(semantic_entities::statement_block& scope);

	private:
		semantic_entities::function o_;
};

class scope_cursor::statement_block_adder: public semantic_entities::scope_visitor
{
	public:
		statement_block_adder(semantic_entities::statement_block&& o);

		void
		visit(semantic_entities::namespace_& scope);

		void
		visit(semantic_entities::class_& scope);

		void
		visit(semantic_entities::function& scope);

		void
		visit(semantic_entities::statement_block& scope);

	private:
		semantic_entities::statement_block o_;
};

class scope_cursor::variable_adder: public semantic_entities::scope_visitor
{
	public:
		variable_adder(semantic_entities::variable&& o);

		void
		visit(semantic_entities::namespace_& scope);

		void
		visit(semantic_entities::class_& scope);

		void
		visit(semantic_entities::function& scope);

		void
		visit(semantic_entities::statement_block& scope);

	private:
		semantic_entities::variable o_;
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
