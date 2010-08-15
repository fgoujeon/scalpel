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

#ifndef SCALPEL_UTILITY_VARIANT_HPP
#define SCALPEL_UTILITY_VARIANT_HPP

#include <boost/optional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace utility
{

template<class... NodesT>
class variant;

template<>
class variant<>
{
	public:
		typedef void head_node_t;
		typedef void tail_variant_t;
};

template<class NodeT, class... NodesT>
class variant<NodeT, NodesT...>
{
	public:
		typedef variant<NodeT, NodesT...> type;
		typedef NodeT head_node_t;
		typedef variant<NodesT...> tail_variant_t;

		/**
		 * Default constructor which does nothing (useful for internal use).
		 */
		variant();

		/**
		 * Constructor.
		 */
		variant(const NodeT& n);

		/**
		 * Constructor.
		 */
		variant(NodeT& n);

		/**
		 * Constructor.
		 */
		variant(NodeT&& n);

		/**
		 * Constructor.
		 */
		template<class NodeT2>
		variant
		(
			const NodeT2& n,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<NodeT2>::type,
					type
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Constructor.
		 */
		template<class NodeT2>
		variant
		(
			NodeT2&& n,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<NodeT2>::type,
					type
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Copy constructor.
		 */
		variant(const type& n);

		/**
		 * Copy constructor.
		 */
		variant(type& n);

		/**
		 * Move constructor.
		 */
		variant(type&& n);

		const type&
		operator=(const type& n);

		const tail_variant_t&
		tail() const;

		//same type
		void
		get(boost::optional<const NodeT&>&) const;

		//different types
		template<class NodeT2>
		void
		get(boost::optional<const NodeT2&>&) const;

		//same type
		void
		set(const NodeT&);

		//different types
		template<class NodeT2>
		void
		set(const NodeT2&);

	private:
		boost::optional<head_node_t> head_;
		tail_variant_t tail_;
};

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant()
{
	//does nothing
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(const NodeT& n):
	head_(n)
{
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(NodeT& n):
	head_(n)
{
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(NodeT&& n):
	head_(std::move(n))
{
}

template<class NodeT, class... NodesT>
template<class NodeT2>
variant<NodeT, NodesT...>::variant
(
	const NodeT2& n,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<NodeT2>::type,
			type
		>
	>::type*
):
	tail_(n)
{
}

template<class NodeT, class... NodesT>
template<class NodeT2>
variant<NodeT, NodesT...>::variant
(
	NodeT2&& n,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<NodeT2>::type,
			type
		>
	>::type*
):
	tail_(std::move(n))
{
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(const variant<NodeT, NodesT...>& n):
	head_(n.head_),
	tail_(n.tail_)
{
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(variant<NodeT, NodesT...>& n):
	head_(n.head_),
	tail_(n.tail_)
{
}

template<class NodeT, class... NodesT>
variant<NodeT, NodesT...>::variant(variant<NodeT, NodesT...>&& n):
	head_(std::move(n.head_)),
	tail_(std::move(n.tail_))
{
}

template<class NodeT, class... NodesT>
const variant<NodeT, NodesT...>&
variant<NodeT, NodesT...>::operator=(const variant<NodeT, NodesT...>& n)
{
	type copy(n);
	std::swap(copy, *this);
	return *this;
}

template<class NodeT, class... NodesT>
const typename variant<NodeT, NodesT...>::tail_variant_t&
variant<NodeT, NodesT...>::tail() const
{
	return tail_;
}

template<class NodeT, class... NodesT>
void
variant<NodeT, NodesT...>::get(boost::optional<const NodeT&>& node) const
{
	node = head_;
}

template<class NodeT, class... NodesT>
template<class NodeT2>
void
variant<NodeT, NodesT...>::get(boost::optional<const NodeT2&>& node) const
{
	tail_.get(node);
}

template<class NodeT, class... NodesT>
void
variant<NodeT, NodesT...>::set(const NodeT& node)
{
	head_ = node;
}

template<class NodeT, class... NodesT>
template<class NodeT2>
void
variant<NodeT, NodesT...>::set(const NodeT2& node)
{
	tail_.set(node);
}



template<class ReturnNodeT, class VariantT>
boost::optional<const ReturnNodeT&>
get(const VariantT* node)
{
	boost::optional<const ReturnNodeT&> return_node;
	node->get(return_node);
	return return_node;
}



template<class VariantVisitorT, class T, class VariantT, typename HeadNodeT>
struct private_visitor
{
	typedef typename VariantT::head_node_t head_node_t;
	typedef typename VariantT::tail_variant_t tail_variant_t;

	static
	void
	visit(const VariantVisitorT& alt_visitor, const T& alt_node)
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
				VariantVisitorT,
				T,
				tail_variant_t,
				typename tail_variant_t::head_node_t
			>::visit(alt_visitor, alt_node);
		}
	}
};

template<class VariantVisitorT, class T, class VariantT>
struct private_visitor<VariantVisitorT, T, VariantT, void>
{
	static
	void
	visit(const VariantVisitorT&, const T&)
	{
		//does nothing
	}
};

template<class VariantVisitorT, class VariantT>
void
apply_visitor(const VariantVisitorT& alt_visitor, const VariantT& node)
{
	private_visitor
	<
		VariantVisitorT,
		VariantT,
		VariantT,
		typename VariantT::head_node_t
	>::visit(alt_visitor, node);
}

}} //namespace scalpel::utility

#endif
