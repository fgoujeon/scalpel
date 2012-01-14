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

#include <scalpel/cpp/semantic_analysis/detail/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(base_classes_2)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		struct s
		{
			typedef int integer;
		};

		struct s2: s
		{
		};
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;

	//classes
	auto class_s = new class_("s");
	auto class_s2 = new class_("s2");

	//typedefs
	auto typedef_s_integer = new member_typedef("integer", fundamental_type::INT, member_accessibility::PUBLIC);

	//assembling
	semantic_graph.add_member(std::unique_ptr<class_>(class_s));
	class_s->add_member(std::unique_ptr<member_typedef>(typedef_s_integer));
	semantic_graph.add_member(std::unique_ptr<class_>(class_s2));
	class_s2->add_base_class(base_class(class_s, member_accessibility::PUBLIC, false));

	//look up s2::integer from global namespace, must find s::integer
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, member_typedef>
			(
				false,
				nested_name_specifier
				(
					identifier("s2"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"integer",
				&semantic_graph
			)
		;

		BOOST_CHECK(found_entity == typedef_s_integer);
	}
}

} //namespace name_lookup

