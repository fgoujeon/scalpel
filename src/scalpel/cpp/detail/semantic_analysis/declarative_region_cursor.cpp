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

#include "declarative_region_cursor.hpp"
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//
//declarative_region_cursor
//

declarative_region_cursor::declarative_region_cursor()
{
}

void
declarative_region_cursor::initialize(std::shared_ptr<semantic_entities::declarative_region> global_declarative_region)
{
	declarative_region_path_.clear();
	declarative_region_path_.push_back(global_declarative_region);
}

declarative_region_cursor::declarative_regions_t::range
declarative_region_cursor::declarative_region_path()
{
	return declarative_region_path_;
}

const declarative_region_cursor::declarative_regions_t&
declarative_region_cursor::declarative_region_path() const
{
	return declarative_region_path_;
}

std::shared_ptr<semantic_entities::declarative_region>
declarative_region_cursor::global_declarative_region()
{
	assert(!declarative_region_path_.empty());
	return declarative_region_path_.front();
}

std::shared_ptr<semantic_entities::declarative_region>
declarative_region_cursor::current_declarative_region()
{
	assert(!declarative_region_path_.empty());
	return declarative_region_path_.back();
}

void
declarative_region_cursor::enter_declarative_region(std::shared_ptr<semantic_entities::declarative_region> a_declarative_region)
{
	declarative_region_path_.push_back(a_declarative_region);
}

void
declarative_region_cursor::enter_last_added_declarative_region()
{
	assert(!current_declarative_region()->named_declarative_regions().empty());
	enter_declarative_region(current_declarative_region()->named_declarative_regions().back());
}

void
declarative_region_cursor::leave_current_declarative_region()
{
	declarative_region_path_.pop_back();
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

