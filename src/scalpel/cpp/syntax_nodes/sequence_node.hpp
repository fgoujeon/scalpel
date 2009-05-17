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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SEQUENCE_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SEQUENCE_NODE_HPP

#include <memory>
#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class... NodesT>
class sequence_node;

template<>
class sequence_node<>: public composite_node
{
	public:
		sequence_node()
		{
		}

		sequence_node(const sequence_node&):
			composite_node()
		{
		}

		sequence_node(sequence_node&&):
			composite_node()
		{
		}

		virtual
		~sequence_node()
		{
		}
};

template<class HeadT, class... TailT>
class sequence_node<HeadT, TailT...>: public sequence_node<TailT...>
{
	private:
		typedef sequence_node<TailT...> tail_t;

	public:
		sequence_node(HeadT&& head_node, TailT&&... tail_nodes);

		sequence_node(HeadT&& head_node, sequence_node<TailT...>&& tail_sequence_node);

		sequence_node(const sequence_node& o);

		sequence_node(sequence_node&& o);

	protected:
		const tail_t&
		tail() const;

		tail_t&
		tail();

	private:
		HeadT node_;
};

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(HeadT&& head_node, TailT&&... tail_nodes):
	tail_t(tail_nodes...),
	node_(head_node)
{
	push_front(node_);
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(HeadT&& head_node, sequence_node<TailT...>&& tail_sequence_node):
	tail_t(tail_sequence_node),
	node_(head_node)
{
	push_front(node_);
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(const sequence_node<HeadT, TailT...>& o):
	tail_t(o.tail()),
	node_(o.node_)
{
	push_front(node_);
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(sequence_node<HeadT, TailT...>&& o):
	tail_t(std::move(o.tail())),
	node_(std::move(o.node_))
{
	push_front(node_);
}

template<class HeadT, class... TailT>
const typename sequence_node<HeadT, TailT...>::tail_t&
sequence_node<HeadT, TailT...>::tail() const
{
	return *this;
}

template<class HeadT, class... TailT>
typename sequence_node<HeadT, TailT...>::tail_t&
sequence_node<HeadT, TailT...>::tail()
{
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
