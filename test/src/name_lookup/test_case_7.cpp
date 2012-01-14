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

BOOST_AUTO_TEST_CASE(test_case_7)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	namespace a
	{
		int i;
	}

	namespace b
	{
		using namespace a;
	}

	namespace c
	{
		using namespace a;
	}

	namespace bc
	{
		using namespace b;
		using namespace c;
	}

	void test()
	{
	}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");
	auto namespace_b = new namespace_("b");
	auto namespace_c = new namespace_("c");
	auto namespace_bc = new namespace_("bc");

	//functions
	auto function_test = new simple_function
	(
		"test",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		false,
		false
	);

	//variables
	auto variable_a_i = new variable
	(
		"i",
		fundamental_type::INT,
		false
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(std::unique_ptr<variable>(variable_a_i));
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_b));
	namespace_b->add_using_directive_namespace(*namespace_a);
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_c));
	namespace_c->add_using_directive_namespace(*namespace_a);
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_bc));
	namespace_bc->add_using_directive_namespace(*namespace_b);
	namespace_bc->add_using_directive_namespace(*namespace_c);
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_test));



	//
	//name lookup test
	//

	//look up bc::i from function test, must find a::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("bc"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}
}

} //namespace name_lookup

