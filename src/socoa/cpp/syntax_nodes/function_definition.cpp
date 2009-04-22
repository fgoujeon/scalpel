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

#include "function_definition.hpp"

#include "declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

function_definition::function_definition
(
	boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
	boost::optional<space>&& post_decl_specifier_seq_space,
	declarator&& a_declarator,
	boost::optional<space>&& pre_ctor_initializer_space,
	boost::optional<ctor_initializer>&& a_ctor_initializer,
	boost::optional<space>&& pre_compound_statement_space,
	boost::optional<compound_statement>&& compound_statement_node
):
    decl_specifier_seq_(a_decl_specifier_seq),
	post_decl_specifier_seq_space_(post_decl_specifier_seq_space),
    declarator_(std::make_shared<declarator>(std::move(a_declarator))),
	pre_ctor_initializer_space_(pre_ctor_initializer_space),
    ctor_initializer_(a_ctor_initializer),
	pre_compound_statement_space_(pre_compound_statement_space),
    compound_statement_(compound_statement_node)
{
	update_node_list();
}

function_definition::function_definition(const function_definition& o):
	composite_node(),
    decl_specifier_seq_(o.decl_specifier_seq_),
	post_decl_specifier_seq_space_(o.post_decl_specifier_seq_space_),
    declarator_(o.declarator_),
	pre_ctor_initializer_space_(o.pre_ctor_initializer_space_),
    ctor_initializer_(o.ctor_initializer_),
	pre_compound_statement_space_(o.pre_compound_statement_space_),
    compound_statement_(o.compound_statement_)
{
	update_node_list();
}

function_definition::function_definition(function_definition&& o):
    decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
	post_decl_specifier_seq_space_(std::move(o.post_decl_specifier_seq_space_)),
    declarator_(std::move(o.declarator_)),
	pre_ctor_initializer_space_(std::move(o.pre_ctor_initializer_space_)),
    ctor_initializer_(std::move(o.ctor_initializer_)),
	pre_compound_statement_space_(std::move(o.pre_compound_statement_space_)),
    compound_statement_(std::move(o.compound_statement_))
{
	update_node_list();
}

const function_definition&
function_definition::operator=(const function_definition& o)
{
    decl_specifier_seq_ = o.decl_specifier_seq_;
	post_decl_specifier_seq_space_ = o.post_decl_specifier_seq_space_;
    declarator_ = o.declarator_;
	pre_ctor_initializer_space_ = o.pre_ctor_initializer_space_;
    ctor_initializer_ = o.ctor_initializer_;
	pre_compound_statement_space_ = o.pre_compound_statement_space_;
    compound_statement_ = o.compound_statement_;

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
	if(pre_ctor_initializer_space_) add(*pre_ctor_initializer_space_);
	if(ctor_initializer_) add(*ctor_initializer_);
	if(pre_compound_statement_space_) add(*pre_compound_statement_space_);
    if(compound_statement_) add(*compound_statement_);
}

}}} //namespace socoa::cpp::syntax_nodes
