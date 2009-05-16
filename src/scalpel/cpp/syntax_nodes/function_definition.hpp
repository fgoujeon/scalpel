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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FUNCTION_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FUNCTION_DEFINITION_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "decl_specifier_seq.hpp"
#include "ctor_initializer.hpp"
#include "space.hpp"
#include "compound_statement.hpp"
#include "function_try_block.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class declarator;

/**
\verbatim
function_definition
	= [decl_specifier_seq], declarator, [ctor_initializer], compound_statement
	| [decl_specifier_seq], declarator, [function_try_block]
;
\endverbatim
*/
class function_definition: public composite_node
{
	public:
        function_definition
        (
            optional_node<decl_specifier_seq>&& a_decl_specifier_seq,
			optional_node<space>&& post_decl_specifier_seq_space,
            declarator&& a_declarator,
			optional_node<space>&& post_declarator_space,
            optional_node<ctor_initializer>&& a_ctor_initializer,
			optional_node<space>&& post_ctor_initializer_space,
            optional_node<compound_statement>&& compound_statement_node,
			optional_node<function_try_block>&& function_try_block_node
        );

		function_definition(const function_definition& o);

		function_definition(function_definition&& o);

		const function_definition&
		operator=(const function_definition& o);

		inline
		const optional_node<decl_specifier_seq>&
		decl_specifier_seq_node() const;

		inline
		const optional_node<space>&
		post_decl_specifier_seq_space_node() const;

		inline
		const declarator&
		declarator_node() const;

		inline
		const optional_node<space>&
		post_declarator_space_node() const;

		inline
		const optional_node<ctor_initializer>&
		ctor_initializer_node() const;

		inline
		const optional_node<compound_statement>&
		compound_statement_node() const;

    private:
		void
		update_node_list();

		optional_node<decl_specifier_seq> decl_specifier_seq_;
		optional_node<space> post_decl_specifier_seq_space_;
		std::unique_ptr<declarator> declarator_;
		optional_node<space> post_declarator_space_;
		optional_node<ctor_initializer> ctor_initializer_;
		optional_node<space> post_ctor_initializer_space_;
		optional_node<compound_statement> compound_statement_;
		optional_node<function_try_block> function_try_block_;
};

inline
const optional_node<decl_specifier_seq>&
function_definition::decl_specifier_seq_node() const
{
	return decl_specifier_seq_;
}

inline
const optional_node<space>&
function_definition::post_decl_specifier_seq_space_node() const
{
	return post_decl_specifier_seq_space_;
}

inline
const declarator&
function_definition::declarator_node() const
{
	return *declarator_;
}

inline
const optional_node<space>&
function_definition::post_declarator_space_node() const
{
	return post_declarator_space_;
}

inline
const optional_node<ctor_initializer>&
function_definition::ctor_initializer_node() const
{
	return ctor_initializer_;
}

inline
const optional_node<compound_statement>&
function_definition::compound_statement_node() const
{
	return compound_statement_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
