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

#include "namespace_definition.hpp"

#include "declaration_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

namespace_definition::namespace_definition
(
    boost::optional<identifier>&& an_identifier,
    boost::optional<declaration_seq>&& a_declaration_seq
)/*:
    identifier_(an_identifier)*/
{
	if(an_identifier)
		identifier_ = std::move(std::unique_ptr<identifier>(new identifier(std::move(*an_identifier))));

	if(identifier_) add(*identifier_);
	if(a_declaration_seq)
	{
		declaration_seq_ = std::make_shared<declaration_seq>(*a_declaration_seq);
		add(*declaration_seq_);
	}
}

namespace_definition::namespace_definition(namespace_definition&& o):
	identifier_(std::move(o.identifier_)),
	declaration_seq_(std::move(o.declaration_seq_))
{
}

}}} //namespace socoa::cpp::syntax_tree
