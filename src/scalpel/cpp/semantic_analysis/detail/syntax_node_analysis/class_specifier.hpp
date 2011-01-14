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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_CLASS_SPECIFIER_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_CLASS_SPECIFIER_HPP

#include <scalpel/cpp/syntax_tree.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

std::string
get_identifier(const syntax_nodes::class_specifier& class_specifier_node);

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

#endif

