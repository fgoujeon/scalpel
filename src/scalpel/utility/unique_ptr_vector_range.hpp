/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_UTILITY_UNIQUE_PTR_VECTOR_RANGE_HPP
#define SCALPEL_UTILITY_UNIQUE_PTR_VECTOR_RANGE_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <vector>
#include <memory>

namespace scalpel { namespace utility
{

template<typename T>
struct unique_ptr_vector_range_types
{
	typedef std::vector<std::unique_ptr<T>> raw_vector_t;

	typedef typename raw_vector_t::const_iterator raw_const_iterator;

	typedef std::function<T& (const std::unique_ptr<T>&)> to_reference_function_t;
	typedef std::function<const T& (const std::unique_ptr<T>&)> to_const_reference_function_t;

	typedef boost::transform_iterator<to_reference_function_t, raw_const_iterator> iterator;
	typedef boost::transform_iterator<to_const_reference_function_t, raw_const_iterator> const_iterator;
};

template<typename T>
struct unique_ptr_vector_range
{
	typedef boost::iterator_range<typename unique_ptr_vector_range_types<T>::iterator> type;
};

template<typename T>
struct unique_ptr_vector_const_range
{
	typedef boost::iterator_range<typename unique_ptr_vector_range_types<T>::const_iterator> type;
};

namespace unique_ptr_vector_range_functions
{
	template<typename T>
	T&
	to_reference(const std::unique_ptr<T>& ptr)
	{
		return *ptr;
	}

	template<typename T>
	const T&
	to_const_reference(const std::unique_ptr<T>& ptr)
	{
		return *ptr;
	}

	template<typename T>
	typename unique_ptr_vector_range_types<T>::iterator
	begin(std::vector<std::unique_ptr<T>>& raw_vector)
	{
		return typename unique_ptr_vector_range_types<T>::iterator(raw_vector.begin(), &to_reference<T>);
	}

	template<typename T>
	typename unique_ptr_vector_range_types<T>::const_iterator
	const_begin(const std::vector<std::unique_ptr<T>>& raw_vector)
	{
		return typename unique_ptr_vector_range_types<T>::const_iterator(raw_vector.begin(), &to_const_reference<T>);
	}

	template<typename T>
	typename unique_ptr_vector_range_types<T>::iterator
	end(std::vector<std::unique_ptr<T>>& raw_vector)
	{
		return typename unique_ptr_vector_range_types<T>::iterator(raw_vector.end(), &to_reference<T>);
	}

	template<typename T>
	typename unique_ptr_vector_range_types<T>::const_iterator
	const_end(const std::vector<std::unique_ptr<T>>& raw_vector)
	{
		return typename unique_ptr_vector_range_types<T>::const_iterator(raw_vector.end(), &to_const_reference<T>);
	}
}

template<typename T>
typename unique_ptr_vector_range<T>::type
make_unique_ptr_vector_range(std::vector<std::unique_ptr<T>>& v)
{
	return
		typename unique_ptr_vector_range<T>::type
		(
			unique_ptr_vector_range_functions::begin(v),
			unique_ptr_vector_range_functions::end(v)
		)
	;
}

template<typename T>
typename unique_ptr_vector_const_range<T>::type
make_unique_ptr_vector_const_range(const std::vector<std::unique_ptr<T>>& v)
{
	return
		typename unique_ptr_vector_const_range<T>::type
		(
			unique_ptr_vector_range_functions::const_begin(v),
			unique_ptr_vector_range_functions::const_end(v)
		)
	;
}

}} //namespace scalpel::utility

#endif

