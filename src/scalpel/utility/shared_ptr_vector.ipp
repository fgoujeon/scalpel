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

#ifndef SCALPEL_UTILITY_SHARED_PTR_VECTOR_IPP
#define SCALPEL_UTILITY_SHARED_PTR_VECTOR_IPP

namespace scalpel { namespace utility
{

template<typename T>
shared_ptr_vector<T>::shared_ptr_vector()
{
}

template<typename T>
shared_ptr_vector<T>::shared_ptr_vector(const shared_ptr_vector& o):
	vector_(o.vector_)
{
}

template<typename T>
shared_ptr_vector<T>::shared_ptr_vector(shared_ptr_vector&& o):
	vector_(std::move(o.vector_))
{
}

template<typename T>
const shared_ptr_vector<T>&
shared_ptr_vector<T>::operator=(const shared_ptr_vector& o)
{
	vector_ = o.vector_;
	return *this;
}

template<typename T>
const shared_ptr_vector<T>&
shared_ptr_vector<T>::operator=(shared_ptr_vector&& o)
{
	vector_ = std::move(o.vector_);
	return *this;
}

template<typename T>
void
shared_ptr_vector<T>::push_back(std::shared_ptr<T> t)
{
	vector_.push_back(t);
}

template<typename T>
typename shared_ptr_vector<T>::range
shared_ptr_vector<T>::pointers()
{
	return vector_;
}

template<typename T>
typename shared_ptr_vector<T>::const_range
shared_ptr_vector<T>::pointers() const
{
	const_iterator begin(vector_.begin(), &constify);
	const_iterator end(vector_.end(), &constify);
	return const_range(begin, end);
}

template<typename T>
inline
std::shared_ptr<const T>
shared_ptr_vector<T>::constify(std::shared_ptr<T> ptr)
{
	return ptr;
}

}} //namespace scalpel::utility

#endif

