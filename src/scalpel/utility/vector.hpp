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

#ifndef SCALPEL_UTILITY_VECTOR_HPP
#define SCALPEL_UTILITY_VECTOR_HPP

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <vector>

namespace scalpel { namespace utility
{

/**
Vector which propagates constness: the pointed objects
of a const vector can't be modified.
*/
template<typename T>
class vector
{
	private:
		typedef std::vector<T> raw_vector_t;

	public:
		typedef typename raw_vector_t::iterator iterator;
		typedef typename raw_vector_t::const_iterator const_iterator;

		/**
		Gives read/write access to the pointed objects (but no access to the container itself).
		The conversion to this type is implicit.
		*/
		typedef boost::iterator_range<iterator> range;

		typedef typename raw_vector_t::size_type size_type;
		typedef typename raw_vector_t::value_type value_type;
		typedef const T& const_reference;

		vector();

		vector(const vector& o) = delete;

		vector(vector&& o);

		const vector&
		operator=(const vector& o) = delete;

		const vector&
		operator=(vector&& o);

		T&
		operator[](const typename raw_vector_t::size_type n)
		{
			return raw_vector_[n];
		}

		const T&
		operator[](const typename raw_vector_t::size_type n) const
		{
			return raw_vector_[n];
		}

		operator range() const
		{
			return range(begin(), end());
		}

		size_type
		size() const
		{
			return raw_vector_.size();
		}

		bool
		empty() const
		{
			return raw_vector_.empty();
		}

		iterator
		begin()
		{
			return raw_vector_.begin();
		}

		const_iterator
		begin() const
		{
			return raw_vector_.begin();
		}

		iterator
		end()
		{
			return raw_vector_.end();
		}

		const_iterator
		end() const
		{
			return raw_vector_.end();
		}

		T&
		front()
		{
			return raw_vector_.front();
		}

		const T&
		front() const
		{
			return raw_vector_.front();
		}

		T&
		back()
		{
			return raw_vector_.back();
		}

		const T&
		back() const
		{
			return raw_vector_.back();
		}

		void
		push_back(const T& t)
		{
			raw_vector_.push_back(t);
		}

		void
		pop_back()
		{
			raw_vector_.pop_back();
		}

		void
		clear()
		{
			raw_vector_.clear();
		}

	private:
		raw_vector_t raw_vector_;
};

}} //namespace scalpel::utility

#include "vector.ipp"

#endif

