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

#include "type_name.h"

#include <iostream>
#include <cassert>
#include "../name_lookup.h"

namespace socoa { namespace cpp { namespace parsers
{

void
type_name::set_input(const std::string& input)
{
    input_ = &input;
}

std::ptrdiff_t
type_name::operator()(const scanner_t& scan) const
{
    assert(input_);

    std::cout << "Ambiguity\n";
    std::cout << "Fragment of input succesfully parsed:\n";
    for(const char* c = &*(input_->begin()); c < scan.first; ++c)
    {
        std::cout << *c;
    }
    std::cout << "\n";

    return -1;
}

}}} //namespace socoa::cpp::parsers
