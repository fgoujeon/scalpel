/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#include "common_nodes.hpp"
#include <vector>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class T>
class list_node
{
    public:
		typedef std::vector<T> nodes_t;
		typedef T type;
		typedef typename nodes_t::const_iterator const_iterator;
		typedef typename nodes_t::const_reverse_iterator const_reverse_iterator;

        list_node();

        list_node(const list_node& rhs);

        list_node(list_node&& rhs);

        const list_node&
		operator=(const list_node& rhs);

		const list_node&
		operator=(list_node&& rhs);

		bool
		empty() const
		{
			return nodes_.empty();
		}

		typename nodes_t::size_type
		size() const
		{
			return nodes_.size();
		}

		const_iterator
		begin() const
		{
			return nodes_.begin();
		}

		const_reverse_iterator
		rbegin() const
		{
			return nodes_.rbegin();
		}

		const_iterator
		end() const
		{
			return nodes_.end();
		}

		const_reverse_iterator
		rend() const
		{
			return nodes_.rend();
		}

		const T&
		front() const
		{
			return nodes_.front();
		}

		const T&
		operator[](const unsigned int index) const
		{
			return nodes_[index];
		}

		void
		push_back(const T& t)
		{
			nodes_.push_back(t);
		}

		void
		push_back(T&& t)
		{
			nodes_.push_back(std::move(t));
		}

	private:
		nodes_t nodes_;
};

template<class T>
list_node<T>::list_node()
{
}

template<class T>
list_node<T>::list_node(const list_node& rhs):
	nodes_(rhs.nodes_)
{
}

template<class T>
list_node<T>::list_node(list_node&& rhs):
	nodes_(std::move(rhs.nodes_))
{
}

template<class T>
const list_node<T>&
list_node<T>::operator=(const list_node& rhs)
{
	nodes_ = rhs.nodes_;
	return *this;
}

template<class T>
const list_node<T>&
list_node<T>::operator=(list_node&& rhs)
{
	nodes_ = std::move(rhs.nodes_);
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

