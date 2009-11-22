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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_HPP

#include <string>
#include <list>
#include <memory>
#include <boost/noncopyable.hpp>
#include "type.hpp"
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_entity.hpp"
#include "statement_block.hpp"
#include "variable.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class class_;

/**
Represents a C++ function.
*/
class function:
	public scope,
	public named_entity,
	public boost::noncopyable
{
    public:
		class parameter;

		typedef std::list<parameter> parameters_t;

        function
		(
			const std::string& name,
			const type& return_type,
			std::list<parameter>&& parameters,
			bool is_static_specified
		);

		//move constructor
		function(function&& f);

		const function&
		operator=(function&& f);

		void
		accept(scope_visitor& v);

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

        /**
        @return false, because a function cannot be the global namespace...
        */
        bool
        is_global() const;

		scope_iterator_range
        scopes();

		scope_const_iterator_range
        scopes() const;

		named_entity_iterator_range
		named_entities();

		named_entity_const_iterator_range
		named_entities() const;

		const type&
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		static_specified() const;

    private:
		scope_impl scope_impl_;
        std::string name_;
		statement_block statement_block_;
		const type* return_type_;
		std::list<parameter> parameters_;
		bool static_specified_;
};

class function::parameter
{
	public:
		parameter(const type& t, const std::string& name);

		parameter(const parameter&) = delete;

		parameter(parameter&& o);

		const parameter&
		operator=(const parameter&) = delete;

		const type&
		get_type() const;

		const std::string&
		name() const;

	private:
		const type& type_;
		std::string name_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
