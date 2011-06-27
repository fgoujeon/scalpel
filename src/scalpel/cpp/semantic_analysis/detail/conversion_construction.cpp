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

#include "conversion_construction.hpp"
#include <scalpel/cpp/semantic_entities/conversions.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace semantic_entities;
using namespace semantic_entity_analysis;

namespace
{
	class create_conversion_visitor: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			create_conversion_visitor(const semantic_entities::expression_t& expr):
				expr_(expr)
			{
			}

			semantic_entities::expression_t
			operator()(const array& /*type*/) const
			{
				return expr_; //TODO
			}

			semantic_entities::expression_t
			operator()(const fundamental_type& type) const
			{
				switch(type)
				{
					case fundamental_type::BOOL:
						return create_boolean_conversion(expr_);
					case fundamental_type::CHAR:
					case fundamental_type::DOUBLE:
					case fundamental_type::FLOAT:
					case fundamental_type::INT:
					case fundamental_type::LONG_DOUBLE:
					case fundamental_type::LONG_INT:
					case fundamental_type::LONG_LONG_INT:
					case fundamental_type::SHORT_INT:
					case fundamental_type::SIGNED_CHAR:
					case fundamental_type::UNSIGNED_CHAR:
					case fundamental_type::UNSIGNED_INT:
					case fundamental_type::UNSIGNED_LONG_INT:
					case fundamental_type::UNSIGNED_LONG_LONG_INT:
					case fundamental_type::UNSIGNED_SHORT_INT:
					case fundamental_type::VOID:
					case fundamental_type::WCHAR_T:
						return expr_; //TODO
				}

				assert(false);
			}

			semantic_entities::expression_t
			operator()(const function_type& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(class_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_class* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(union_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(anonymous_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(anonymous_member_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const cv_qualified_type& type) const
			{
				return apply_visitor(*this, type.qualified_type());
			}

			semantic_entities::expression_t
			operator()(enum_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_enum* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const pointer& /*type*/) const
			{
				return expr_; //TODO
			}

			semantic_entities::expression_t
			operator()(const pointer_to_member& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const reference& type) const
			{
				return apply_visitor(*this, type.qualified_type());
			}

		private:
			const semantic_entities::expression_t& expr_;
	};
}

semantic_entities::expression_t
create_conversion
(
	const semantic_entities::expression_t& expr,
	const semantic_entities::type_variant& destination_type
)
{
	create_conversion_visitor visitor(expr);
	return apply_visitor(visitor, destination_type);
}



semantic_entities::expression_t
create_conversion_to_long_int(const semantic_entities::expression_t& expr)
{
	return conversion_to_long_int(expr);
}

semantic_entities::expression_t
create_conversion_to_unsigned_int(const semantic_entities::expression_t& expr)
{
	return conversion_to_unsigned_int(expr);
}

semantic_entities::expression_t
create_conversion_to_unsigned_long_int(const semantic_entities::expression_t& expr)
{
	return conversion_to_unsigned_long_int(expr);
}

semantic_entities::expression_t
create_conversion_to_float(const semantic_entities::expression_t& expr)
{
	return conversion_to_float(expr);
}

semantic_entities::expression_t
create_conversion_to_double(const semantic_entities::expression_t& expr)
{
	return conversion_to_double(expr);
}

semantic_entities::expression_t
create_conversion_to_long_double(const semantic_entities::expression_t& expr)
{
	return conversion_to_long_double(expr);
}

semantic_entities::expression_t
create_boolean_conversion(const semantic_entities::expression_t& expr)
{
	if(get_type(expr) == type_variant(fundamental_type::BOOL))
		return expr;
	else
		return boolean_conversion(expr);
}



namespace
{
	template<typename T, typename U, bool TSigned, bool USigned>
	struct can_represent_all_the_values_of_base;

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, false, false>
	{
		static const bool value =
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, false, true>
	{
		static const bool value = false;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, true, false>
	{
		static const bool value =
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, true, true>
	{
		static const bool value =
			std::numeric_limits<T>::min() <= std::numeric_limits<U>::min() &&
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of
	{
		static const bool value =
			can_represent_all_the_values_of_base
			<
				T,
				U,
				std::numeric_limits<T>::is_signed,
				std::numeric_limits<U>::is_signed
			>::value
		;
	};
}

semantic_entities::expression_t
create_integral_promotions
(
	const semantic_entities::expression_t& source,
	const type_category source_type_category
)
{
	//An rvalue of type char, signed char, unsigned char, short int, or
	//unsigned short int can be converted to an rvalue of type int if int can
	//represent all the values of the source type.
	//Otherwise, the source rvalue can be converted to an rvalue of type
	//unsigned int.
	if(is_char(source_type_category))
	{
		if(can_represent_all_the_values_of<int, char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(is_signed_char(source_type_category))
	{
		if(can_represent_all_the_values_of<int, signed char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(is_unsigned_char(source_type_category))
	{
		if(can_represent_all_the_values_of<int, unsigned char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(is_short_int(source_type_category))
	{
		if(can_represent_all_the_values_of<int, short int>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(is_unsigned_short_int(source_type_category))
	{
		if(can_represent_all_the_values_of<int, unsigned short int>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	//An rvalue of type wchar_t or an enumeration type can be converted to an
	//rvalue of the first of the following types that can represent all the
	//values of its underlying type: int, unsigned int, long, or unsigned long.
	else if(is_wchar_t(source_type_category))
	{
		if(can_represent_all_the_values_of<int, wchar_t>::value)
			return conversion_to_int(source);
		else if(can_represent_all_the_values_of<unsigned int, wchar_t>::value)
			return conversion_to_unsigned_int(source);
		else if(can_represent_all_the_values_of<long int, wchar_t>::value)
			return conversion_to_long_int(source);
		else if(can_represent_all_the_values_of<unsigned long int, wchar_t>::value)
			return conversion_to_unsigned_long_int(source);
		else
			assert(false);
	}
	else if(is_enumeration(source_type_category))
	{
		assert(false); //TODO
	}
	//An rvalue for an integral bit-field can be converted to an rvalue
	//of type int if int can represent all the values of the bit-field; otherwise,
	//it can be converted to unsigned int if unsigned int can represent all the
	//values of the bit-field. If the bit-field is larger yet, no integral
	//promotion applies to it. If the bit-field has an enumerated type, it is
	//treated as any other value of that type for promotion purposes.
	else if(false)
	{
		//TODO
	}
	//An rvalue of type bool can be converted to an rvalue of type int, with
	//false becoming zero and true becoming one.
	else if(is_bool(source_type_category))
	{
		return conversion_to_int(source);
	}
	else
	{
		return source;
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

