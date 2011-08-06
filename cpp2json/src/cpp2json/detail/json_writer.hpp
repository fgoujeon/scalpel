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

#ifndef CPP2XML_DETAIL_JSON_WRITER_HPP
#define CPP2XML_DETAIL_JSON_WRITER_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/utility/enable_if.hpp>
#include <string>
#include <iostream>

namespace cpp2json { namespace detail
{

class json_writer
{
	public:
		json_writer(std::ostream& output);



		void
		open_object();

		void
		open_object(const std::string& key);

		void
		close_object();



		void
		open_array(const std::string& key);

		void
		close_array();



		void
		write_key_value_pair(const std::string& key, const bool value);

		template<typename T>
		void
		write_key_value_pair
		(
			const std::string& key,
			const T value,
			typename boost::enable_if<boost::is_arithmetic<T>>::type* = 0
		);

		void
		write_key_value_pair(const std::string& key, const char* const value);

		void
		write_key_value_pair(const std::string& key, const std::string& value);



		template<typename T>
		void
		write_array_value
		(
			const T value,
			typename boost::enable_if<boost::is_arithmetic<T>>::type* = 0
		);

	private:
		void
		indent();

	private:
		std::ostream& output_;
		unsigned int indent_level_;
		bool first_item_;
};

}} //namespace cpp2json::detail

#include "json_writer.ipp"

#endif

