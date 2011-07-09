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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_EXPRESSION_INFORMATION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_EXPRESSION_INFORMATION_HPP

#include <scalpel/cpp/semantic_entities/type.hpp>
#include <scalpel/cpp/semantic_entities/expression.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

class expression_information
{
	private:
		enum class type_category
		{
			BOOL,
			CHAR,
			WCHAR_T,
			INT,
			LONG_INT,
			LONG_LONG_INT,
			SHORT_INT,
			SIGNED_CHAR,
			UNSIGNED_CHAR,
			UNSIGNED_INT,
			UNSIGNED_LONG_INT,
			UNSIGNED_LONG_LONG_INT,
			UNSIGNED_SHORT_INT,
			FLOAT,
			DOUBLE,
			LONG_DOUBLE,
			ENUMERATION,
			POINTER_TO_DEFINED_TYPE,
			OTHER
		};

		struct get_category_visitor_t: utility::static_visitor<type_category>
		{
			get_category_visitor_t()
			{
			}

			template<typename T>
			type_category
			operator()(const T&) const
			{
				return type_category::OTHER;
			}

			type_category
			operator()(const semantic_entities::cv_qualified_type& type) const;

			type_category
			operator()(const semantic_entities::fundamental_type type) const;
		};
		friend struct get_category_visitor_t;

		struct is_bit_field_visitor_t: utility::static_visitor<bool>
		{
			is_bit_field_visitor_t()
			{
			}

			template<typename T>
			bool
			operator()(const T&) const
			{
				return false;
			}

			bool
			operator()(const semantic_entities::bit_field&) const
			{
				return true;
			}
		};
		friend struct is_bit_field_visitor_t;

	public:
		expression_information(const semantic_entities::expression_t& expr);



		//
		//specific types
		//

		inline
		bool
		has_bool_type() const
		{
			return type_category_ == type_category::BOOL;
		}

		inline
		bool
		has_char_type() const
		{
			return type_category_ == type_category::CHAR;
		}

		inline
		bool
		has_wchar_t_type() const
		{
			return type_category_ == type_category::WCHAR_T;
		}

		inline
		bool
		has_signed_char_type() const
		{
			return type_category_ == type_category::SIGNED_CHAR;
		}

		inline
		bool
		has_short_int_type() const
		{
			return type_category_ == type_category::SHORT_INT;
		}

		inline
		bool
		has_long_int_type() const
		{
			return type_category_ == type_category::LONG_INT;
		}

		inline
		bool
		has_unsigned_char_type() const
		{
			return type_category_ == type_category::UNSIGNED_CHAR;
		}

		inline
		bool
		has_unsigned_short_int_type() const
		{
			return type_category_ == type_category::UNSIGNED_SHORT_INT;
		}

		inline
		bool
		has_unsigned_int_type() const
		{
			return type_category_ == type_category::UNSIGNED_INT;
		}

		inline
		bool
		has_unsigned_long_int_type() const
		{
			return type_category_ == type_category::UNSIGNED_LONG_INT;
		}

		inline
		bool
		has_float_type() const
		{
			return type_category_ == type_category::FLOAT;
		}

		inline
		bool
		has_double_type() const
		{
			return type_category_ == type_category::DOUBLE;
		}

		inline
		bool
		has_long_double_type() const
		{
			return type_category_ == type_category::LONG_DOUBLE;
		}



		//
		//type categories
		//

		inline
		bool
		has_integral_type() const
		{
			switch(type_category_)
			{
				case type_category::BOOL:
				case type_category::CHAR:
				case type_category::WCHAR_T:
				case type_category::INT:
				case type_category::LONG_INT:
				case type_category::LONG_LONG_INT:
				case type_category::SHORT_INT:
				case type_category::SIGNED_CHAR:
				case type_category::UNSIGNED_CHAR:
				case type_category::UNSIGNED_INT:
				case type_category::UNSIGNED_LONG_INT:
				case type_category::UNSIGNED_LONG_LONG_INT:
				case type_category::UNSIGNED_SHORT_INT:
					return true;
				default:
					return false;
			}
		}

		inline
		bool
		has_floating_type() const
		{
			switch(type_category_)
			{
				case type_category::FLOAT:
				case type_category::DOUBLE:
				case type_category::LONG_DOUBLE:
					return true;
				default:
					return false;
			}
		}

		inline
		bool
		has_arithmetic_type() const
		{
			return has_integral_type() || has_floating_type();
		}

		inline
		bool
		has_enumeration_type() const
		{
			return type_category_ == type_category::ENUMERATION;
		}

		inline
		bool
		has_pointer_to_defined_type_type() const
		{
			return type_category_ == type_category::POINTER_TO_DEFINED_TYPE;
		}

		inline
		bool
		has_arithmetic_or_enumeration_type() const
		{
			return has_arithmetic_type() || has_enumeration_type();
		}

		inline
		bool
		has_integral_or_enumeration_type() const
		{
			return has_integral_type() || has_enumeration_type();
		}



		//
		//other categories
		//

		inline
		bool
		is_bit_field() const
		{
			return is_bit_field_;
		}

	private:
		static const get_category_visitor_t get_category_visitor;
		static const is_bit_field_visitor_t is_bit_field_visitor;

		const type_category type_category_;
		const bool is_bit_field_;
};

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

#endif

