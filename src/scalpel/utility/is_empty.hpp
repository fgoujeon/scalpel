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

#ifndef SCALPEL_UTILITY_IS_EMPTY_HPP
#define SCALPEL_UTILITY_IS_EMPTY_HPP

#include "vector.hpp"
#include <boost/optional.hpp>
#include <vector>
#include <set>
#include <memory>

namespace scalpel { namespace utility
{

template<class T>
inline
bool
is_empty(const std::vector<T>& container);

template<class T>
inline
bool
is_empty(const std::set<T>& container);

template<class T>
inline
bool
is_empty(const vector<T>& container);

template<class T>
inline
bool
is_empty(const std::shared_ptr<T>& container);

template<class T>
inline
bool
is_empty(const boost::optional<T>& container);

}} //namespace scalpel::utility

#include "is_empty.ipp"

#endif

