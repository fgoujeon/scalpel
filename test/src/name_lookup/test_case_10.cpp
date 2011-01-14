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
#include <scalpel/utility/shared_ptr_variant.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(test_case_10)
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

	namespace as = a;

	void
	test()
	{
		namespace as2 = a;
		as::i = 0;
		as2::i = 0;
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("a");

	//namespace aliases
	auto namespace_alias_as = std::make_shared<namespace_alias>("as", namespace_a);
	auto namespace_alias_as2 = std::make_shared<namespace_alias>("as2", namespace_a);

	//functions
	auto function_test = std::make_shared<simple_function>
	(
		"test",
		fundamental_type::VOID
	);

	//variables
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph->add_member(namespace_a);
	namespace_a->add_member(variable_a_i);
	semantic_graph->add_member(namespace_alias_as);
	semantic_graph->add_member(function_test);
	function_test->body(std::make_shared<statement_block>());
	function_test->body()->add_member(namespace_alias_as2);



	//
	//name lookup test
	//

	//look up as::i from function test, must find a::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("as"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test->body()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//look up as2::i from function test, must find a::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("as2"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test->body()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//look up a from as, must find a
	{
		scalpel::utility::shared_ptr_variant<namespace_, namespace_alias>::type found_entity =
			find<identification_policies::by_name, false, false, namespace_, namespace_alias>("as", function_test->body())
		;
		std::shared_ptr<namespace_alias> found_namespace_alias = get<namespace_alias>(found_entity);
		BOOST_CHECK_EQUAL(found_namespace_alias, namespace_alias_as);
		BOOST_CHECK_EQUAL(found_namespace_alias->referred_namespace(), namespace_a);
	}
}

} //namespace name_lookup

