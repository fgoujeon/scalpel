/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP

#include "variable.hpp"
#include <string>
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class class_;

/**
Represents a C++ statement block.
*/
class statement_block
{
    public:
        statement_block();

		statement_block(const statement_block& o);

		statement_block(statement_block&& o);

		const statement_block&
		operator=(const statement_block& o);

		const statement_block&
		operator=(statement_block&& o);

		bool
		operator==(const statement_block& o) const;

		void
		add(std::shared_ptr<statement_block> o);

		void
		add(std::shared_ptr<variable> o);

    private:
		std::vector<std::shared_ptr<statement_block>> statement_blocks_;
		std::vector<std::shared_ptr<variable>> variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
