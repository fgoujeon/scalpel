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

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace semantic_entities;

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
create_boolean_conversion(const semantic_entities::expression_t& expr)
{
	if(get_type(expr) == type_variant(fundamental_type::BOOL))
		return expr;
	else
		return boolean_conversion(expr);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

