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

#include "name_lookup.hpp"

#include <algorithm>
#include <functional>

namespace socoa { namespace cpp { namespace name_lookup
{

using namespace syntax_tree;
using namespace semantic_graph;

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
            const semantic_graph::named_entity* found_symbol = find_unqualified_name(current_scope.enclosing_scope(), name, true);
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
//            const std::shared_ptr<semantic_graph::named_entity> found_symbol = find_unqualified_name(base_class, name, false);
//            if(found_symbol)
//            {
//                return found_symbol;
//            }
//        }
//    }

	//no name has been found, we return a null pointer
    return 0;
}

semantic_graph::scope*
find_scope
(
	scope& current_scope,
	const nested_name_specifier& a_nested_name_specifier
)
{
	scope* found_scope = 0;

	auto an_identifier_or_template_id = a_nested_name_specifier.get_identifier_or_template_id();
	boost::optional<const identifier&> an_identifier = get_alternative<identifier>(an_identifier_or_template_id);

	if(an_identifier)
	{
		const std::string& scope_name = an_identifier->get_value();

		//find the scope which has that name
		auto scopes = current_scope.scopes();
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

		if(scope_it == scopes.end())
			return 0;

		found_scope = &*scope_it;
	}

	if(found_scope)
	{
		auto next_parts = a_nested_name_specifier.get_parts();
		for(auto i = next_parts.begin(); i != next_parts.end(); ++i)
		{
			auto next_part = *i;

			auto an_identifier_or_template_id = next_part.get_identifier_or_template_id();
			boost::optional<const identifier&> an_identifier = get_alternative<identifier>(an_identifier_or_template_id);

			if(an_identifier)
			{
				const std::string& scope_name = an_identifier->get_value();

				//find the scope which has that name
				auto scopes = current_scope.scopes();
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

				if(scope_it == scopes.end())
					return 0;

				found_scope = &*scope_it;
			}
		}
	}

	return found_scope;
}

}}} //namespace socoa::cpp::name_lookup

