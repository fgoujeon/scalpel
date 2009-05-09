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
#include <boost/optional.hpp>
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
            boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
			boost::optional<space>&& post_decl_specifier_seq_space,
            declarator&& a_declarator,
			boost::optional<space>&& post_declarator_space,
            boost::optional<ctor_initializer>&& a_ctor_initializer,
			boost::optional<space>&& post_ctor_initializer_space,
            boost::optional<compound_statement>&& compound_statement_node,
			boost::optional<function_try_block>&& function_try_block_node
        );

		function_definition(const function_definition& o);

		function_definition(function_definition&& o);

		const function_definition&
		operator=(const function_definition& o);

		inline
		const boost::optional<const decl_specifier_seq&>
		decl_specifier_seq_node() const;

		inline
		const boost::optional<const space&>
		post_decl_specifier_seq_space_node() const;

		inline
		const declarator&
		declarator_node() const;

		inline
		const boost::optional<const space&>
		post_declarator_space_node() const;

		inline
		const boost::optional<const ctor_initializer&>
		ctor_initializer_node() const;

		inline
		const boost::optional<const compound_statement&>
		compound_statement_node() const;

    private:
		void
		update_node_list();

		boost::optional<decl_specifier_seq> decl_specifier_seq_;
		boost::optional<space> post_decl_specifier_seq_space_;
		std::shared_ptr<declarator> declarator_;
		boost::optional<space> post_declarator_space_;
		boost::optional<ctor_initializer> ctor_initializer_;
		boost::optional<space> post_ctor_initializer_space_;
		boost::optional<compound_statement> compound_statement_;
		boost::optional<function_try_block> function_try_block_;
};

inline
const boost::optional<const decl_specifier_seq&>
function_definition::decl_specifier_seq_node() const
{
	if(decl_specifier_seq_)
		return boost::optional<const decl_specifier_seq&>(*decl_specifier_seq_);
	else
		return boost::optional<const decl_specifier_seq&>();
}

inline
const boost::optional<const space&>
function_definition::post_decl_specifier_seq_space_node() const
{
	return boost::optional<const space&>(post_decl_specifier_seq_space_);
}

inline
const declarator&
function_definition::declarator_node() const
{
	return *declarator_;
}

inline
const boost::optional<const space&>
function_definition::post_declarator_space_node() const
{
	return boost::optional<const space&>(post_declarator_space_);
}

inline
const boost::optional<const ctor_initializer&>
function_definition::ctor_initializer_node() const
{
	return boost::optional<const ctor_initializer&>(ctor_initializer_);
}

inline
const boost::optional<const compound_statement&>
function_definition::compound_statement_node() const
{
	return boost::optional<const compound_statement&>(compound_statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
