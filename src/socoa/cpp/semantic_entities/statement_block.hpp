/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP
#define SOCOA_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP

#include <string>
#include <list>
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_entity.hpp"
#include "variable.hpp"

namespace socoa { namespace cpp { namespace semantic_entities
{

class namespace_;
class class_;

/**
Represents a C++ statement block.
*/
class statement_block:
	public scope
{
    public:
        statement_block();

		statement_block(const statement_block&) = delete;

		statement_block(statement_block&& o);

		const statement_block&
		operator=(const statement_block& o) = delete;

		const statement_block&
		operator=(statement_block&& o);

		void
		accept(scope_visitor& v);

        /**
        @return an empty string
        */
        const std::string&
        name() const;

        /**
        @return false
        */
        bool
        is_a_type() const;

        /**
        @return false, because a statement block cannot be the global namespace...
        */
        bool
        is_global() const;

        /**
        @return true if the statement block has an enclosing scope
        */
        bool
        has_enclosing_scope() const;

        /**
        @return the enclosing scope of the statement block
        */
		scope&
        enclosing_scope();

        /**
        @return the enclosing scope of the statement block
        */
        const scope&
        enclosing_scope() const;

        /**
        Sets the enclosing scope of the statement block.
        */
        void
        enclosing_scope(function& enclosing_scope);

        void
        enclosing_scope(statement_block& enclosing_scope);

		scope_iterator_range
        scopes();

		scope_const_iterator_range
        scopes() const;

		named_entity_iterator_range
		named_entities();

		named_entity_const_iterator_range
		named_entities() const;

		void
		add(statement_block&& o);

		void
		add(variable&& v);

    private:
		scope_impl scope_impl_;
		std::list<statement_block> statement_blocks_;
		std::list<variable> variables_;
};

}}} //namespace socoa::cpp::semantic_entities

#endif
