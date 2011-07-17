/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_IPP

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

namespace
{
	class add_to_enum_visitor: public utility::static_visitor<void>
	{
		public:
			add_to_enum_visitor(std::unique_ptr<semantic_entities::enum_constant<int>>&& constant):
				constant_(std::move(constant))
			{
			}

			template<template<typename> class Enum>
			void
			operator()(Enum<int>& e)
			{
				e.add(std::move(constant_));
			}

			template<template<typename> class Enum>
			void
			operator()(Enum<unsigned int>&)
			{
				assert(false);
			}

		private:
			std::unique_ptr<semantic_entities::enum_constant<int>>&& constant_;
	};

	template<class Enum>
	void
	add_to_enum
	(
		Enum& enum_entity,
		std::unique_ptr<semantic_entities::enum_constant<int>>&& constant
	)
	{
		add_to_enum_visitor visitor(std::move(constant));
		utility::apply_visitor(visitor, enum_entity);
	}
}

template<class Enum>
void
fill_enum
(
	Enum& enum_entity,
	const syntax_nodes::enum_specifier& enum_specifier_node
)
{
	int value_counter = 0;

	if(const syntax_nodes::optional_node<syntax_nodes::enumerator_list>& opt_enumerator_list_node = get_enumerator_list(enum_specifier_node))
	{
		const syntax_nodes::enumerator_list& enumerator_list_node = *opt_enumerator_list_node;
		for(auto i = enumerator_list_node.begin(); i != enumerator_list_node.end(); ++i)
		{
			const syntax_nodes::enumerator_definition& enumerator_definition_node = *i;
			add_to_enum
			(
				enum_entity,
				std::unique_ptr<semantic_entities::enum_constant<int>>
				(
					new semantic_entities::enum_constant<int>
					(
						get_identifier(enumerator_definition_node).value(),
						value_counter++
					)
				)
			);
//			enum_entity.add
//			(
//				std::unique_ptr<semantic_entities::enum_constant<int>>
//				(
//					new semantic_entities::enum_constant<int>
//					(
//						get_identifier(enumerator_definition_node).value(),
//						value_counter++
//					)
//				)
//			);
		}
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

