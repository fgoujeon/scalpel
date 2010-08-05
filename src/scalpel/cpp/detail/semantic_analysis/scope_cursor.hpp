/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SCOPE_CURSOR_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <boost/noncopyable.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class scope_cursor: public boost::noncopyable
{
	public:
		typedef utility::shared_ptr_vector<semantic_entities::scope> scopes_t;

		scope_cursor();

		void
		initialize(std::shared_ptr<semantic_entities::scope> global_scope);

		scopes_t::const_range
		scope_stack() const;

		scopes_t::range
		scope_stack();

		/*
		scopes_t::const_range
		global_scope_stack() const;

		scopes_t::range
		global_scope_stack();
		*/

		std::shared_ptr<semantic_entities::scope>
		global_scope();

		std::shared_ptr<semantic_entities::scope>
		current_scope();

		void
		enter_scope(std::shared_ptr<semantic_entities::scope> a_scope);

		void
		enter_last_added_scope();

		void
		leave_scope();

	private:
		scopes_t scope_stack_;
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
