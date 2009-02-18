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

#ifndef SOCOA_CPP_SYNTAX_TREE_NAMESPACE_DEFINITION_IMPL_H
#define SOCOA_CPP_SYNTAX_TREE_NAMESPACE_DEFINITION_IMPL_H

#include <boost/optional.hpp>
#include <string>
#include "identifier.h"
#include "declaration.h"
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class namespace_definition_impl
{
	public:
		namespace_definition_impl
		(
			boost::optional<identifier> an_identifier,
			boost::optional<util::sequence<declaration>> a_declaration_seq
		);

		inline
		const boost::optional<const identifier&>
	   	get_identifier() const;

		inline
		const boost::optional<const util::sequence<declaration>&>
		get_declaration_seq() const;

	private:
		boost::optional<identifier> identifier_;
		boost::optional<util::sequence<declaration>> declaration_seq_;
};

inline
const boost::optional<const identifier&>
namespace_definition_impl::get_identifier() const
{
	return boost::optional<const identifier&>(identifier_);
}

inline
const boost::optional<const util::sequence<declaration>&>
namespace_definition_impl::get_declaration_seq() const
{
	return boost::optional<const util::sequence<declaration>&>(declaration_seq_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
