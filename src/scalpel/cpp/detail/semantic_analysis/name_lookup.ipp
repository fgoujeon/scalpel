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

#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class RangeT>
std::shared_ptr<semantic_entities::named_entity>
name_lookup::find_name
(
	RangeT declarative_region_stack,
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	auto opt_nested_name_specifier_node = get_nested_name_specifier(nested_identifier_or_template_id_node);
	auto identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);

	if(opt_nested_name_specifier_node)
	{
		auto nested_name_specifier_node = *opt_nested_name_specifier_node;
		std::shared_ptr<declarative_region> found_declarative_region = find_declarative_region(declarative_region_stack, nested_name_specifier_node);

		if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
		{
			auto identifier_node = *opt_identifier_node;
			return find_name(*found_declarative_region, identifier_node.value());
		}
		else if(auto template_id_node = get<template_id>(&identifier_or_template_id_node))
		{
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
		{
			auto identifier_node = *opt_identifier_node;
			return find_name(declarative_region_stack, identifier_node.value());
		}
		else if(auto template_id_node = get<template_id>(&identifier_or_template_id_node))
		{
		}
		else
		{
			assert(false);
		}
	}

	throw std::runtime_error("Type not found");
}



template<class RangeT>
std::shared_ptr<semantic_entities::named_entity>
name_lookup::find_name
(
	RangeT declarative_region_stack,
	const std::string& name
)
{
    return find_name(declarative_region_stack, name, true);
}



template<class RangeT>
std::shared_ptr<semantic_entities::named_entity>
name_lookup::find_name
(
	RangeT declarative_region_stack,
	const std::string& name,
	bool recursive_ascent
)
{
	using namespace semantic_entities;

	std::shared_ptr<declarative_region> current_declarative_region = declarative_region_stack.back();

    /*
    1. Current named_declarative_region
    */
	if(std::shared_ptr<named_entity> found_name = find_name(*current_declarative_region, name))
	{
		return found_name;
	}

    /*
    2. Enclosing declarative_regions (recursive ascent call)
    */
	if
	(
		recursive_ascent &&
		declarative_region_stack.size() >= 2 //is there at least an enclosing named_declarative_region?
	)
	{
		auto last_but_one_it = declarative_region_stack.end();
		--last_but_one_it;
		RangeT enclosing_declarative_region_stack(declarative_region_stack.begin(), last_but_one_it);

		if(!enclosing_declarative_region_stack.empty())
		{
			std::shared_ptr<semantic_entities::named_entity> found_name = find_name(enclosing_declarative_region_stack, name, true);
			if(found_name)
			{
				return found_name;
			}
		}
	}


//    /*
//    3. Base classes (non-recursive_ascent)
//    */
//    {
//        const std::list<base_specifier>& base_specifiers = current_declarative_region->get_base_specifiers();
//        for
//        (
//            std::list<base_specifier>::const_iterator i = base_specifiers.begin();
//            i != base_specifiers.end();
//            ++i
//        ) //for each base specifier (== for each base class)
//        {
//            const base_specifier& base_spec = *i;
//            const std::shared_ptr<class_> base_class = base_spec.get_class();
//            const std::shared_ptr<semantic_entities::named_entity> found_symbol = find_name(base_class, name, false);
//            if(found_symbol)
//            {
//                return found_symbol;
//            }
//        }
//    }

	//no name has been found, we return a null pointer
	return std::shared_ptr<semantic_entities::named_entity>();
}



template<class RangeT>
std::shared_ptr<semantic_entities::declarative_region>
name_lookup::find_declarative_region
(
	RangeT declarative_region_stack,
	const syntax_nodes::nested_name_specifier& a_nested_name_specifier
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	std::shared_ptr<declarative_region> found_declarative_region;

	//get the first part of the nested-name-specifier
	const identifier_or_template_id& an_identifier_or_template_id = get_identifier_or_template_id(a_nested_name_specifier);
	boost::optional<const identifier&> an_identifier = get<identifier>(&an_identifier_or_template_id);

	//if the first part is a simple identifier
	if(an_identifier)
	{
		const std::string& declarative_region_name = an_identifier->value();

		//find the named_declarative_region which has that identifier in the current named_declarative_region and in the enclosing declarative_regions
		found_declarative_region = find_declarative_region(declarative_region_stack, declarative_region_name);
	}

	//if the first part named_declarative_region has been found, go on with the next parts
	if(found_declarative_region)
	{
		//is there other parts?
		auto last_part_seq = get_last_part_seq(a_nested_name_specifier);
		if(last_part_seq)
		{
			//for each part...
			for(auto i = last_part_seq->begin(); i != last_part_seq->end(); ++i)
			{
				if(found_declarative_region)
				{
					const nested_name_specifier_last_part& last_part = i->main_node();

					const identifier_or_template_id& an_identifier_or_template_id = get_identifier_or_template_id(last_part);
					boost::optional<const identifier&> an_identifier = get<identifier>(&an_identifier_or_template_id);

					if(an_identifier)
					{
						const std::string& declarative_region_name = an_identifier->value();
						found_declarative_region = find_declarative_region(*found_declarative_region, declarative_region_name);
					}
				}
				else
					break;
			}
		}
	}

	return found_declarative_region;
}



template<class RangeT>
std::shared_ptr<semantic_entities::declarative_region>
name_lookup::find_declarative_region
(
	RangeT declarative_region_stack,
	const std::string& declarative_region_name
)
{
	using namespace semantic_entities;

	if(!declarative_region_stack.empty())
	{
		auto it = declarative_region_stack.end();
		for(auto i = declarative_region_stack.size(); i > 0; --i)
		{
			--it;
			std::shared_ptr<declarative_region> current_declarative_region = *it;
			if(std::shared_ptr<declarative_region> found_declarative_region = find_declarative_region(*current_declarative_region, declarative_region_name))
			{
				return found_declarative_region;
			}
		}
	}

	throw std::runtime_error("Declarative region " + declarative_region_name + " not found");
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

