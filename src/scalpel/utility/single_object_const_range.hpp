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

#ifndef SCALPEL_UTILITY_SINGLE_OBJECT_CONST_RANGE_HPP
#define SCALPEL_UTILITY_SINGLE_OBJECT_CONST_RANGE_HPP

namespace scalpel { namespace utility
{

template<typename T>
class single_object_const_range
{
	public:
		typedef T value_type;
		typedef const T& reference;
		class iterator;

		//empty const_range
		single_object_const_range();

		single_object_const_range(const T& object);

		bool
		empty() const;

		iterator
		begin();

		iterator
		end();

	private:
		const T* object_;
};

template<typename T>
class single_object_const_range<T>::iterator
{
	public:
		iterator();

		iterator(const T& object);

		bool
		operator==(const iterator& rhs);

		bool
		operator!=(const iterator& rhs);

		iterator
		operator++();

		const T&
		operator*() const;

	private:
		const T* object_;
};

}} //namespace scalpel::utility

#include "single_object_const_range.ipp"

#endif

