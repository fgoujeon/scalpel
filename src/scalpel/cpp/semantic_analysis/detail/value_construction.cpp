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

#include "value_construction.hpp"
#include <sstream>
#include <limits>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;

namespace
{
	enum class integer_suffix_enum
	{
		NONE,
		U,
		L,
		LL,
		UL,
		ULL
	};

	template<typename Integer>
	std::string
	to_string(const Integer i)
	{
		std::ostringstream oss;
		oss << i;
		return oss.str();
	}

	template<typename Integer>
	std::string
	to_hexadecimal_string(const Integer i)
	{
		std::ostringstream oss;
		oss << std::hex << i;
		return oss.str();
	}

	template<typename Integer>
	std::string
	to_octal_string(const Integer i)
	{
		std::ostringstream oss;
		oss << std::oct << i;
		return oss.str();
	}

	struct decimal_string_to_integer_converter
	{
		template<typename Integer>
		static
		Integer
		convert(const std::string& str)
		{
			std::istringstream iss(str);
			Integer i;
			iss >> i;
			return i;
		}
	};

	struct hexadecimal_string_to_integer_converter
	{
		template<typename Integer>
		static
		Integer
		convert(const std::string& str)
		{
			std::istringstream iss(str);
			Integer i;
			iss >> std::hex >> i;
			return i;
		}
	};

	struct octal_string_to_integer_converter
	{
		template<typename Integer>
		static
		Integer
		convert(const std::string& str)
		{
			std::istringstream iss(str);
			Integer i;
			iss >> std::oct >> i;
			return i;
		}
	};

	bool
	lower_than_or_equal_to(const std::string& lhs, const std::string& rhs)
	{
		if(lhs.size() < rhs.size())
			return true;
		else if(lhs.size() > rhs.size())
			return false;
		else
			return lhs <= rhs;
	}



	//maximum value that can be hold in the given integer type, converted in string (decimal format)
	template<typename Integer>
	struct max_decimal_string
	{
		static const std::string value;
	};
	template<typename Integer>
	const std::string max_decimal_string<Integer>::value = to_string(std::numeric_limits<Integer>::max());

	//maximum value that can be hold in the given integer type, converted in string (hexadecimal format)
	template<typename Integer>
	struct max_hexadecimal_string
	{
		static const std::string value;
	};
	template<typename Integer>
	const std::string max_hexadecimal_string<Integer>::value = to_hexadecimal_string(std::numeric_limits<Integer>::max());

	//maximum value that can be hold in the given integer type, converted in string (octal format)
	template<typename Integer>
	struct max_octal_string
	{
		static const std::string value;
	};
	template<typename Integer>
	const std::string max_octal_string<Integer>::value = to_octal_string(std::numeric_limits<Integer>::max());



	template<template<typename> class MaxString, class StringToIntegerConverter, typename... Integers>
	struct to_first_integer_impl;

	template<template<typename> class MaxString, class StringToIntegerConverter>
	struct to_first_integer_impl<MaxString, StringToIntegerConverter>
	{
		static
		semantic_entities::integer_value_t
		cast(const std::string&)
		{
			throw std::runtime_error("integer constant is too large for its type");
		}
	};

	template<template<typename> class MaxString, class StringToIntegerConverter, typename Integer, typename... Integers>
	struct to_first_integer_impl<MaxString, StringToIntegerConverter, Integer, Integers...>
	{
		static
		semantic_entities::integer_value_t
		cast(const std::string& integer)
		{
			if(lower_than_or_equal_to(integer, MaxString<Integer>::value))
				return StringToIntegerConverter::template convert<Integer>(integer);
			else
				return to_first_integer_impl<MaxString, StringToIntegerConverter, Integers...>::cast(integer);
		}
	};

	//Converts the given string to one of the given integer types.
	//The selected type is the first big enough to hold the integer.
	template<template<typename> class MaxString, class StringToIntegerConverter, typename... Integers>
	semantic_entities::integer_value_t
	to_first_integer(const std::string& integer)
	{
		return to_first_integer_impl<MaxString, StringToIntegerConverter, Integers...>::cast(integer);
	}
}

semantic_entities::integer_value_t
create_value(const syntax_nodes::integer_literal& integer_literal_node)
{
	const integer_literal_no_suffix& integer_literal_no_suffix_node = get_integer_literal_no_suffix(integer_literal_node);

	integer_suffix_enum suffix = integer_suffix_enum::NONE;
	if(const optional_node<integer_suffix>& opt_integer_suffix = get_integer_suffix(integer_literal_node))
	{
		const integer_suffix& integer_suffix_node = *opt_integer_suffix;
		const bool has_unsigned_suffix = syntax_nodes::has_unsigned_suffix(integer_suffix_node);
		const bool has_long_suffix = syntax_nodes::has_long_suffix(integer_suffix_node);
		const bool has_long_long_suffix = syntax_nodes::has_long_long_suffix(integer_suffix_node);

		if(has_unsigned_suffix)
		{
			if(!has_long_suffix && !has_long_long_suffix)
			{
				suffix = integer_suffix_enum::U;
			}
			else if(has_long_suffix)
			{
				assert(!has_long_long_suffix);
				suffix = integer_suffix_enum::UL;
			}
			else if(has_long_long_suffix)
			{
				assert(!has_long_suffix);
				suffix = integer_suffix_enum::ULL;
			}
		}
		else
		{
			if(has_long_suffix)
			{
				assert(!has_long_long_suffix);
				suffix = integer_suffix_enum::L;
			}
			else
			{
				assert(has_long_long_suffix);
				suffix = integer_suffix_enum::LL;
			}
		}
	}

	if(const boost::optional<const decimal_literal&>& opt_decimal_literal_node = get<decimal_literal>(&integer_literal_no_suffix_node))
	{
		const decimal_literal& decimal_literal_node = *opt_decimal_literal_node;
		const std::string& integer_str = decimal_literal_node.value();

		switch(suffix)
		{
			case integer_suffix_enum::NONE:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						int,
						long int,
						long long int
					>(integer_str)
				;
			case integer_suffix_enum::L:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						long int,
						long long int
					>(integer_str)
				;
			case integer_suffix_enum::LL:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						long long int
					>(integer_str)
				;
			case integer_suffix_enum::U:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						unsigned int,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::UL:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::ULL:
				return
					to_first_integer
					<
						max_decimal_string,
						decimal_string_to_integer_converter,
						unsigned long long int
					>(integer_str)
				;
		}
	}
	else if(const boost::optional<const hexadecimal_literal&>& opt_hexadecimal_literal_node = get<hexadecimal_literal>(&integer_literal_no_suffix_node))
	{
		const hexadecimal_literal& hexadecimal_literal_node = *opt_hexadecimal_literal_node;
		const std::string& prefix_integer_str = hexadecimal_literal_node.value();
		const std::string& integer_str = prefix_integer_str.substr(2, prefix_integer_str.size() - 2); //remove 0x prefix

		switch(suffix)
		{
			case integer_suffix_enum::NONE:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						int,
						unsigned int,
						long int,
						unsigned long int,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::L:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						long int,
						unsigned long int,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::LL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::U:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned int,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::UL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::ULL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned long long int
					>(integer_str)
				;
		}
	}
	else if(const boost::optional<const octal_literal&>& opt_octal_literal_node = get<octal_literal>(&integer_literal_no_suffix_node))
	{
		const octal_literal& octal_literal_node = *opt_octal_literal_node;
		const std::string& prefix_integer_str = octal_literal_node.value();
		const std::string& integer_str = prefix_integer_str.substr(1, prefix_integer_str.size() - 1); //remove 0 prefix

		switch(suffix)
		{
			case integer_suffix_enum::NONE:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						int,
						unsigned int,
						long int,
						unsigned long int,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::L:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						long int,
						unsigned long int,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::LL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::U:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned int,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::UL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::ULL:
				return
					to_first_integer
					<
						max_hexadecimal_string,
						hexadecimal_string_to_integer_converter,
						unsigned long long int
					>(integer_str)
				;
		}
	}

	assert(false);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

