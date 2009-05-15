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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BRACKETED_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BRACKETED_NODE_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
class bracketed_node: public composite_node
{
    public:
		explicit
        bracketed_node
		(
			boost::optional<space>&& post_opening_bracket_space_node,
			SyntaxNodeT&& main_node,
			boost::optional<space>&& post_main_space_node
		);

        bracketed_node(const bracketed_node& o);

        bracketed_node(bracketed_node&& o);

        const bracketed_node&
		operator=(const bracketed_node& o);

		const bracketed_node&
		operator=(bracketed_node&& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_opening_bracket_space_;
		SyntaxNodeT main_;
		boost::optional<space> post_main_space_;
};


template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::bracketed_node
(
	boost::optional<space>&& post_opening_bracket_space_node,
	SyntaxNodeT&& main_node,
	boost::optional<space>&& post_main_space_node
):
	post_opening_bracket_space_(std::move(post_opening_bracket_space_node)),
	main_(std::move(main_node)),
	post_main_space_(std::move(post_main_space_node))
{
}

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::bracketed_node(const bracketed_node& o):
	composite_node(),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	main_(o.main_),
	post_main_space_(o.post_main_space_)
{
	update_node_list();
}

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::bracketed_node(bracketed_node&& o):
	composite_node(),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	main_(std::move(o.main_)),
	post_main_space_(std::move(o.post_main_space_))
{
	update_node_list();
}

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
const bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>&
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::operator=(const bracketed_node& o)
{
	bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode> copy(o);
	std::swap(copy, *this);
	return *this;
}

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
const bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>&
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::operator=(bracketed_node&& o)
{
	post_opening_bracket_space_ = std::move(o.post_opening_bracket_space_);
	main_ = std::move(o.main_);
	post_main_space_ = std::move(o.post_main_space_);
	update_node_list();
	return *this;
}

template<const leaf_node& OpeningBracketNode, class SyntaxNodeT, const leaf_node& ClosingBracketNode>
void
bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>::update_node_list()
{
	clear();
	add(OpeningBracketNode);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	add(main_);
	if(post_main_space_) add(*post_main_space_);
	add(ClosingBracketNode);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
