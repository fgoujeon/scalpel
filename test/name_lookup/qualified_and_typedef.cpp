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

BOOST_AUTO_TEST_CASE(qualified_and_typedef)
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

		typedef s alias;
		typedef const volatile s cv_alias;

		alias::integer i;
		cv_alias::integer j;
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;

	//classes
	auto struct_s = new class_("s");

	//typedefs
	auto typedef_s_integer = new member_typedef("integer", fundamental_type::INT, member_access::PUBLIC);
	auto typedef_alias = new typedef_("alias", struct_s);
	auto typedef_cv_alias = new typedef_("cv_alias", cv_qualified_type(struct_s, cv_qualified_type::qualification_type::CONST_AND_VOLATILE));

	//assembling
	semantic_graph.add_member(std::unique_ptr<class_>(struct_s));
	struct_s->add_member(std::unique_ptr<member_typedef>(typedef_s_integer));
	semantic_graph.add_member(std::unique_ptr<typedef_>(typedef_alias));
	semantic_graph.add_member(std::unique_ptr<typedef_>(typedef_cv_alias));



	//
	//name lookup test
	//

	//look up alias::integer from the global namespace, must find s::integer
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, member_typedef>
			(
				false,
				nested_name_specifier
				(
					identifier("alias"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"integer",
				&semantic_graph
			)
		;

		BOOST_CHECK_EQUAL(found_entity, typedef_s_integer);
	}

	//look up cv_alias::integer from the global namespace, must find s::integer
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, member_typedef>
			(
				false,
				nested_name_specifier
				(
					identifier("cv_alias"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"integer",
				&semantic_graph
			)
		;

		BOOST_CHECK_EQUAL(found_entity, typedef_s_integer);
	}
}

} //namespace name_lookup

