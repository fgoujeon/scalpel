/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_GRAMMAR_CONFIGURATION_H
#define SOCOA_CPP_GRAMMAR_CONFIGURATION_H

namespace socoa { namespace cpp
{

struct grammar_configuration
{
    grammar_configuration():
        skip_function_bodies(false),
        enable_typeof_support(true),
        enable_restrict_support(true)
    {
    }

    bool skip_function_bodies;

    bool enable_typeof_support;
    bool enable_restrict_support;
};

}} //namespace socoa::cpp

#endif
