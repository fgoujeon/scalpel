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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_IPP

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class EntityT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
)
{
	bool has_leading_double_colon = syntax_nodes::has_leading_double_colon(nested_identifier_or_template_id_node);
	auto opt_nested_name_specifier_node = get_nested_name_specifier(nested_identifier_or_template_id_node);



	//Check whether the given qualified name is really qualified.
	//If not, perform a simple unqualified name lookup.
	if(!has_leading_double_colon && !opt_nested_name_specifier_node)
	{
		auto identifier_or_template_id_node = syntax_nodes::get_identifier_or_template_id(nested_identifier_or_template_id_node);
		return find_entities<EntityT>(identifier_or_template_id_node, declarative_region_path);
	}



	//Get the last declarative region of the nested name specifier
	//(i.e. Z in "[::]X::Y::Z::").
	std::shared_ptr<semantic_entities::namespace_> last_declarative_region;
	if(has_leading_double_colon)
	{
		//the first declarative region is in the global namespace
		std::shared_ptr<semantic_entities::namespace_> global_namespace = boost::get<std::shared_ptr<semantic_entities::namespace_>>(declarative_region_path.front());

		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;

			//find the first declarative region
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
			auto first_declarative_regions = find_entities_in_declarative_region<semantic_entities::namespace_>(identifier_or_template_id_node, global_namespace);
			if(first_declarative_regions.size() != 1)
			{
				throw std::runtime_error("more than one declarative regions first");
			}
			std::shared_ptr<semantic_entities::namespace_> first_declarative_region = first_declarative_regions.front();

			//find the last declarative region
			if(auto opt_last_part_seq_node = get_last_part_seq(nested_name_specifier_node))
			{
				auto last_part_seq_node = *opt_last_part_seq_node;
				last_declarative_region =
					find_declarative_region<semantic_entities::namespace_>(last_part_seq_node, first_declarative_region)
				;
			}
			else
			{
				//the last declarative region also is the first one
				last_declarative_region = first_declarative_region;
			}
		}
		else
		{
			//both the first and last declarative regions ARE the global namespace
			last_declarative_region = global_namespace;
		}
	}
	else
	{
		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;

			//find the first declarative region
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
			auto first_declarative_regions = find_entities<semantic_entities::namespace_>(identifier_or_template_id_node, declarative_region_path);
			if(first_declarative_regions.size() != 1)
			{
				throw std::runtime_error("more than one declarative regions first");
			}
			std::shared_ptr<semantic_entities::namespace_> first_declarative_region = first_declarative_regions.front();

			//find the last declarative region
			if(auto opt_last_part_seq_node = get_last_part_seq(nested_name_specifier_node))
			{
				auto last_part_seq_node = *opt_last_part_seq_node;
				last_declarative_region =
					find_declarative_region<semantic_entities::namespace_>(last_part_seq_node, first_declarative_region)
				;
			}
			else
			{
				//the last declarative region also is the first one
				last_declarative_region = first_declarative_region;
			}
		}
	}

	//find entities in the last declarative region
	auto identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);
	return find_entities_in_declarative_region<EntityT>(identifier_or_template_id_node, last_declarative_region);
}

template<class DeclarativeRegionT, class CurrentDeclarativeRegionT>
std::shared_ptr<DeclarativeRegionT>
name_lookup2::find_declarative_region
(
	const syntax_nodes::nested_name_specifier_last_part_seq& nested_name_specifier_last_part_seq_node,
	std::shared_ptr<CurrentDeclarativeRegionT> current_declarative_region
)
{
	std::shared_ptr<DeclarativeRegionT> found_declarative_region = current_declarative_region;

	for
	(
		auto i = nested_name_specifier_last_part_seq_node.begin();
		i != nested_name_specifier_last_part_seq_node.end();
		++i
	)
	{
		const syntax_nodes::nested_name_specifier_last_part& last_part_node = i->main_node();
		if(has_template_keyword(last_part_node))
		{
			assert(false); //not implemented yet (template)
		}
		else
		{
			const syntax_nodes::identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(last_part_node);
			if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id_node))
			{
				auto identifier_node = *opt_identifier_node;
				auto found_declarative_regions = find_entities_from_identifier_in_declarative_region<semantic_entities::namespace_>(identifier_node.value(), found_declarative_region);
				if(found_declarative_regions.size() != 1)
				{
					throw std::runtime_error("find_declarative_region() error");
				}
				found_declarative_region = found_declarative_regions.front();
			}
			else
			{
				assert(false); //not implemented yet (template)
			}
		}
	}

	return found_declarative_region;
}

template<class EntityT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
)
{
	if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id))
	{
		auto identifier_node = *opt_identifier_node;
		return find_entities_from_identifier<EntityT>(identifier_node.value(), declarative_region_path);
	}
	else
	{
		throw std::runtime_error("Not implemented yet");
	}
}

template<class EntityT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities_from_identifier
(
	const std::string& name,
	std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
)
{
	utility::shared_ptr_vector<EntityT> found_entities;

	//find entities from current to outermost declarative regions
	//(until global namespace)
	for(auto i = declarative_region_path.rbegin(); i != declarative_region_path.rend(); ++i)
	{
		semantic_entities::declarative_region_variant current_declarative_region = *i;

		if(auto opt_namespace_ptr = boost::get<std::shared_ptr<semantic_entities::namespace_>>(&current_declarative_region))
		{
			std::shared_ptr<semantic_entities::namespace_> namespace_ptr = *opt_namespace_ptr;

			//find entities in that namespace
			found_entities =
				find_entities_from_identifier_in_declarative_region<EntityT>(name, namespace_ptr)
			;
			if(!found_entities.empty()) break;
		}
		else if(auto opt_class_ptr = boost::get<std::shared_ptr<semantic_entities::class_>>(&current_declarative_region))
		{
			std::shared_ptr<semantic_entities::class_> class_ptr = *opt_class_ptr;

			//find entities in the members of that class
			found_entities =
				find_entities_from_identifier_in_declarative_region<EntityT>(name, class_ptr)
			;
			if(!found_entities.empty()) break;

			//find entities in the base classes of that class
			found_entities =
				find_entities_in_base_classes<EntityT>(name, class_ptr->base_classes())
			;
			if(!found_entities.empty()) break;
		}
	}

	return found_entities;
}

template<class EntityT, class DeclarativeRegionT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities_in_declarative_region
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id))
	{
		auto identifier_node = *opt_identifier_node;
		return find_entities_from_identifier_in_declarative_region<EntityT>(identifier_node.value(), current_declarative_region);
	}
	else
	{
		throw std::runtime_error("Not implemented yet");
	}
}

template<class EntityT, class DeclarativeRegionT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities_from_identifier_in_declarative_region
(
	const std::string& name,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	utility::shared_ptr_vector<EntityT> found_entities;

	typename utility::shared_ptr_vector<EntityT>::range members = get_members<EntityT>(current_declarative_region);
	for(auto i = members.begin(); i != members.end(); ++i)
	{
		std::shared_ptr<EntityT> current_entity = *i;
		if(current_entity->name() == name)
		{
			found_entities.push_back(current_entity);
		}
	}

	return found_entities;
}

template<class EntityT>
utility::shared_ptr_vector<EntityT>
name_lookup2::find_entities_in_base_classes
(
	const std::string& name,
	utility::shared_ptr_vector<semantic_entities::class_>::range base_classes
)
{
	typedef utility::shared_ptr_vector<EntityT> entities_t;

	entities_t found_entities;
	std::back_insert_iterator<entities_t> found_entities_back_insert_iterator(found_entities);

	for(auto i = base_classes.begin(); i != base_classes.end(); ++i)
	{
		std::shared_ptr<semantic_entities::class_> current_class = *i;

		//find entities in the current declarative region (i.e. current class)
		entities_t current_class_found_entities = find_entities_from_identifier_in_declarative_region<EntityT>(name, current_class);

		//entities found?
		if(!current_class_found_entities.empty())
		{
			//add them to the list
			std::copy
			(
				current_class_found_entities.begin(),
				current_class_found_entities.end(),
				found_entities_back_insert_iterator
			);
		}
		else
		{
			//find entities in the current declarative region's base classes
			entities_t current_class_base_classes_found_entities = find_entities_in_base_classes<EntityT>(name, current_class->base_classes());

			//add them to the list
			std::copy
			(
				current_class_base_classes_found_entities.begin(),
				current_class_base_classes_found_entities.end(),
				found_entities_back_insert_iterator
			);
		}
	}

	return found_entities;
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

