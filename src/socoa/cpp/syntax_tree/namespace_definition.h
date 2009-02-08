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

#ifndef SOCOA_CPP_SYNTAX_TREE_NAMESPACE_DEFINITION_H
#define SOCOA_CPP_SYNTAX_TREE_NAMESPACE_DEFINITION_H

#include <memory>
#include <string>
#include "visitor.h"
#include "declaration.h"
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class identifier;

class namespace_definition: public declaration
{
	public:
		namespace_definition
		(
			std::shared_ptr<identifier> an_identifier,
			std::shared_ptr<util::sequence<declaration>> a_declaration_seq
		);

		inline
		const std::shared_ptr<const identifier>
	   	get_identifier() const;

		inline
		const std::shared_ptr<const util::sequence<declaration>>
		get_declaration_seq() const;

		SOCOA_CPP_DEFINE_VISITABLE()

	private:
		std::shared_ptr<identifier> identifier_;
		std::shared_ptr<util::sequence<declaration>> declaration_seq_;
};

inline
const std::shared_ptr<const identifier>
namespace_definition::get_identifier() const
{
	return identifier_;
}

inline
const std::shared_ptr<const util::sequence<declaration>>
namespace_definition::get_declaration_seq() const
{
	return declaration_seq_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
