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

#ifndef CPP2XML_DETAIL_JSON_WRITER_IPP
#define CPP2XML_DETAIL_JSON_WRITER_IPP

namespace cpp2json { namespace detail
{

template<typename T>
void
json_writer::write_key_value_pair
(
	const std::string& key,
	const T value,
	typename boost::enable_if<boost::is_arithmetic<T>>::type*
)
{
	if(!first_item_) output_ << ',';
	first_item_ = false;

	output_ << '\n';
	indent();
	output_ << '"' << key << "\": " << value;
}

template<typename T>
void
json_writer::write_array_value
(
	const T value,
	typename boost::enable_if<boost::is_arithmetic<T>>::type*
)
{
	if(!first_item_) output_ << ',';
	first_item_ = false;

	output_ << '\n';
	indent();
	output_ << value;
}

}} //namespace cpp2json::detail

#endif

