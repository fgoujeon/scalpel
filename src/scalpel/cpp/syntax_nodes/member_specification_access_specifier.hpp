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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "access_specifier.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_specification_access_specifier
	= access_specifier >> !s >> ':'
;
*/
class member_specification_access_specifier: public composite_node
{
	public:
		explicit
		member_specification_access_specifier
		(
			access_specifier&& a_access_specifier,
			boost::optional<space>&& post_access_specifier_node
		);

		member_specification_access_specifier(const member_specification_access_specifier& o);

		member_specification_access_specifier(member_specification_access_specifier&& o);

		const member_specification_access_specifier&
		operator=(const member_specification_access_specifier& o);

		inline
		const access_specifier&
	   	access_specifier_node() const;

	private:
		void
		update_node_list();

		access_specifier access_specifier_;
		boost::optional<space> post_access_specifier_;
};

inline
const access_specifier&
member_specification_access_specifier::access_specifier_node() const
{
	return access_specifier_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif