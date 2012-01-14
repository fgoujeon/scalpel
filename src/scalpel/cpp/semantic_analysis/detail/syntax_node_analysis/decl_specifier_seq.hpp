/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_DECL_SPECIFIER_SEQ_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_DECL_SPECIFIER_SEQ_HPP

#include "type_specifier_seq.hpp"
#include <scalpel/cpp/syntax_tree.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

type_specifier_seq_type
get_decl_specifier_seq_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

syntax_nodes::type_specifier_seq
to_type_specifier_seq(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_specifier&
get_class_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::enum_specifier&
get_enum_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_elaborated_specifier&
get_class_elaborated_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

template<class SpecifierNodeT, const std::string& Specifier>
bool
has_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

inline
bool
has_inline_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::inline_>(decl_specifier_seq_node);
}

inline
bool
has_virtual_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::virtual_>(decl_specifier_seq_node);
}

inline
bool
has_explicit_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::explicit_>(decl_specifier_seq_node);
}

inline
bool
has_static_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::static_>(decl_specifier_seq_node);
}

inline
bool
has_mutable_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::mutable_>(decl_specifier_seq_node);
}

bool
has_typedef_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

bool
has_friend_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

#include "decl_specifier_seq.ipp"

#endif

