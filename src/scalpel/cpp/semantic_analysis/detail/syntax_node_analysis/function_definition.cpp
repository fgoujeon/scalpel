/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "declarator.hpp"
#include "type_specifier_seq.hpp"
#include <stdexcept>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;

const optional_node<decl_specifier_seq>&
get_decl_specifier_seq
(
	const syntax_nodes::function_definition& function_definition_node
)
{
	if
	(
		const boost::optional<const simple_function_definition&> opt_simple_function_definition =
			get<simple_function_definition>(&function_definition_node)
	)
		return get_decl_specifier_seq(*opt_simple_function_definition);
	else if
	(
		const boost::optional<const try_block_function_definition&> opt_try_block_function_definition =
			get<try_block_function_definition>(&function_definition_node)
	)
		return get_decl_specifier_seq(*opt_try_block_function_definition);
	else
		assert(false);
}

const syntax_nodes::declarator&
get_declarator
(
	const syntax_nodes::function_definition& function_definition_node
)
{
	if
	(
		const boost::optional<const simple_function_definition&> opt_simple_function_definition =
			get<simple_function_definition>(&function_definition_node)
	)
		return get_declarator(*opt_simple_function_definition);
	else if
	(
		const boost::optional<const try_block_function_definition&> opt_try_block_function_definition =
			get<try_block_function_definition>(&function_definition_node)
	)
		return get_declarator(*opt_try_block_function_definition);
	else
		assert(false);
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

