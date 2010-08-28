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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP

#include "operator_.hpp"
#include "simple_function.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ operator simple_function.
*/
class operator_function
{
    public:
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

        operator_function
		(
			const operator_ op,
			const type_shared_ptr_variant& return_type,
			parameters_t&& parameters,
			const bool is_is_inline
		);

		//move constructor
		operator_function(operator_function&& rhs);

		const operator_function&
		operator=(operator_function&& rhs);

		operator_
		get_operator() const;

		const type_shared_ptr_variant&
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		is_inline() const;

		bool
		defined() const;

		void
		defined(const bool d);

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

    private:
		simple_function impl_;
        operator_ op_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

