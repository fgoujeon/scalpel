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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_SIMPLE_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_SIMPLE_FUNCTION_HPP

#include "variable.hpp"
#include "statement_block.hpp"
#include "named_entity.hpp"
#include "named_scope.hpp"
#include "type.hpp"
#include <string>
#include <list>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ non-special function (which is neither a constructor nor an
operator function nor a conversion function).
*/
class simple_function: public named_scope, public named_entity
{
    public:
		class parameter;

		typedef std::list<parameter> parameters_t;

        simple_function
		(
			const std::string& name,
			std::shared_ptr<const type> return_type,
			parameters_t&& parameters = parameters_t(),
			bool is_static_specified = false
		);

		//copy constructor
		simple_function(const simple_function& f);

		//move constructor
		simple_function(simple_function&& f);

		const simple_function&
		operator=(const simple_function& f);

		const simple_function&
		operator=(simple_function&& f);

		bool
		operator==(const simple_function& f) const;

		bool
		has_same_signature(const simple_function& f) const;

		bool
		has_same_parameters(const simple_function& f) const;

        /**
        @return the name of the function
        */
        const std::string&
        name() const;

        /**
        @return false
        */
        bool
        is_a_type() const;

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

		named_scopes_t::range
        named_scopes();

		named_scopes_t::const_range
        named_scopes() const;

		named_entities_t::range
		named_entities();

		named_entities_t::const_range
		named_entities() const;

    private:
        std::string name_;
		std::shared_ptr<const type> return_type_;
		std::list<parameter> parameters_;
		bool static_specified_;
		bool defined_;

		//polymorphic containers
		named_scopes_t named_scopes_;
		named_entities_t named_entities_;

		statement_block statement_block_;
};

class simple_function::parameter
{
	public:
		parameter(std::shared_ptr<const type> t, const std::string& name);

		parameter(const parameter& o);

		parameter(parameter&& o);

		const parameter&
		operator=(const parameter& o);

		const parameter&
		operator=(parameter&& o);

		bool
		operator==(const parameter& o) const;

		std::shared_ptr<const type>
		get_type() const;

		const std::string&
		name() const;

	private:
		std::shared_ptr<const type> type_;
		std::string name_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

