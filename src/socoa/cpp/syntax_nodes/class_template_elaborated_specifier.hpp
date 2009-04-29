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

#ifndef SOCOA_CPP_SYNTAX_NODES_CLAS_TEMPLATE_ELABORATED_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_CLAS_TEMPLATE_ELABORATED_SPECIFIER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "class_key.hpp"
#include "space.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
class_template_elaborated_specifier
	= class_key, ["::"], [nested_name_specifier], template_id
;
*/
class class_template_elaborated_specifier: public composite_node
{
	public:
		class_template_elaborated_specifier
		(
			class_key&& class_key_node,
			boost::optional<space>&& post_class_key_space_node,
			bool double_colon,
			boost::optional<space>&& post_double_colon_space_node,
			boost::optional<nested_name_specifier>&& nested_name_specifier_node,
			boost::optional<space>&& post_nested_name_specifier_space_node,
			template_id&& template_id_node
		);

		class_template_elaborated_specifier(const class_template_elaborated_specifier& o);

		class_template_elaborated_specifier(class_template_elaborated_specifier&& o);

		const class_template_elaborated_specifier&
		operator=(const class_template_elaborated_specifier& o);

	private:
		void
		update_node_list();

		class_key class_key_;
		boost::optional<space> post_class_key_space_;
		bool double_colon_;
		boost::optional<space> post_double_colon_space_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<space> post_nested_name_specifier_space_;
		template_id template_id_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
