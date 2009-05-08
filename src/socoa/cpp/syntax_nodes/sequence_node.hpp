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

#ifndef SOCOA_CPP_SYNTAX_NODES_SEQUENCE_NODE_HPP
#define SOCOA_CPP_SYNTAX_NODES_SEQUENCE_NODE_HPP

#include <boost/optional.hpp>
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "common_nodes.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

template<class T, const leaf_node& SeparatorNode = global_nodes::empty>
class sequence_node: public composite_node
{
    public:
		class item;

		typedef std::vector<item> seq_t;
		typedef T type;
		typedef typename seq_t::const_iterator const_iterator;

        sequence_node();

        sequence_node(const sequence_node& s);

        sequence_node(sequence_node&& s);

        const sequence_node&
		operator=(const sequence_node& s);

		const sequence_node&
		operator=(sequence_node&& s);

		bool
		empty() const
		{
			return seq_.empty();
		}

		const_iterator
		begin() const
		{
			return seq_.begin();
		}

		const_iterator
		end() const
		{
			return seq_.end();
		}

		void
		push_back(item&& t)
		{
			seq_.push_back(std::move(t));
			update_node_list(); ///\todo why add() doesn't work?
//			add(seq_.back());
		}

		static const leaf_node& separator_node;

	private:
		void
		update_node_list();

		seq_t seq_;
};

template<class T, const leaf_node& SeparatorNode = global_nodes::empty>
class sequence_node<T, SeparatorNode>::item
{
	public:
		item
		(
			boost::optional<space>&& pre_separator_space,
			boost::optional<space>&& post_separator_space,
			T&& main_node
		);

		item(const item& i);

		const item&
		operator=(const item& i);

		const boost::optional<const space&>
		pre_separator_space_node() const;

		const boost::optional<const space&>
		post_separator_space_node() const;

		const T&
		main_node() const;

	private:
		boost::optional<space> pre_separator_space_;
		boost::optional<space> post_separator_space_;
		T main_node_;
};


template<class T, const leaf_node& SeparatorNode>
sequence_node<T, SeparatorNode>::sequence_node()
{
}

template<class T, const leaf_node& SeparatorNode>
sequence_node<T, SeparatorNode>::sequence_node(const sequence_node& s):
	composite_node(),
	seq_(s.seq_)
{
	update_node_list();
}

template<class T, const leaf_node& SeparatorNode>
sequence_node<T, SeparatorNode>::sequence_node(sequence_node&& s):
	seq_(std::move(s.seq_))
{
	update_node_list();
}

template<class T, const leaf_node& SeparatorNode>
const sequence_node<T, SeparatorNode>&
sequence_node<T, SeparatorNode>::operator=(const sequence_node& s)
{
	seq_ = s.seq_;
	update_node_list();

	return *this;
}

template<class T, const leaf_node& SeparatorNode>
const sequence_node<T, SeparatorNode>&
sequence_node<T, SeparatorNode>::operator=(sequence_node&& s)
{
	seq_ = std::move(s.seq_);
	update_node_list();

	return *this;
}

template<class T, const leaf_node& SeparatorNode>
void
sequence_node<T, SeparatorNode>::update_node_list()
{
	clear();

	bool first_item = true;
	for(auto i = seq_.begin(); i != seq_.end(); ++i)
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
sequence_node<T, SeparatorNode>::separator_node = SeparatorNode;


template<class T, const leaf_node& SeparatorNode>
sequence_node<T, SeparatorNode>::item::item
(
	boost::optional<space>&& pre_separator_space,
	boost::optional<space>&& post_separator_space,
	T&& main_node
):
	pre_separator_space_(pre_separator_space),
	post_separator_space_(post_separator_space),
	main_node_(main_node)
{
}

template<class T, const leaf_node& SeparatorNode>
sequence_node<T, SeparatorNode>::item::item(const item& i):
	pre_separator_space_(i.pre_separator_space_),
	post_separator_space_(i.post_separator_space_),
	main_node_(i.main_node_)
{
}

template<class T, const leaf_node& SeparatorNode>
const boost::optional<const space&>
sequence_node<T, SeparatorNode>::item::pre_separator_space_node() const
{
	return boost::optional<const space&>(pre_separator_space_);
}

template<class T, const leaf_node& SeparatorNode>
const boost::optional<const space&>
sequence_node<T, SeparatorNode>::item::post_separator_space_node() const
{
	return boost::optional<const space&>(post_separator_space_);
}

template<class T, const leaf_node& SeparatorNode>
const T&
sequence_node<T, SeparatorNode>::item::main_node() const
{
	return main_node_;
}

template<class T, const leaf_node& SeparatorNode>
const typename sequence_node<T, SeparatorNode>::item&
sequence_node<T, SeparatorNode>::item::operator=(const item& i)
{
	pre_separator_space_ = i.pre_separator_space_;
	post_separator_space_ = i.post_separator_space_;
	main_node_ = i.main_node_;

	return *this;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
