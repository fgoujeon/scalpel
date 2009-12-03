/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP

#include <list>
#include <memory>
#include "type.hpp"
#include "function.hpp"
#include "operator_.hpp"
#include "statement_block.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ operator function.
*/
class operator_function
{
    public:
		typedef function::parameter parameter;
		typedef function::parameters_t parameters_t;

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

		std::shared_ptr<const type>
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		static_specified() const;

    private:
        operator_ op_;
		statement_block statement_block_;
		std::shared_ptr<const type> return_type_;
		parameters_t parameters_;
		bool static_specified_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
