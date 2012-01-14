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

#include "decl_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;

type_specifier_seq_type
get_decl_specifier_seq_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return syntax_node_analysis::get_type_specifier_seq_type(to_type_specifier_seq(decl_specifier_seq_node));
}

syntax_nodes::type_specifier_seq
to_type_specifier_seq(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	syntax_nodes::type_specifier_seq type_specifier_seq_node;
	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const syntax_nodes::decl_specifier& decl_specifier_node = *i;

		if(boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			const type_specifier& type_specifier_node = *opt_type_specifier_node;
			type_specifier_seq_node.push_back(type_specifier_node);
		}
	}

	return type_specifier_seq_node;
}

const syntax_nodes::class_specifier&
get_class_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			const type_specifier& type_specifier_node = *opt_type_specifier_node;

			if(const boost::optional<const class_specifier&> opt_class_specifier_node = get<class_specifier>(&type_specifier_node))
			{
				return *opt_class_specifier_node;
			}
		}
	}

	assert(false);
}

const syntax_nodes::enum_specifier&
get_enum_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			const type_specifier& type_specifier_node = *opt_type_specifier_node;

			if(const boost::optional<const enum_specifier&> opt_enum_specifier_node = get<enum_specifier>(&type_specifier_node))
			{
				return *opt_enum_specifier_node;
			}
		}
	}

	assert(false);
}

const syntax_nodes::class_elaborated_specifier&
get_class_elaborated_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	assert(decl_specifier_seq_node.size() == 1);

	const decl_specifier& decl_specifier_node = decl_specifier_seq_node.front();

	const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node);
	assert(opt_type_specifier_node);

	const type_specifier& type_specifier_node = *opt_type_specifier_node;

	const boost::optional<const elaborated_type_specifier&> opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node);
	assert(opt_elaborated_type_specifier_node);

	const elaborated_type_specifier& elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

	const boost::optional<const class_elaborated_specifier&> opt_class_elaborated_specifier_node = get<class_elaborated_specifier>(&elaborated_type_specifier_node);
	assert(opt_class_elaborated_specifier_node);

	return *opt_class_elaborated_specifier_node;
}

bool
has_typedef_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(get<predefined_text_node<utility::extern_strings::typedef_>>(&decl_specifier_node))
			return true;
	}

	return false;
}

bool
has_friend_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(get<predefined_text_node<utility::extern_strings::friend_>>(&decl_specifier_node))
			return true;
	}

	return false;
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

