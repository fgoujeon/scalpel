/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/noncopyable.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class scope_cursor: public boost::noncopyable
{
	public:
		typedef std::vector<std::shared_ptr<semantic_entities::named_scope>> scopes_t;

		typedef scopes_t::const_iterator scope_const_iterator;
		typedef boost::indirect_iterator<scope_const_iterator, const std::shared_ptr<semantic_entities::named_scope>> scope_const_indirect_iterator;
		typedef boost::iterator_range<scope_const_indirect_iterator> scope_const_iterator_range;

		typedef scopes_t::iterator scope_iterator;
		typedef boost::iterator_range<scope_iterator> scope_iterator_range;

		scope_cursor();

		void
		initialize(std::shared_ptr<semantic_entities::named_scope> global_scope);

		scope_const_iterator_range
		scope_stack() const;

		scope_iterator_range
		scope_stack();

		scope_const_iterator_range
		global_scope_stack() const;

		scope_iterator_range
		global_scope_stack();

		std::shared_ptr<semantic_entities::named_scope>
		global_scope();

		std::shared_ptr<semantic_entities::named_scope>
		current_scope();

		void
		enter_scope(std::shared_ptr<semantic_entities::named_scope> a_scope);

		void
		enter_last_added_scope();

		void
		leave_scope();

	private:
		scopes_t scope_stack_;
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
