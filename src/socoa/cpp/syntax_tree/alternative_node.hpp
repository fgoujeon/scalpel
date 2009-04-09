/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_TREE_ALTERNATIVE_NODE_HPP
#define SOCOA_CPP_SYNTAX_TREE_ALTERNATIVE_NODE_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

template<class T>
void
assign_if_same_type(boost::optional<T>& t1, const T& t2)
{
	t1 = t2;
}

template<class T1, class T2>
void
assign_if_same_type(T1&, T2&)
{
	//does nothing
}


template<class... NodesT>
class alternative_node;


template<>
class alternative_node<>: public composite_node
{
	public:
		template<class NodeT2>
		alternative_node(const NodeT2&){};

		virtual
		~alternative_node(){};

		void
		get_node() const{};
};


template<class NodeT, class... NodesT>
class alternative_node<NodeT, NodesT...>: public alternative_node<NodesT...>
{
	public:
		template<class NodeT2>
		alternative_node(const NodeT2&);

		~alternative_node(){};

	protected:
		void
		get_node(boost::optional<const NodeT&>&) const;

		using alternative_node<NodesT...>::get_node;

		template<class ReturnNodeT, class AlternativeNodeT>
		friend
		boost::optional<const ReturnNodeT&>
		get(const AlternativeNodeT* node);

		template<class ReturnNodeT, class AlternativeNodeT>
		friend
		boost::optional<const ReturnNodeT&>
		get(boost::optional<const AlternativeNodeT&> node);

	private:
		boost::optional<NodeT> node_;
};

template<class NodeT, class... NodesT>
template<class NodeT2>
alternative_node<NodeT, NodesT...>::alternative_node(const NodeT2& node):
	alternative_node<NodesT...>(node)
{
	assign_if_same_type(node_, node);
}

template<class NodeT, class... NodesT>
void
alternative_node<NodeT, NodesT...>::get_node(boost::optional<const NodeT&>& node) const
{
	node = node_;
}


template<class ReturnNodeT, class AlternativeNodeT>
boost::optional<const ReturnNodeT&>
get(const AlternativeNodeT* node)
{
	boost::optional<const ReturnNodeT&> return_node;
	node->get_node(return_node);
	return return_node;
}

template<class ReturnNodeT, class AlternativeNodeT>
boost::optional<const ReturnNodeT&>
get(boost::optional<const AlternativeNodeT&> node)
{
	boost::optional<const ReturnNodeT&> return_node;
	node->get_node(return_node);
	return return_node;
}


template<class AlternativeVisitorT, class AlternativeNodeT, class... NodesT>
class private_visitor;

template<class AlternativeVisitorT, class AlternativeNodeT>
class private_visitor<AlternativeVisitorT, AlternativeNodeT>
{
	public:
		static
		void
		visit(const AlternativeVisitorT&, const AlternativeNodeT&)
		{
			//does nothing
		}
};

template<class AlternativeVisitorT, class AlternativeNodeT, class NodeT, class... NodesT>
class private_visitor<AlternativeVisitorT, AlternativeNodeT, NodeT, NodesT...>
{
	public:
		static
		void
		visit(const AlternativeVisitorT& alt_visitor, const AlternativeNodeT& alt_node)
		{
			boost::optional<const NodeT&> node = get<NodeT>(&alt_node);
			if(node)
			{
				alt_visitor(*node);
			}
			else
			{
				private_visitor<AlternativeVisitorT, AlternativeNodeT, NodesT...>::visit(alt_visitor, alt_node);
			}
		}
};

template<class AlternativeVisitorT, class... NodesT>
void
apply_visitor(const AlternativeVisitorT& alt_visitor, const alternative_node<NodesT...>& node)
{
	private_visitor<AlternativeVisitorT, alternative_node<NodesT...>, NodesT...>::visit(alt_visitor, node);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
