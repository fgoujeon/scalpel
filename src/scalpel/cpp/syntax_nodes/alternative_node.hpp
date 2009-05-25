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

	protected:
		alternative_node():
		   	initialized_(false)
		{
		}

	public:
		alternative_node(const alternative_node<>&):
			composite_node(),
			initialized_(false)
		{
		}

		alternative_node(alternative_node<>&&):
			initialized_(false)
		{
		}

		const alternative_node&
		operator=(const alternative_node<>&)
		{
			clear();
			return *this;
		}

		bool
		initialized() const
		{
			return initialized_;
		}

	protected:
		void
		get() const{}

		void
		set_node(){}

		void
		initialized(bool b)
		{
			initialized_ = b;
		}

	private:
		bool initialized_;
};

template<class NodeT, class... NodesT>
class alternative_node<NodeT, NodesT...>: public alternative_node<NodesT...>
{
	public:
		typedef NodeT head_node_t;
		typedef alternative_node<NodesT...> tail_alternative_node_t;

	protected:
		/**
		 * Default constructor which does nothing (useful for internal use).
		 */
		alternative_node();

	public:
		/**
		 * Copy constructor.
		 */
		alternative_node(const alternative_node<NodeT, NodesT...>& n);

		/**
		 * Copy constructor.
		 */
		alternative_node(alternative_node<NodeT, NodesT...>& n);

		/**
		 * Move constructor.
		 */
		alternative_node(alternative_node<NodeT, NodesT...>&& n);

		/**
		 * Constructor. Must be placed after move constructor, otherwise
		 * this constructor will be chosen for move construction.
		 */
		template<class NodeT2>
		alternative_node(NodeT2&&);

		const alternative_node<NodeT, NodesT...>&
		operator=(const alternative_node<NodeT, NodesT...>& n);

		void
		get(boost::optional<const NodeT&>&) const;

		using alternative_node<NodesT...>::get;

		void
		set_node(const NodeT&);

		using alternative_node<NodesT...>::set_node;

	private:
		boost::optional<NodeT> node_;
};

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node()
{
	//does nothing
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(const alternative_node<NodeT, NodesT...>& n):
	alternative_node<NodesT...>(static_cast<const alternative_node<NodesT...>&>(n)),
	node_(n.node_)
{
	if(node_)
	{
		add(*node_);
		alternative_node<>::initialized(true);
	}
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(alternative_node<NodeT, NodesT...>& n):
	alternative_node<NodesT...>(static_cast<alternative_node<NodesT...>&>(n)),
	node_(n.node_)
{
	if(node_)
	{
		add(*node_);
		alternative_node<>::initialized(true);
	}
}

template<class NodeT, class... NodesT>
alternative_node<NodeT, NodesT...>::alternative_node(alternative_node<NodeT, NodesT...>&& n):
	alternative_node<NodesT...>(static_cast<alternative_node<NodesT...>&&>(n)),
	node_(n.node_)
{
	if(node_)
	{
		add(*node_);
		alternative_node<>::initialized(true);
	}
}

template<class NodeT, class... NodesT>
template<class NodeT2>
alternative_node<NodeT, NodesT...>::alternative_node(NodeT2&& node):
	alternative_node<NodesT...>()
{
	set_node(node);
}

template<class NodeT, class... NodesT>
const alternative_node<NodeT, NodesT...>&
alternative_node<NodeT, NodesT...>::operator=(const alternative_node<NodeT, NodesT...>& n)
{
	alternative_node<NodesT...>::operator=(static_cast<const alternative_node<NodesT...>&>(n));

	node_ = n.node_;
	if(node_)
	{
		add(*node_);
		alternative_node<>::initialized(true);
	}

	return *this;
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::get(boost::optional<const NodeT&>& node) const
{
	node = node_;
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::set_node(const NodeT& node)
{
	node_ = node;
	if(node_) add(*node_);
	alternative_node<>::initialized(true);
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
