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

#ifndef SOCOA_CPP_SYNTAX_NODES_CONVERSION_FUNCTION_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_CONVERSION_FUNCTION_ID_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "type_specifier_seq.hpp"
#include "space.hpp"
#include "ptr_operator_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
conversion_function_id
	= "operator" >> !s >> type_specifier_seq >> !(!s >> ptr_operator_seq)
;
\endverbatim
*/
class conversion_function_id: public composite_node
{
    public:
		conversion_function_id
		(
			boost::optional<space>&& post_operator_keyword_space_node,
			type_specifier_seq&& type_specifier_seq_node,
			boost::optional<space>&& pre_ptr_operator_seq_space_node,
			boost::optional<ptr_operator_seq>&& ptr_operator_seq_node
		);

		conversion_function_id(const conversion_function_id& o);

		conversion_function_id(conversion_function_id&& o);

		const conversion_function_id&
		operator=(const conversion_function_id& o);

    private:
		void
		update_node_list();

		boost::optional<space> post_operator_keyword_space_;
		type_specifier_seq type_specifier_seq_;
		boost::optional<space> pre_ptr_operator_seq_space_;
		boost::optional<ptr_operator_seq> ptr_operator_seq_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
