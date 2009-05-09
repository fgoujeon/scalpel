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

#ifndef SCALPEL_CPP_SEMANTIC_GRAPH_HPP
#define SCALPEL_CPP_SEMANTIC_GRAPH_HPP

#include <memory>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include "semantic_entities/class_.hpp"
#include "semantic_entities/function.hpp"
#include "semantic_entities/namespace_.hpp"
#include "semantic_entities/statement_block.hpp"
#include "semantic_entities/variable.hpp"
#include "syntax_tree.hpp"

namespace scalpel { namespace cpp
{

class semantic_graph
{
	public:
		typedef std::vector<semantic_entities::scope*> scopes_t;
		typedef scopes_t::const_iterator scope_const_iterator;
		typedef boost::indirect_iterator<scope_const_iterator, const semantic_entities::scope&> scope_const_indirect_iterator;
		typedef boost::iterator_range<scope_const_indirect_iterator> scope_const_iterator_range;
		typedef scopes_t::const_reverse_iterator scope_const_reverse_iterator;
		typedef boost::indirect_iterator<scope_const_reverse_iterator, const semantic_entities::scope&> scope_const_reverse_indirect_iterator;
		typedef boost::iterator_range<scope_const_reverse_indirect_iterator> scope_const_reverse_iterator_range;

		semantic_graph();

		semantic_graph(const semantic_graph&) = delete;

		semantic_graph(semantic_graph&& o);

		const semantic_graph&
		operator=(const semantic_graph&) = delete;

		semantic_entities::namespace_&
		root_node();

		scope_const_iterator_range
		lastly_closed_scope_iterator() const;

		scope_const_reverse_iterator_range
		lastly_closed_scope_reverse_iterator() const;

		void
		lastly_closed_scopes(const scopes_t& scopes);

	private:
		std::unique_ptr<semantic_entities::namespace_> root_node_;
		scopes_t lastly_closed_scopes_;
};

}} //namespace scalpel::cpp

#endif
