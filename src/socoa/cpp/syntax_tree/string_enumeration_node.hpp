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

#ifndef SOCOA_CPP_SYNTAX_TREE_STRING_ENUMERATION_NODE_HPP
#define SOCOA_CPP_SYNTAX_TREE_STRING_ENUMERATION_NODE_HPP

#include <string>
#include "../../util/string_enumeration.hpp"
#include "leaf_node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

template<const std::vector<std::string>& StringList>
class string_enumeration_node: public leaf_node
{
	private:
		typedef util::string_enumeration<StringList> string_enumeration_t;

	public:
        string_enumeration_node(const std::string& value);

        string_enumeration_node(const string_enumeration_node& o);

        string_enumeration_node(string_enumeration_node&& o);

        const string_enumeration_node&
		operator=(const string_enumeration_node& o);

		const std::string&
		value() const;

	private:
		void
		update_node_list();

		string_enumeration_t string_enumeration_;
};

template<const std::vector<std::string>& StringList>
string_enumeration_node<StringList>::string_enumeration_node(const std::string& value):
	leaf_node(" " + value),
	string_enumeration_(value)
{
}

template<const std::vector<std::string>& StringList>
string_enumeration_node<StringList>::string_enumeration_node(const string_enumeration_node& o):
	leaf_node(" " + o.string_enumeration_.value()),
	string_enumeration_(o.string_enumeration_)
{
}

template<const std::vector<std::string>& StringList>
string_enumeration_node<StringList>::string_enumeration_node(string_enumeration_node&& o):
	leaf_node(" " + o.string_enumeration_.value()),
	string_enumeration_(std::move(o.string_enumeration_))
{
}

template<const std::vector<std::string>& StringList>
const string_enumeration_node<StringList>&
string_enumeration_node<StringList>::operator=(const string_enumeration_node& o)
{
	raw_code(" " + o.string_enumeration_.value());
	string_enumeration_ = o.string_enumeration_;
	return *this;
}

template<const std::vector<std::string>& StringList>
const std::string&
string_enumeration_node<StringList>::value() const
{
    return string_enumeration_.value();
}

}}} //namespace socoa::cpp::syntax_tree

#endif
