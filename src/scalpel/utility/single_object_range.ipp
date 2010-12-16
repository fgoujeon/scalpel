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

#ifndef SCALPEL_UTILITY_SINGLE_OBJECT_RANGE_IPP
#define SCALPEL_UTILITY_SINGLE_OBJECT_RANGE_IPP

namespace scalpel { namespace utility
{

template<typename T>
single_object_range<T>::single_object_range():
	object_(0)
{
}

template<typename T>
single_object_range<T>::single_object_range(const T& object):
	object_(&object)
{
}

template<typename T>
typename single_object_range<T>::iterator
single_object_range<T>::begin()
{
	if(object_)
		return iterator(*object_);
	else
		return iterator();
}

template<typename T>
typename single_object_range<T>::iterator
single_object_range<T>::end()
{
	return iterator();
}



template<typename T>
single_object_range<T>::iterator::iterator():
	object_(0)
{
}

template<typename T>
single_object_range<T>::iterator::iterator(const T& object):
	object_(&object)
{
}

template<typename T>
bool
single_object_range<T>::iterator::operator==(const iterator& rhs)
{
	return object_ == rhs.object_;
}

template<typename T>
bool
single_object_range<T>::iterator::operator!=(const iterator& rhs)
{
	return !operator==(rhs);
}

template<typename T>
typename single_object_range<T>::iterator::iterator
single_object_range<T>::iterator::operator++()
{
	object_ = 0;
	return *this;
}

template<typename T>
const T&
single_object_range<T>::iterator::operator*()
{
	return *object_;
}

}} //namespace scalpel::utility

#endif

