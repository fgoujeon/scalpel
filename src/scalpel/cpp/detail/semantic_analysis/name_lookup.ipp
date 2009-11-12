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

#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

template<class RangeT>
const semantic_entities::named_entity*
find_unqualified_name
(
	RangeT scope_stack,
	const std::string& name,
	bool recursive
);



template<class RangeT>
const semantic_entities::named_entity*
find_unqualified_name
(
	RangeT scope_stack,
	const std::string& name
)
{
    return find_unqualified_name(scope_stack, name, true);
}



template<class RangeT>
const semantic_entities::named_entity*
find_unqualified_name
(
	RangeT scope_stack,
	const std::string& name,
	bool recursive
)
{
	using namespace semantic_entities;

	const scope& current_scope = scope_stack.back();

    /*
    1. Current scope
    */
    {
		std::cout << "Try to find " << name << " in scope " << current_scope.name() << "\n";
		auto members = current_scope.named_entities();
		auto member_it = std::find_if
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
            scope_stack.size() >= 2 //is there at least an enclosing scope?
        )
        {
			auto last_but_one_it = scope_stack.end();
			--last_but_one_it;
			RangeT enclosing_scope_stack(scope_stack.begin(), last_but_one_it);

			if(!enclosing_scope_stack.empty())
			{
				const semantic_entities::named_entity* found_symbol = find_unqualified_name(enclosing_scope_stack, name, true);
				if(found_symbol)
				{
					return found_symbol;
				}
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



template<class RangeT>
semantic_entities::scope*
find_scope
(
	RangeT scope_stack,
	const syntax_nodes::nested_name_specifier& a_nested_name_specifier
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	std::cout << "find_scope()\n";
	//std::cout << "nested_name_specifier = " << a_nested_name_specifier.value() << "\n";

	scope* found_scope = 0;

	//get the first part of the nested-name-specifier
	const identifier_or_template_id& an_identifier_or_template_id = get_identifier_or_template_id(a_nested_name_specifier);
	boost::optional<const identifier&> an_identifier = get<identifier>(&an_identifier_or_template_id);

	//if the first part is a simple identifier
	if(an_identifier)
	{
		const std::string& scope_name = an_identifier->value();

		//find the scope which has that identifier in the current scope and in the enclosing scopes
		found_scope = recursive_ascent_find_scope(scope_stack, scope_name);
	}

	//if the first part scope has been found, go on with the next parts
	if(found_scope)
	{
		//is there other parts?
		auto last_part_seq = get_last_part_seq(a_nested_name_specifier);
		if(last_part_seq)
		{
			//for each part...
			for(auto i = last_part_seq->begin(); i != last_part_seq->end(); ++i)
			{
				if(found_scope)
				{
					const nested_name_specifier_last_part& last_part = i->main_node();

					const identifier_or_template_id& an_identifier_or_template_id = get_identifier_or_template_id(last_part);
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



template<class RangeT>
semantic_entities::scope*
recursive_ascent_find_scope
(
	RangeT scope_stack,
	const std::string& scope_name
)
{
	using namespace semantic_entities;

	scope* found_scope = 0;

	if(!scope_stack.empty())
	{
		auto i = scope_stack.end();
		do
		{
			--i;
			scope& current_scope = *i;
			found_scope = find_scope(current_scope, scope_name);
		} while(i != scope_stack.begin() && found_scope != 0);
	}

	return found_scope;
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

