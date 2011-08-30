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

#include <scalpel/cpp/semantic_analysis/detail/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(enums)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		enum color
		{
			RED,
			GREEN,
			BLUE
		};

		struct s
		{
			enum direction
			{
				LEFT,
				RIGHT
			};
		};
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;

	//classes
	auto class_s = new class_("s");

	//enum constants
	auto enum_constant_color_red = new enum_constant<int>("RED", 0);
	auto enum_constant_color_green = new enum_constant<int>("GREEN", 1);
	auto enum_constant_color_blue = new enum_constant<int>("BLUE", 2);
	auto enum_constant_s_direction_left = new enum_constant<long int>("LEFT", 0);
	auto enum_constant_s_direction_right = new enum_constant<long int>("RIGHT", 1);

	//enums
	enum_* enum_color = enum_::create<int>("color");
	enum_constant_list<int>& enum_constant_list_color = scalpel::utility::get<enum_constant_list<int>>(enum_color->constants());
	enum_constant_list_color.add(std::unique_ptr<enum_constant<int>>(enum_constant_color_red));
	enum_constant_list_color.add(std::unique_ptr<enum_constant<int>>(enum_constant_color_green));
	enum_constant_list_color.add(std::unique_ptr<enum_constant<int>>(enum_constant_color_blue));

	member_enum* enum_s_direction = member_enum::create<long int>("direction", member_accessibility::PUBLIC);
	enum_constant_list<long int>& enum_constant_list_direction = scalpel::utility::get<enum_constant_list<long int>>(enum_s_direction->constants());
	enum_constant_list_direction.add(std::unique_ptr<enum_constant<long int>>(enum_constant_s_direction_left));
	enum_constant_list_direction.add(std::unique_ptr<enum_constant<long int>>(enum_constant_s_direction_right));

	//assembling
	semantic_graph.add_member(std::unique_ptr<enum_>(enum_color));
	semantic_graph.add_member(std::unique_ptr<class_>(class_s));
	class_s->add_member(std::unique_ptr<member_enum>(enum_s_direction));

	//look up color from the global namespace, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, enum_>
			(
				"color",
				&semantic_graph
			)
		;

		BOOST_CHECK_EQUAL(found_entity, enum_color);
	}

	//look up color::RED from the global namespace, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, enum_constant<int>>
			(
				false,
				nested_name_specifier
				(
					identifier("color"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"RED",
				&semantic_graph
			)
		;
		BOOST_CHECK_EQUAL(found_entity, enum_constant_color_red);
	}

	//look up RED from the global namespace, must find color::RED
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, enum_constant<int>>
			(
				"RED",
				&semantic_graph
			)
		;
		BOOST_CHECK_EQUAL(found_entity, enum_constant_color_red);
	}

	//look up s::direction::LEFT from the global namespace, must find it
	{
		nested_name_specifier_last_part_seq last_part_seq_node;
		last_part_seq_node.push_back
		(
			nested_name_specifier_last_part
			(
				optional_node<predefined_text_node<str::template_>>(),
				identifier("direction"),
				predefined_text_node<str::double_colon>()
			)
		);

		auto found_entity =
			find<identification_policies::by_name, false, false, enum_constant<long int>>
			(
				false,
				nested_name_specifier
				(
					identifier("s"),
					predefined_text_node<str::double_colon>(),
					last_part_seq_node
				),
				"LEFT",
				&semantic_graph
			)
		;
		BOOST_CHECK_EQUAL(found_entity, enum_constant_s_direction_left);
	}

	//look up s::LEFT from the global namespace, must find s::direction::LEFT
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, enum_constant<long int>>
			(
				false,
				nested_name_specifier
				(
					identifier("s"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"LEFT",
				&semantic_graph
			)
		;
		BOOST_CHECK_EQUAL(found_entity, enum_constant_s_direction_left);
	}
}

} //namespace name_lookup

