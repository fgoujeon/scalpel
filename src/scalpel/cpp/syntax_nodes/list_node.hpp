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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LIST_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LIST_NODE_HPP

#include "space.hpp"
#include "common_nodes.hpp"
#include "optional_node.hpp"
#include <vector>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class T, const leaf_node& SeparatorNode = common_nodes::empty>
class list_node
{
    public:
		class item;

		typedef std::vector<item> items_t;
		typedef T type;
		typedef typename items_t::const_iterator const_iterator;

        list_node();

        list_node(const list_node& s);

        list_node(list_node&& s);

        const list_node&
		operator=(const list_node& s);

		const list_node&
		operator=(list_node&& s);

		bool
		empty() const
		{
			return items_.empty();
		}

		typename items_t::size_type
		size() const
		{
			return items_.size();
		}

		const_iterator
		begin() const
		{
			return items_.begin();
		}

		const_iterator
		end() const
		{
			return items_.end();
		}

		const item&
		front() const
		{
			return items_.front();
		}

		void
		push_back(const item& t)
		{
			items_.push_back(t);
		}

		void
		push_back(item&& t)
		{
			items_.push_back(std::move(t));
		}

		static const leaf_node& separator_node;

	private:
		items_t items_;
};

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::list_node()
{
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::list_node(const list_node& s):
	items_(s.items_)
{
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::list_node(list_node&& s):
	items_(std::move(s.items_))
{
}

template<class T, const leaf_node& SeparatorNode>
const list_node<T, SeparatorNode>&
list_node<T, SeparatorNode>::operator=(const list_node& s)
{
	items_ = s.items_;
	return *this;
}

template<class T, const leaf_node& SeparatorNode>
const list_node<T, SeparatorNode>&
list_node<T, SeparatorNode>::operator=(list_node&& s)
{
	items_ = std::move(s.items_);
	return *this;
}

template<class T, const leaf_node& SeparatorNode>
const leaf_node&
list_node<T, SeparatorNode>::separator_node = SeparatorNode;



template<class T, const leaf_node& SeparatorNode = common_nodes::empty>
class list_node<T, SeparatorNode>::item
{
	public:
		item
		(
			optional_node<space>&& pre_separator_space,
			optional_node<space>&& post_separator_space,
			const T& main_node
		);

		item
		(
			optional_node<space>&& pre_separator_space,
			optional_node<space>&& post_separator_space,
			T&& main_node
		);

		item(const item& i);

		const item&
		operator=(const item& i);

		const optional_node<space>&
		pre_separator_space_node() const;

		const optional_node<space>&
		post_separator_space_node() const;

		const T&
		main_node() const;

	private:
		optional_node<space> pre_separator_space_;
		optional_node<space> post_separator_space_;
		T main_node_;
};

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::item::item
(
	optional_node<space>&& pre_separator_space,
	optional_node<space>&& post_separator_space,
	T&& main_node
):
	pre_separator_space_(pre_separator_space),
	post_separator_space_(post_separator_space),
	main_node_(main_node)
{
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::item::item
(
	optional_node<space>&& pre_separator_space,
	optional_node<space>&& post_separator_space,
	const T& main_node
):
	pre_separator_space_(pre_separator_space),
	post_separator_space_(post_separator_space),
	main_node_(main_node)
{
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::item::item(const item& i):
	pre_separator_space_(i.pre_separator_space_),
	post_separator_space_(i.post_separator_space_),
	main_node_(i.main_node_)
{
}

template<class T, const leaf_node& SeparatorNode>
const optional_node<space>&
list_node<T, SeparatorNode>::item::pre_separator_space_node() const
{
	return pre_separator_space_;
}

template<class T, const leaf_node& SeparatorNode>
const optional_node<space>&
list_node<T, SeparatorNode>::item::post_separator_space_node() const
{
	return post_separator_space_;
}

template<class T, const leaf_node& SeparatorNode>
const T&
list_node<T, SeparatorNode>::item::main_node() const
{
	return main_node_;
}

template<class T, const leaf_node& SeparatorNode>
const typename list_node<T, SeparatorNode>::item&
list_node<T, SeparatorNode>::item::operator=(const item& i)
{
	pre_separator_space_ = i.pre_separator_space_;
	post_separator_space_ = i.post_separator_space_;
	main_node_ = i.main_node_;

	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
