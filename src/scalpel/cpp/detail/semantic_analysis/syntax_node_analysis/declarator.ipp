/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SYNTAX_NODE_ANALYSIS_DECLARATOR_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SYNTAX_NODE_ANALYSIS_DECLARATOR_IPP

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace syntax_node_analysis
{

template<const std::string& Qualifier>
bool
has_qualifier(const syntax_nodes::declarator& declarator_node)
{
	using namespace syntax_nodes;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			auto last_part_node = i->main_node();
			if(auto opt_function_part_node = get<direct_declarator_function_part>(&last_part_node))
			{
				auto function_part_node = *opt_function_part_node;
				if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(function_part_node))
				{
					auto cv_qualifier_seq_node = *opt_cv_qualifier_seq_node;
					for(auto j = cv_qualifier_seq_node.begin(); j != cv_qualifier_seq_node.end(); ++j)
					{
						auto cv_qualifier_node = j->main_node();
						if(get<predefined_text_node<Qualifier>>(&cv_qualifier_node))
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::syntax_node_analysis

#endif

