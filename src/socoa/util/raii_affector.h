/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_UTIL_RAII_AFFECTOR_H
#define SOCOA_UTIL_RAII_AFFECTOR_H

#include <string>

namespace socoa { namespace util
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

}} //namespace socoa::util

#endif
