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

#ifndef SCALPEL_UTIL_RAII_AFFECTOR_HPP
#define SCALPEL_UTIL_RAII_AFFECTOR_HPP

#include <string>

namespace scalpel { namespace util
{

template <typename T, T InitialValue, T FinalValue>
class raii_affector
{
    public:
        raii_affector(T& var);

        ~raii_affector();

    private:
        T& var_;
};

template <typename T, T InitialValue, T FinalValue>
raii_affector<T, InitialValue, FinalValue>::raii_affector(T& var):
    var_(var)
{
    var_ = InitialValue;
}

template <typename T, T InitialValue, T FinalValue>
raii_affector<T, InitialValue, FinalValue>::~raii_affector()
{
    var_ = FinalValue;
}

}} //namespace scalpel::util

#endif
