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

#ifndef SCALPEL_UTILITY_SHARED_PTR_VECTOR_HPP
#define SCALPEL_UTILITY_SHARED_PTR_VECTOR_HPP

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <vector>
#include <memory>

namespace scalpel { namespace utility
{

/**
A container for shared_ptrs which propagates constness: the pointed objects of
a const shared_prt_vector can't be modified.
*/
template<typename T>
class shared_ptr_vector
{
	private:
		typedef std::vector<std::shared_ptr<T>> raw_vector_t;

		typedef typename raw_vector_t::const_iterator raw_const_iterator;

		typedef std::function<std::shared_ptr<const T> (std::shared_ptr<T>)> constify_function_t;

	public:
		typedef typename raw_vector_t::iterator iterator;
		typedef boost::transform_iterator<constify_function_t, raw_const_iterator, std::shared_ptr<const T>> const_iterator;

		typedef boost::iterator_range<iterator> range;
		typedef boost::iterator_range<const_iterator> const_range;

		typedef typename raw_vector_t::size_type size_type;
		typedef typename raw_vector_t::value_type value_type;
		typedef std::shared_ptr<T> const_reference;

		shared_ptr_vector();

		shared_ptr_vector(const shared_ptr_vector& o);

		shared_ptr_vector(shared_ptr_vector&& o);

		const shared_ptr_vector&
		operator=(const shared_ptr_vector& o);

		const shared_ptr_vector&
		operator=(shared_ptr_vector&& o);

		inline
		size_type
		size() const;

		inline
		bool
		empty() const;

		inline
		operator range();

		inline
		operator const_range() const;

		/**
		Gives read/write access to the pointers (but no access to the container itself)
		*/
		inline
		range
		pointers();

		const_range
		pointers() const;

		inline
		iterator
		begin();

		inline
		iterator
		end();

		inline
		std::shared_ptr<T>
		front();

		inline
		std::shared_ptr<const T>
		front() const;

		inline
		std::shared_ptr<T>
		back();

		inline
		std::shared_ptr<const T>
		back() const;

		inline
		void
		push_back(std::shared_ptr<T> t);

		inline
		void
		pop_back();

		inline
		void
		clear();

	private:
		static
		inline
		std::shared_ptr<const T>
		constify(std::shared_ptr<T> ptr);

		raw_vector_t raw_vector_;
};

}} //namespace scalpel::utility

#include "shared_ptr_vector.ipp"

#endif

