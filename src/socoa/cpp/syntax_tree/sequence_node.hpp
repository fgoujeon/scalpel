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

#ifndef SOCOA_CPP_SYNTAX_TREE_SEQUENCE_NODE_HPP
#define SOCOA_CPP_SYNTAX_TREE_SEQUENCE_NODE_HPP

#include "../../util/sequence.hpp"
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

template<class T, const std::string& Separator = util::extern_strings::space>
class sequence_node: public composite_node
{
    public:
		typedef util::sequence<T, Separator> seq_t;
		typedef typename seq_t::type type;
		typedef typename seq_t::const_iterator const_iterator;

        sequence_node();

        sequence_node(sequence_node&& s);

		const_iterator
		begin() const
		{
			return seq_.begin();
		}

		const_iterator
		end() const
		{
			return seq_.end();
		}

		void
		push_back(T&& t)
		{
			seq_.push_back(t);
		}

		static const std::string& separator;

	private:
		seq_t seq_;
};

template<class T, const std::string& Separator>
sequence_node<T, Separator>::sequence_node()
{
}

template<class T, const std::string& Separator>
sequence_node<T, Separator>::sequence_node(sequence_node&& s):
	seq_(std::move(s.seq_))
{
}

template<class T, const std::string& Separator>
const std::string&
sequence_node<T, Separator>::separator = Separator;

}}} //namespace socoa::cpp::syntax_tree

#endif
