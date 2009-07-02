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

#include <string>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class... NodesT>
class sequence_node;

template<unsigned int I, class SequenceNodeT>
struct tail_sequence_node_getter;



template<>
class sequence_node<>
{
	public:
		typedef void head_node_t;
		typedef void tail_sequence_node_t;

		sequence_node();

		sequence_node(const sequence_node&);

		sequence_node(sequence_node&&);

		const sequence_node&
		operator=(const sequence_node&);
};

template<class HeadT, class... TailT>
class sequence_node<HeadT, TailT...>
{
	public:
		typedef HeadT head_node_t;
		typedef sequence_node<TailT...> tail_sequence_node_t;

		sequence_node(HeadT&& head_node, TailT&&... tail_nodes);

		sequence_node(HeadT&& head_node, sequence_node<TailT...>&& tail_sequence_node);

		sequence_node(const sequence_node& o);

		sequence_node(sequence_node&& o);

		const sequence_node&
		operator=(const sequence_node& o);

		const head_node_t&
		head() const;

		const tail_sequence_node_t&
		tail() const;

	private:
		head_node_t head_;
		tail_sequence_node_t tail_;
};

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(HeadT&& head_node, TailT&&... tail_nodes):
	head_(head_node),
	tail_(tail_nodes...)
{
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(HeadT&& head_node, sequence_node<TailT...>&& tail_sequence_node):
	head_(head_node),
	tail_(tail_sequence_node)
{
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(const sequence_node<HeadT, TailT...>& o):
	head_(o.head_),
	tail_(o.tail_)
{
}

template<class HeadT, class... TailT>
sequence_node<HeadT, TailT...>::sequence_node(sequence_node<HeadT, TailT...>&& o):
	head_(std::move(o.head_)),
	tail_(std::move(o.tail_))
{
}

template<class HeadT, class... TailT>
const sequence_node<HeadT, TailT...>&
sequence_node<HeadT, TailT...>::operator=(const sequence_node& o)
{
	head_ = o.head_;
	tail_ = o.tail_;
	return *this;
}

template<class HeadT, class... TailT>
const HeadT&
sequence_node<HeadT, TailT...>::head() const
{
	return head_;
}

template<class HeadT, class... TailT>
const typename sequence_node<HeadT, TailT...>::tail_sequence_node_t&
sequence_node<HeadT, TailT...>::tail() const
{
	return tail_;
}



template<class SequenceNodeT>
struct tail_sequence_node_getter<0, SequenceNodeT>
{
	typedef SequenceNodeT type;
	typedef typename SequenceNodeT::head_node_t head_node_t;
	typedef typename SequenceNodeT::tail_sequence_node_t tail_sequence_node_t;

	static
	const type&
	get_tail(const SequenceNodeT& sequence)
	{
		return sequence;
	}
};

template<unsigned int I, class SequenceNodeT>
struct tail_sequence_node_getter
{
	typedef typename tail_sequence_node_getter<I - 1, SequenceNodeT>::tail_sequence_node_t type;
	typedef typename type::head_node_t head_node_t;
	typedef typename type::tail_sequence_node_t tail_sequence_node_t;

	static
	const type&
	get_tail(const SequenceNodeT& sequence)
	{
		return tail_sequence_node_getter<I - 1, SequenceNodeT>::get_tail(sequence).tail();
	}
};



template<unsigned int I, class SequenceNodeT>
const typename tail_sequence_node_getter<I, SequenceNodeT>::head_node_t&
get(const SequenceNodeT& sequence)
{
	//get the tail sequence node whose head node type is the return type
	const typename tail_sequence_node_getter<I, SequenceNodeT>::type& tail = tail_sequence_node_getter<I, SequenceNodeT>::get_tail(sequence);

	return tail.head();
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
