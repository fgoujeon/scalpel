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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INCOMPLETE_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INCOMPLETE_NODE_HPP

#include <memory>
#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class T, class WrapperT>
class incomplete_node: public composite_node
{
    public:
        incomplete_node(T&& node);

        incomplete_node(const incomplete_node& o);

        incomplete_node(incomplete_node&& o);

        const incomplete_node&
		operator=(const incomplete_node& o);

		const incomplete_node&
		operator=(incomplete_node&& o);

		const T&
		node() const;

	private:
		void
		update_node_list();

		WrapperT wrapper_;
};

template<class T, class WrapperT>
incomplete_node<T, WrapperT>::incomplete_node(T&& node):
	wrapper_(std::move(node))
{
}

template<class T, class WrapperT>
incomplete_node<T, WrapperT>::incomplete_node(const incomplete_node& o):
	composite_node(),
	wrapper_(o.wrapper_)
{
	update_node_list();
}

template<class T, class WrapperT>
incomplete_node<T, WrapperT>::incomplete_node(incomplete_node&& o):
	composite_node(),
	wrapper_(std::move(o.wrapper_))
{
	update_node_list();
}

template<class T, class WrapperT>
const incomplete_node<T, WrapperT>&
incomplete_node<T, WrapperT>::operator=(const incomplete_node& o)
{
	incomplete_node<T, WrapperT> copy(o);
	std::swap(copy, *this);
	return *this;
}

template<class T, class WrapperT>
const incomplete_node<T, WrapperT>&
incomplete_node<T, WrapperT>::operator=(incomplete_node&& o)
{
	wrapper_ = std::move(o.wrapper_);
	update_node_list();
	return *this;
}

template<class T, class WrapperT>
const T&
incomplete_node<T, WrapperT>::node() const
{
	return wrapper_.node();
}

template<class T, class WrapperT>
void
incomplete_node<T, WrapperT>::update_node_list()
{
	clear();
	add(wrapper_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
