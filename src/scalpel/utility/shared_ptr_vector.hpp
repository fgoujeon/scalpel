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
Vector which propagates constness: the pointed objects
of a const vector can't be modified.
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

		/**
		Gives read/write access to the pointed objects (but no access to the container itself).
		The conversion to this type is implicit.
		*/
		typedef boost::iterator_range<iterator> range;

		typedef typename raw_vector_t::size_type size_type;
		typedef typename raw_vector_t::value_type value_type;
		typedef std::shared_ptr<T> const_reference;

		shared_ptr_vector();

		shared_ptr_vector(const shared_ptr_vector& o) = delete;

		shared_ptr_vector(shared_ptr_vector&& o);

		const shared_ptr_vector&
		operator=(const shared_ptr_vector& o) = delete;

		const shared_ptr_vector&
		operator=(shared_ptr_vector&& o);

		std::shared_ptr<T>
		operator[](const typename raw_vector_t::size_type n)
		{
			return raw_vector_[n];
		}

		std::shared_ptr<const T>
		operator[](const typename raw_vector_t::size_type n) const
		{
			return raw_vector_[n];
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
			return const_iterator(raw_vector_.begin(), &constify);
		}

		iterator
		end()
		{
			return raw_vector_.end();
		}

		const_iterator
		end() const
		{
			return const_iterator(raw_vector_.end(), &constify);
		}

		std::shared_ptr<T>
		front()
		{
			return raw_vector_.front();
		}

		std::shared_ptr<const T>
		front() const
		{
			return raw_vector_.front();
		}

		std::shared_ptr<T>
		back()
		{
			return raw_vector_.back();
		}

		std::shared_ptr<const T>
		back() const
		{
			return raw_vector_.back();
		}

		void
		push_back(std::shared_ptr<T> t)
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
		static
		std::shared_ptr<const T>
		constify(std::shared_ptr<T> ptr)
		{
			return ptr;
		}

		raw_vector_t raw_vector_;
};

}} //namespace scalpel::utility

#include "shared_ptr_vector.ipp"

#endif

