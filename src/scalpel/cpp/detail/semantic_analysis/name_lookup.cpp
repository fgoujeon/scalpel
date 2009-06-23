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

#include "name_lookup.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <boost/optional.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

using namespace syntax_nodes;
using namespace semantic_entities;

const named_entity*
find_unqualified_name(const scope& current_scope, const std::string& name, bool recursive);


const named_entity*
find_unqualified_name(const scope& current_scope, const std::string& name)
{
    return find_unqualified_name(current_scope, name, true);
}

const named_entity*
find_unqualified_name(const scope& current_scope, const std::string& name, bool recursive)
{
    /*
    1. Current scope
    */
    {
		std::cout << "Try to find " << name << " in scope " << current_scope.name() << "\n";
		scope::named_entity_const_iterator_range members = current_scope.named_entities();
		scope::named_entity_const_indirect_iterator member_it = std::find_if
        (
            members.begin(),
            members.end(),
			std::bind
			(
				std::equal_to<std::string>(),
				std::cref(name),
				std::bind
				(
					&named_entity::name,
					std::placeholders::_1
				)
			)
        );

        if(member_it != members.end()) //if a name has been found
        {
            return &*member_it;
        }
    }


    /*
    2. Enclosing scopes (recursive call)
    */
    {
        if
        (
            recursive &&
            current_scope.has_enclosing_scope() //is there at least an enclosing scope?
        )
        {
            const semantic_entities::named_entity* found_symbol = find_unqualified_name(current_scope.enclosing_scope(), name, true);
            if(found_symbol)
            {
                return found_symbol;
            }
        }
    }


//    /*
//    3. Base classes (non-recursive)
//    */
//    {
//        const std::list<base_specifier>& base_specifiers = current_scope->get_base_specifiers();
//        for
//        (
//            std::list<base_specifier>::const_iterator i = base_specifiers.begin();
//            i != base_specifiers.end();
//            ++i
//        ) //for each base specifier (== for each base class)
//        {
//            const base_specifier& base_spec = *i;
//            const std::shared_ptr<class_> base_class = base_spec.get_class();
//            const std::shared_ptr<semantic_entities::named_entity> found_symbol = find_unqualified_name(base_class, name, false);
//            if(found_symbol)
//            {
//                return found_symbol;
//            }
//        }
//    }

	//no name has been found, we return a null pointer
    return 0;
}

semantic_entities::scope*
find_scope
(
	scope& current_scope,
	const nested_name_specifier& a_nested_name_specifier
)
{
	std::cout << "find_scope()\n";
	std::cout << "nested_name_specifier = " << a_nested_name_specifier.value() << "\n";

	scope* found_scope = 0;

	//get the first part of the nested-name-specifier
	const identifier_or_template_id& an_identifier_or_template_id = a_nested_name_specifier.identifier_or_template_id_node();
	boost::optional<const identifier&> an_identifier = get<identifier>(&an_identifier_or_template_id);

	//if the first part is a simple identifier
	if(an_identifier)
	{
		const std::string& scope_name = an_identifier->value();

		//find the scope which has that identifier in the current scope and in the enclosing scopes
		found_scope = recursive_ascent_find_scope(current_scope, scope_name);
	}

	//if the first part scope has been found, go on with the next parts
	if(found_scope)
	{
		//is there other parts?
		auto last_part_seq = a_nested_name_specifier.last_part_seq_node();
		if(last_part_seq)
		{
			//for each part...
			for(auto i = last_part_seq->begin(); i != last_part_seq->end(); ++i)
			{
				if(found_scope)
				{
					const nested_name_specifier::last_part& last_part = i->main_node();

					const identifier_or_template_id& an_identifier_or_template_id = last_part.identifier_or_template_id_node();
					boost::optional<const identifier&> an_identifier = get<identifier>(&an_identifier_or_template_id);

					if(an_identifier)
					{
						const std::string& scope_name = an_identifier->value();
						found_scope = find_scope(*found_scope, scope_name);
					}
				}
				else
					break;
			}
		}
	}

	return found_scope;
}

semantic_entities::scope*
recursive_ascent_find_scope
(
	scope& start_scope,
	const std::string& scope_name
)
{
	scope* found_scope = 0;
	scope* current_scope = &start_scope;

	while((found_scope = find_scope(*current_scope, scope_name)) == 0 && current_scope->has_enclosing_scope())
	{
		current_scope = &current_scope->enclosing_scope();
	}

	return found_scope;
}

semantic_entities::scope*
find_scope
(
	scope& parent_scope,
	const std::string& scope_name
)
{
	auto scopes = parent_scope.scopes();
	auto scope_it = std::find_if
	(
		scopes.begin(),
		scopes.end(),
		std::bind
		(
			std::equal_to<std::string>(),
			std::cref(scope_name),
			std::bind
			(
				&scope::name,
				std::placeholders::_1
			)
		)
	);

	if(scope_it != scopes.end())
	{
		std::cout << scope_name << " found in " << parent_scope.name() << "\n";
		return &*scope_it;
	}
	else
	{
		std::cout << scope_name << " not found in " << parent_scope.name() << "\n";
		return 0;
	}
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

