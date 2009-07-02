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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ALTERNATIVE_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ALTERNATIVE_NODE_HPP

#include <boost/optional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class... NodesT>
class alternative_node;

template<>
class alternative_node<>: public composite_node
{
	public:
		typedef void head_node_t;
		typedef void tail_alternative_node_t;

		alternative_node()
		{
		}

		alternative_node(const alternative_node<>&):
			composite_node()
		{
		}

		alternative_node(alternative_node<>&&)
		{
		}

		const alternative_node&
		operator=(const alternative_node<>&)
		{
			clear();
			return *this;
		}

		void
		add(const node& n)
		{
			composite_node::add(n);
		}

	protected:
		void
		get() const{}

		void
		set_node(){}
};

template<class NodeT, class... NodesT>
class alternative_node<NodeT, NodesT...>: public node
{
	public:
		typedef alternative_node<NodeT, NodesT...> type;
		typedef NodeT head_node_t;
		typedef alternative_node<NodesT...> tail_alternative_node_t;

		/**
		 * Default constructor which does nothing (useful for internal use).
		 */
		alternative_node();

		/**
		 * Constructor.
		 */
		alternative_node(const NodeT& n);

		/**
		 * Constructor.
		 */
		alternative_node(NodeT& n);

		/**
		 * Constructor.
		 */
		alternative_node(NodeT&& n);

		/**
		 * Constructor.
		 */
		template<class NodeT2>
		alternative_node
		(
			const NodeT2& n,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_reference<NodeT2>::type,
					type
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Constructor.
		 */
		template<class NodeT2>
		alternative_node
		(
			NodeT2&& n,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_reference<NodeT2>::type,
					type
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Copy constructor.
		 */
		alternative_node(const type& n);

		/**
		 * Move constructor.
		 */
		alternative_node(type&& n);

		const type&
		operator=(const type& n);

		child_const_iterator_range
		children() const;

		void
		add(const node& n);

		const std::string
		value() const;

		//same type
		void
		get(boost::optional<const NodeT&>&) const;

		//different types
		template<class NodeT2>
		void
		get(boost::optional<const NodeT2&>&) const;

		//same type
		void
		set_node(const NodeT&);

		//different types
		template<class NodeT2>
		void
		set_node(const NodeT2&);

	private:
		boost::optional<head_node_t> head_;
		tail_alternative_node_t tail_;
};

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node()
{
	//does nothing
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(const NodeT& n):
	head_(n)
{
	if(head_) add(*head_);
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(NodeT& n):
	head_(n)
{
	if(head_) add(*head_);
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(NodeT&& n):
	head_(std::move(n))
{
	if(head_) add(*head_);
}

template<class NodeT, class... NodesT>
template<class NodeT2>
alternative_node<NodeT, NodesT...>::alternative_node
(
	const NodeT2& n,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_reference<NodeT2>::type,
			type
		>
	>::type*
):
	tail_(n)
{
}

template<class NodeT, class... NodesT>
template<class NodeT2>
alternative_node<NodeT, NodesT...>::alternative_node
(
	NodeT2&& n,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_reference<NodeT2>::type,
			type
		>
	>::type*
):
	tail_(std::move(n))
{
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(const alternative_node<NodeT, NodesT...>& n):
	head_(n.head_),
	tail_(n.tail_)
{
	if(head_)
	{
		tail_.add(*head_);
	}
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(alternative_node<NodeT, NodesT...>&& n):
	head_(std::move(n.head_)),
	tail_(std::move(n.tail_))
{
	if(head_)
	{
		tail_.add(*head_);
	}
}

template<class NodeT, class... NodesT>
const alternative_node<NodeT, NodesT...>&
alternative_node<NodeT, NodesT...>::operator=(const alternative_node<NodeT, NodesT...>& n)
{
	head_ = n.head_;
	if(head_)
	{
		tail_.add(*head_);
	}

	tail_ = n.tail_;

	return *this;
}

template<class NodeT, class... NodesT>
node::child_const_iterator_range
alternative_node<NodeT, NodesT...>::children() const
{
	return tail_.children();
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::add(const node& n)
{
	tail_.add(n);
}

template<class NodeT, class... NodesT>
const std::string
alternative_node<NodeT, NodesT...>::value() const
{
	return tail_.value();
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::get(boost::optional<const NodeT&>& node) const
{
	node = head_;
}

template<class NodeT, class... NodesT>
template<class NodeT2>
void
alternative_node<NodeT, NodesT...>::get(boost::optional<const NodeT2&>& node) const
{
	tail_.get(node);
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::set_node(const NodeT& node)
{
	head_ = node;
	if(head_) add(*head_);
}

template<class NodeT, class... NodesT>
template<class NodeT2>
void
alternative_node<NodeT, NodesT...>::set_node(const NodeT2& node)
{
	tail_.set_node(node);
}



template<class ReturnNodeT, class AlternativeNodeT>
boost::optional<const ReturnNodeT&>
get(const AlternativeNodeT* node)
{
	boost::optional<const ReturnNodeT&> return_node;
	node->get(return_node);
	return return_node;
}

template<class ReturnNodeT, class AlternativeNodeT>
boost::optional<const ReturnNodeT&>
get(boost::optional<const AlternativeNodeT&> node)
{
	boost::optional<const ReturnNodeT&> return_node;
	node->get(return_node);
	return return_node;
}



template<class AlternativeVisitorT, class T, class AlternativeNodeT, typename HeadNodeT>
struct private_visitor
{
	typedef typename AlternativeNodeT::head_node_t head_node_t;
	typedef typename AlternativeNodeT::tail_alternative_node_t tail_alternative_node_t;

	static
	void
	visit(const AlternativeVisitorT& alt_visitor, const T& alt_node)
	{
		boost::optional<const head_node_t&> node = get<head_node_t>(&alt_node);
		if(node)
		{
			alt_visitor(*node);
		}
		else
		{
			private_visitor
			<
				AlternativeVisitorT,
				T,
				tail_alternative_node_t,
				typename tail_alternative_node_t::head_node_t
			>::visit(alt_visitor, alt_node);
		}
	}
};

template<class AlternativeVisitorT, class T, class AlternativeNodeT>
struct private_visitor<AlternativeVisitorT, T, AlternativeNodeT, void>
{
	static
	void
	visit(const AlternativeVisitorT&, const T&)
	{
		//does nothing
	}
};

template<class AlternativeVisitorT, class AlternativeNodeT>
void
apply_visitor(const AlternativeVisitorT& alt_visitor, const AlternativeNodeT& node)
{
	private_visitor
	<
		AlternativeVisitorT,
		AlternativeNodeT,
		AlternativeNodeT,
		typename AlternativeNodeT::head_node_t
	>::visit(alt_visitor, node);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
