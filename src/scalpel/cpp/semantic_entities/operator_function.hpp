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
#include "statement_block.hpp"
#include "simple_function.hpp"
#include "type.hpp"
#include <list>
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
			std::shared_ptr<const type> return_type,
			parameters_t&& parameters,
			const bool is_static_specified
		);

		//move constructor
		operator_function(operator_function&& f);

		const operator_function&
		operator=(operator_function&& f);

		bool
		operator==(const operator_function& f) const;

		bool
		has_same_signature(const operator_function& f) const;

		bool
		has_same_parameters(const operator_function& f) const;

		operator_
		get_operator() const;

		std::shared_ptr<const type>
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		static_specified() const;

		bool
		defined() const;

		void
		defined(bool d);

    private:
        operator_ op_;
		statement_block statement_block_;
		std::shared_ptr<const type> return_type_;
		parameters_t parameters_;
		bool static_specified_;
		bool defined_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
