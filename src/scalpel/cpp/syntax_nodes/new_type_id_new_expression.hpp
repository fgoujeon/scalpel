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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NEW_TYPE_ID_NEW_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NEW_TYPE_ID_NEW_EXPRESSION_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "new_placement.hpp"
#include "new_type_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class new_initializer;

/**
new_type_id_new_expression
	= !(str_p("::") >> !s) >> str_p("new") >> !s >> !(new_placement >> !s) >> new_type_id >> !(!s >> new_initializer)
;
*/
class new_type_id_new_expression: public composite_node
{
	public:
		new_type_id_new_expression
		(
			bool leading_double_colon,
			boost::optional<space>&& post_double_colon_space_node,
			boost::optional<space>&& post_new_keyword_space_node,
			boost::optional<new_placement>&& new_placement_node,
			boost::optional<space>&& post_new_placement_space_node,
			new_type_id&& new_type_id_node,
			boost::optional<space>&& pre_new_initializer_space_node,
			boost::optional<new_initializer>&& new_initializer_node
		);

		new_type_id_new_expression(const new_type_id_new_expression& o);

		new_type_id_new_expression(new_type_id_new_expression&& o);

		const new_type_id_new_expression&
		operator=(const new_type_id_new_expression& o);

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		boost::optional<space> post_double_colon_space_;
		boost::optional<space> post_new_keyword_space_;
		boost::optional<new_placement> new_placement_;
		boost::optional<space> post_new_placement_space_;
		new_type_id new_type_id_;
		boost::optional<space> pre_new_initializer_space_;
		std::unique_ptr<new_initializer> new_initializer_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
