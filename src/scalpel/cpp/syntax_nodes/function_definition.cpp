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

#include "function_definition.hpp"

#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

function_definition::function_definition
(
	boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
	boost::optional<space>&& post_decl_specifier_seq_space,
	declarator&& a_declarator,
	boost::optional<space>&& post_declarator_space,
	boost::optional<ctor_initializer>&& a_ctor_initializer,
	boost::optional<space>&& post_ctor_initializer_space,
	boost::optional<compound_statement>&& compound_statement_node,
	boost::optional<function_try_block>&& function_try_block_node
):
    decl_specifier_seq_(a_decl_specifier_seq),
	post_decl_specifier_seq_space_(post_decl_specifier_seq_space),
    declarator_(std::make_shared<declarator>(std::move(a_declarator))),
	post_declarator_space_(post_declarator_space),
    ctor_initializer_(a_ctor_initializer),
	post_ctor_initializer_space_(post_ctor_initializer_space),
    compound_statement_(compound_statement_node),
	function_try_block_(function_try_block_node)
{
	update_node_list();
}

function_definition::function_definition(const function_definition& o):
	composite_node(),
    decl_specifier_seq_(o.decl_specifier_seq_),
	post_decl_specifier_seq_space_(o.post_decl_specifier_seq_space_),
    declarator_(o.declarator_),
	post_declarator_space_(o.post_declarator_space_),
    ctor_initializer_(o.ctor_initializer_),
	post_ctor_initializer_space_(o.post_ctor_initializer_space_),
    compound_statement_(o.compound_statement_),
	function_try_block_(o.function_try_block_)
{
	update_node_list();
}

function_definition::function_definition(function_definition&& o):
    decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
	post_decl_specifier_seq_space_(std::move(o.post_decl_specifier_seq_space_)),
    declarator_(std::move(o.declarator_)),
	post_declarator_space_(std::move(o.post_declarator_space_)),
    ctor_initializer_(std::move(o.ctor_initializer_)),
	post_ctor_initializer_space_(std::move(o.post_ctor_initializer_space_)),
    compound_statement_(std::move(o.compound_statement_)),
	function_try_block_(std::move(o.function_try_block_))
{
	update_node_list();
}

const function_definition&
function_definition::operator=(const function_definition& o)
{
    decl_specifier_seq_ = o.decl_specifier_seq_;
	post_decl_specifier_seq_space_ = o.post_decl_specifier_seq_space_;
    declarator_ = o.declarator_;
	post_declarator_space_ = o.post_declarator_space_;
    ctor_initializer_ = o.ctor_initializer_;
	post_ctor_initializer_space_ = o.post_ctor_initializer_space_;
    compound_statement_ = o.compound_statement_;
	function_try_block_ = o.function_try_block_;

	update_node_list();

	return *this;
}

void
function_definition::update_node_list()
{
	clear();
	if(decl_specifier_seq_) add(*decl_specifier_seq_);
	if(post_decl_specifier_seq_space_) add(*post_decl_specifier_seq_space_);
	add(*declarator_);
	if(post_declarator_space_) add(*post_declarator_space_);
	if(ctor_initializer_) add(*ctor_initializer_);
	if(post_ctor_initializer_space_) add(*post_ctor_initializer_space_);
    if(compound_statement_) add(*compound_statement_);
	if(function_try_block_) add(*function_try_block_);
}

}}} //namespace scalpel::cpp::syntax_nodes
