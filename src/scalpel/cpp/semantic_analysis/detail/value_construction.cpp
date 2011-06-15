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

	template<unsigned int Base>
	unsigned int
	convert_char_to_digit(const char c)
	{
		return c - '0';
	}

	template<>
	unsigned int
	convert_char_to_digit<16>(const char c)
	{
		if(c <= '9')
			return c - '0';
		else if(c <= 'F')
			return c - 'A' + 10;
		else
			return c - 'a' + 10;
	}

	template<typename Integer, unsigned int Base>
	Integer
	convert_string_to_integer(const std::string& str)
	{
		Integer value = 0;

		for(unsigned int i = 0; i < str.size(); ++i)
		{
			value *= Base;

			const char current_digit_char = str[i];
			const unsigned int current_digit = convert_char_to_digit<Base>(current_digit_char);

			value += current_digit;
		}

		return value;
	}

	struct decimal_string_to_integer_converter
	{
		template<typename Integer>
		inline
		static
		Integer
		convert(const std::string& str)
		{
			return convert_string_to_integer<Integer, 10>(str);
		}
	};

	struct hexadecimal_string_to_integer_converter
	{
		template<typename Integer>
		inline
		static
		Integer
		convert(const std::string& str)
		{
			return convert_string_to_integer<Integer, 16>(str);
		}
	};

	struct octal_string_to_integer_converter
	{
		template<typename Integer>
		inline
		static
		Integer
		convert(const std::string& str)
		{
			return convert_string_to_integer<Integer, 8>(str);
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
		semantic_entities::expression_t
		cast(const std::string&)
		{
			throw std::runtime_error("integer constant is too large for its type");
		}
	};

	template<template<typename> class MaxString, class StringToIntegerConverter, typename Integer, typename... Integers>
	struct to_first_integer_impl<MaxString, StringToIntegerConverter, Integer, Integers...>
	{
		static
		semantic_entities::expression_t
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
	semantic_entities::expression_t
	to_first_integer(const std::string& integer)
	{
		return to_first_integer_impl<MaxString, StringToIntegerConverter, Integers...>::cast(integer);
	}
}

semantic_entities::expression_t
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
						max_octal_string,
						octal_string_to_integer_converter,
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
						max_octal_string,
						octal_string_to_integer_converter,
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
						max_octal_string,
						octal_string_to_integer_converter,
						long long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::U:
				return
					to_first_integer
					<
						max_octal_string,
						octal_string_to_integer_converter,
						unsigned int,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::UL:
				return
					to_first_integer
					<
						max_octal_string,
						octal_string_to_integer_converter,
						unsigned long int,
						unsigned long long int
					>(integer_str)
				;
			case integer_suffix_enum::ULL:
				return
					to_first_integer
					<
						max_octal_string,
						octal_string_to_integer_converter,
						unsigned long long int
					>(integer_str)
				;
		}
	}

	assert(false);
}



semantic_entities::expression_t
create_boolean_value(const syntax_nodes::boolean_literal& boolean_literal_node)
{
	if(get<predefined_text_node<str::false_>>(&boolean_literal_node))
		return false;
	else
		return true;
}



namespace
{
	template<typename Float>
	Float
	string_to_float(const syntax_nodes::floating_literal& floating_literal_node)
	{
		Float integer_part = 0;
		if(get_integer_part(floating_literal_node))
		{
			const std::string& integer_part_str = get_integer_part(floating_literal_node)->value();
			std::istringstream integer_part_iss(integer_part_str);
			integer_part_iss >> integer_part;
		}

		Float fractional_part = 0;
		if(get_fractional_part(floating_literal_node))
		{
			const std::string& fractional_part_str = get_fractional_part(floating_literal_node)->value();

			for(int i = fractional_part_str.size() - 1; i >= 0; --i)
			{
				const unsigned char current_digit_char = fractional_part_str[i];
				const unsigned int current_digit = current_digit_char - '0';

				fractional_part += current_digit;
				fractional_part /= 10;
			}
		}

		Float value = integer_part + fractional_part;

		if(const optional_node<exponent_part>& opt_exponent_part_node = get_exponent_part(floating_literal_node))
		{
			const exponent_part& exponent_part_node = *opt_exponent_part_node;
			const std::string& exponent_str = get_digit_sequence(exponent_part_node).value();
			const unsigned int exponent = decimal_string_to_integer_converter::convert<unsigned int>(exponent_str);

			bool negative_exponent = false;
			if(const optional_node<sign>& opt_sign_node = get_sign(exponent_part_node))
			{
				const std::string& sign = opt_sign_node->value();
				negative_exponent = (sign == "-");
			}

			if(negative_exponent)
				for(unsigned int i = 0; i < exponent; ++i)
					value /= 10;
			else
				for(unsigned int i = 0; i < exponent; ++i)
					value *= 10;
		}

		return value;
	}
}

semantic_entities::expression_t
create_floating_value(const syntax_nodes::floating_literal& floating_literal_node)
{
	if(const optional_node<floating_suffix>& opt_floating_suffix_node = get_floating_suffix(floating_literal_node))
	{
		const floating_suffix& floating_suffix_node = *opt_floating_suffix_node;

		if(get<float_floating_suffix>(&floating_suffix_node))
			return string_to_float<float>(floating_literal_node);
		else
			return string_to_float<long double>(floating_literal_node);
	}

	//double by default
	return string_to_float<double>(floating_literal_node);
}



namespace
{
	template<typename Char>
	Char
	convert_c_char_to_char(const c_char& c_char_node)
	{
		if(const boost::optional<const source_character_set&>& opt_source_character_set_node = get<source_character_set>(&c_char_node))
		{
			const source_character_set& source_character_set_node = *opt_source_character_set_node;
			const std::string& str = source_character_set_node.value();
			assert(str.size() == 1);
			return str.front();
		}
		else if(const boost::optional<const escape_sequence&>& opt_escape_sequence_node = get<escape_sequence>(&c_char_node))
		{
			const escape_sequence& escape_sequence_node = *opt_escape_sequence_node;

			if(const boost::optional<const simple_escape_sequence&>& opt_simple_escape_sequence_node = get<simple_escape_sequence>(&escape_sequence_node))
			{
				const simple_escape_sequence& simple_escape_sequence_node = *opt_simple_escape_sequence_node;
				const std::string& str = simple_escape_sequence_node.value();

				if(str == "\\'") return '\'';
				if(str == "\\\"") return '"';
				if(str == "\\?") return '?';
				if(str == "\\\\") return '\\';
				if(str == "\\a") return '\a';
				if(str == "\\b") return '\b';
				if(str == "\\f") return '\f';
				if(str == "\\n") return '\n';
				if(str == "\\r") return '\r';
				if(str == "\\t") return '\t';
				if(str == "\\v") return '\v';
			}
			else if(const boost::optional<const octal_escape_sequence&>& opt_octal_escape_sequence_node = get<octal_escape_sequence>(&escape_sequence_node))
			{
				const octal_escape_sequence& octal_escape_sequence_node = *opt_octal_escape_sequence_node;
				const std::string& str = octal_escape_sequence_node.value();
				return octal_string_to_integer_converter::convert<char>(str);
			}
			else if(const boost::optional<const hexadecimal_escape_sequence&>& opt_hexadecimal_escape_sequence_node = get<hexadecimal_escape_sequence>(&escape_sequence_node))
			{
				const hexadecimal_escape_sequence& hexadecimal_escape_sequence_node = *opt_hexadecimal_escape_sequence_node;
				const std::string& str = hexadecimal_escape_sequence_node.value();
				return hexadecimal_string_to_integer_converter::convert<char>(str);
			}
		}
		else if(get<universal_character_name>(&c_char_node))
		{
			assert(false); //TODO
		}

		assert(false);
	}

	template<typename SingleChar, typename MultipleChar>
	semantic_entities::expression_t
	convert_c_char_sequence_to_char(const c_char_sequence& c_char_sequence_node)
	{
		if(c_char_sequence_node.size() == 1) //character literal containing a single c_char -> SingleChar
		{
			const c_char& c_char_node = c_char_sequence_node.front();
			return convert_c_char_to_char<SingleChar>(c_char_node);
		}
		else //character literal containing multiple c_chars -> MultipleChar
		{
			MultipleChar value = 0;

			//read the last N chars, where Nmax = sizeof(MultipleChar)
			const unsigned int char_sequence_size = c_char_sequence_node.size();
			const unsigned int max_char_count = sizeof(MultipleChar);
			const unsigned int begin_index = (char_sequence_size > max_char_count) ? char_sequence_size - max_char_count : 0;
			for(unsigned int i = begin_index; i < c_char_sequence_node.size(); ++i)
			{
				const c_char& c_char_node = c_char_sequence_node[i];
				const SingleChar c = convert_c_char_to_char<SingleChar>(c_char_node);

				value <<= 8;
				value += c;
			}

			return value;
		}
	}
}

semantic_entities::expression_t
create_character_value(const syntax_nodes::character_literal& character_literal_node)
{
	const c_char_sequence& c_char_sequence_node = get_char_sequence(character_literal_node);
	if(has_leading_l(character_literal_node))
		return convert_c_char_sequence_to_char<wchar_t, wchar_t>(c_char_sequence_node);
	else
		return convert_c_char_sequence_to_char<char, int>(c_char_sequence_node);
}

//semantic_entities::expression_t
//create_string_value(const syntax_nodes::string_literal& string_literal_node)
//{
//}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

