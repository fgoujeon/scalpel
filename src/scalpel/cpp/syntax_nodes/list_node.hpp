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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LIST_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LIST_NODE_HPP

#include <vector>
#include "optional_node.hpp"
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "common_nodes.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class T, const leaf_node& SeparatorNode = common_nodes::empty>
class list_node: public composite_node
{
    public:
		class item;

		typedef std::vector<item> list_t;
		typedef T type;
		typedef typename list_t::const_iterator const_iterator;

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
			return list_.empty();
		}

		const_iterator
		begin() const
		{
			return list_.begin();
		}

		const_iterator
		end() const
		{
			return list_.end();
		}

		void
		push_back(item&& t)
		{
			list_.push_back(std::move(t));
			update_node_list(); ///\todo why add() doesn't work?
//			add(list_.back());
		}

		static const leaf_node& separator_node;

	private:
		void
		update_node_list();

		list_t list_;
};

template<class T, const leaf_node& SeparatorNode = common_nodes::empty>
class list_node<T, SeparatorNode>::item
{
	public:
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
list_node<T, SeparatorNode>::list_node()
{
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::list_node(const list_node& s):
	composite_node(),
	list_(s.list_)
{
	update_node_list();
}

template<class T, const leaf_node& SeparatorNode>
list_node<T, SeparatorNode>::list_node(list_node&& s):
	list_(std::move(s.list_))
{
	update_node_list();
}

template<class T, const leaf_node& SeparatorNode>
const list_node<T, SeparatorNode>&
list_node<T, SeparatorNode>::operator=(const list_node& s)
{
	list_ = s.list_;
	update_node_list();

	return *this;
}

template<class T, const leaf_node& SeparatorNode>
const list_node<T, SeparatorNode>&
list_node<T, SeparatorNode>::operator=(list_node&& s)
{
	list_ = std::move(s.list_);
	update_node_list();

	return *this;
}

template<class T, const leaf_node& SeparatorNode>
void
list_node<T, SeparatorNode>::update_node_list()
{
	clear();

	bool first_item = true;
	for(auto i = list_.begin(); i != list_.end(); ++i)
	{
		if(first_item)
		{
			add(i->main_node());
			first_item = false;
		}
		else
		{
			if(i->pre_separator_space_node()) add(*i->pre_separator_space_node());
			add(SeparatorNode);
			if(i->post_separator_space_node()) add(*i->post_separator_space_node());
			add(i->main_node());
		}
	}
}

template<class T, const leaf_node& SeparatorNode>
const leaf_node&
list_node<T, SeparatorNode>::separator_node = SeparatorNode;


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
