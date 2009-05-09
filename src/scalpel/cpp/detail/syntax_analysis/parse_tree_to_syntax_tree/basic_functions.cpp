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

#include "basic_functions.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

tree_node_iterator_t
find_child_node(const tree_node_t& parent_node, grammar::parser_id child_id)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        boost::spirit::parser_id id = child_node.value.id();
        if(id == child_id)
        {
            return i;
        }
    }

    return parent_node.children.end();
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return get_value(parent_node.children[position]) == value;
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        if(get_value(child_node) == value)
        {
            return true;
        }
    }

    return false;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id,
    unsigned int position
)
{
    if(parent_node.children.size() <= position)
        return false;

    return parent_node.children[position].value.id() == id;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id
)
{
    for
    (
        tree_node_iterator_t i = parent_node.children.begin();
        i != parent_node.children.end();
        ++i
    ) //for each child
    {
        const tree_node_t& child_node = *i;
        const boost::spirit::parser_id child_id = child_node.value.id();

        if(child_id == id)
        {
            return true;
        }
    }

    return false;
}

tree_node_iterator_t
find_node(const tree_node_t& parent_node, const std::string& value)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        if(get_value(child_node) == value)
        {
            return i;
        }
    }

    return parent_node.children.end();
}

std::string
get_only_child_value(const tree_node_t& node)
{
    assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    return get_value(child_node);
}

std::string
get_value(const tree_node_t& node)
{
    //get value
    std::ostringstream value_oss;
    for
    (
        tree_node_value_iterator_t i = node.value.begin();
        i != node.value.end();
        ++i
    ) //iterate node value
    {
        value_oss << *i;
    }

    return value_oss.str();
}

int
get_id(const tree_node_t& node)
{
    boost::spirit::parser_id id = node.value.id();

    for(unsigned int i = 0; i < 400; ++i)
    {
        if(id == i)
        {
            return i;
        }
    }

    return -1;
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

