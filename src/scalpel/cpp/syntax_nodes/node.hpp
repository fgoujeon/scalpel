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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NODE_HPP

#include <string>
#include <list>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

struct node
{
	typedef std::list<const node*> children_t;
	typedef children_t::const_iterator child_const_iterator;
	typedef boost::indirect_iterator<child_const_iterator, const node&> child_const_indirect_iterator;
	typedef boost::iterator_range<child_const_indirect_iterator> child_const_iterator_range;

	virtual
	~node(){};

	virtual
	child_const_iterator_range
	children() const = 0;

	virtual
	const std::string
	value() const = 0;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
