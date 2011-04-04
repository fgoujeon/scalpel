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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_DECL_SPECIFIER_SEQ_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SYNTAX_NODE_ANALYSIS_DECL_SPECIFIER_SEQ_IPP

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

template<class SpecifierNodeT, const std::string& Specifier>
bool
has_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	using namespace syntax_nodes;

	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(auto opt_specifier_node = get<SpecifierNodeT>(&decl_specifier_node))
		{
			auto specifier_node = *opt_specifier_node;
			if(get<predefined_text_node<Specifier>>(&specifier_node))
				return true;
		}
	}

	return false;
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

#endif

