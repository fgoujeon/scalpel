/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "json_writer.hpp"

namespace cpp2json { namespace detail
{

json_writer::json_writer(std::ostream& output):
	output_(output),
	indent_level_(0),
	first_item_(true)
{
}

void
json_writer::open_object()
{
	if(!first_item_) output_ << ',';

	if(indent_level_ != 0) output_ << '\n'; //no new line at begin of file
	indent();
	output_ << "{";
	++indent_level_;
	first_item_ = true;
}

void
json_writer::open_object(const std::string& key)
{
	if(!first_item_) output_ << ',';

	if(indent_level_ != 0) output_ << '\n'; //no new line at begin of file

	indent();
	output_ << "\"" << key << "\":\n";

	indent();
	output_ << "{";
	++indent_level_;
	first_item_ = true;
}

void
json_writer::close_object()
{
	first_item_ = false;
	--indent_level_;
	output_ << '\n';
	indent();
	output_ << '}';

	if(indent_level_ == 0) output_ << '\n'; //final new line at end of file
}

void
json_writer::open_array(const std::string& key)
{
	if(!first_item_) output_ << ',';

	output_ << '\n';

	indent();
	output_ << "\"" << key << "\":\n";

	indent();
	output_ << "[";
	++indent_level_;
	first_item_ = true;
}

void
json_writer::close_array()
{
	first_item_ = false;
	--indent_level_;
	output_ << '\n';
	indent();
	output_ << ']';
}

void
json_writer::write_key_value_pair(const std::string& key, const bool value)
{
	if(!first_item_) output_ << ',';
	first_item_ = false;

	output_ << '\n';
	indent();
	output_ << '"' << key << "\": ";

	if(value)
		output_ << "true";
	else
		output_ << "false";
}

void
json_writer::write_key_value_pair(const std::string& key, const char* const value)
{
	if(!first_item_) output_ << ',';
	first_item_ = false;

	output_ << '\n';
	indent();
	output_ << '"' << key << "\": \"" << value << '"';
}

void
json_writer::write_key_value_pair(const std::string& key, const std::string& value)
{
	write_key_value_pair(key, value.c_str());
}

void
json_writer::indent()
{
	for(unsigned int i = 0; i < indent_level_; ++i)
		output_ << "  ";
}

}} //namespace cpp2json::detail

