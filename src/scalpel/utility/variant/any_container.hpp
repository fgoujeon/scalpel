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

#ifndef SCALPEL_UTILITY_VARIANT_ANY_CONTAINER_HPP
#define SCALPEL_UTILITY_VARIANT_ANY_CONTAINER_HPP

namespace scalpel { namespace utility
{

template<unsigned int Size>
class any_container
{
	public:
		template<typename T>
		T&
		get()
		{
			return *reinterpret_cast<T*>(buffer_);
		}

		template<typename T>
		const T&
		get() const
		{
			return *reinterpret_cast<const T*>(buffer_);
		}

		template<typename T>
		void
		set(const T& value)
		{
			new(buffer_) T(value);
		}

		template<typename T>
		void
		clear()
		{
			get<T>().~T();
		}

	private:
		char buffer_[Size];
};

}} //namespace scalpel::utility

#endif
