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

#ifndef SCALPEL_CPP_SYNTAX_NODES_OPTIONAL_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_OPTIONAL_NODE_HPP

#include <memory>
#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<class T>
class optional_node: public composite_node
{
    public:
        optional_node();

        optional_node(T&& node);

        optional_node(const optional_node& o);

        optional_node(optional_node&& o);

        const optional_node&
		operator=(const optional_node& o);

		const optional_node&
		operator=(optional_node&& o);

		const T&
		operator*() const;

		T&
		operator*();

		const T*
		operator->() const;

		T*
		operator->();

		operator bool() const;

	private:
		void
		update_node_list();

		std::unique_ptr<T> node_;
};

template<class T>
optional_node<T>::optional_node()
{
}

template<class T>
optional_node<T>::optional_node(T&& node):
	node_(new T(std::move(node)))
{
}

template<class T>
optional_node<T>::optional_node(const optional_node& o):
	composite_node()
{
	if(o.node_)
		node_ = std::move(std::unique_ptr<T>(new T(*o.node_)));
	update_node_list();
}

template<class T>
optional_node<T>::optional_node(optional_node&& o):
	composite_node(),
	node_(std::move(o.node_))
{
	update_node_list();
}

template<class T>
const optional_node<T>&
optional_node<T>::operator=(const optional_node& o)
{
	optional_node<T> copy(o);
	std::swap(copy, *this);
	return *this;
}

template<class T>
const optional_node<T>&
optional_node<T>::operator=(optional_node&& o)
{
	node_ = std::move(o.node_);
	update_node_list();
	return *this;
}

template<class T>
const T&
optional_node<T>::operator*() const
{
	if(node_)
		return *node_;
	else
		throw "optional_node error";
}

template<class T>
T&
optional_node<T>::operator*()
{
	if(node_)
		return *node_;
	else
		throw "optional_node error";
}

template<class T>
const T*
optional_node<T>::operator->() const
{
	return &*node_;
}

template<class T>
T*
optional_node<T>::operator->()
{
	return &*node_;
}

template<class T>
optional_node<T>::operator bool() const
{
	return node_;
}

template<class T>
void
optional_node<T>::update_node_list()
{
	clear();
	if(node_)
		add(*node_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
