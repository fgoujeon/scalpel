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

#include "test_case_8.hpp"
#include <scalpel/cpp/detail/semantic_analysis/semantic_graph_analysis/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_8()
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis::name_lookup;

	//
	//construction of the semantic graph of the following source code:
	/*
	namespace b
	{
		int i;
	}

	namespace a
	{
		using namespace b;
		int j;
	}

	namespace b
	{
		using namespace a;
	}

	void test()
	{
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("a");
	auto namespace_b = namespace_::make_shared("b");

	//functions
	auto function_test = simple_function::make_shared
	(
		"test",
		fundamental_type_shared_ptrs::void_
	);

	//variables
	auto variable_b_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);
	auto variable_a_j = std::make_shared<variable>
	(
		"j",
		fundamental_type_shared_ptrs::int_
	);

	//assembling
	semantic_graph->add_member(namespace_a);
	namespace_a->add_using_directive_namespace(namespace_b);
	namespace_a->add_member(variable_a_j);
	semantic_graph->add_member(namespace_b);
	namespace_b->add_using_directive_namespace(namespace_a);
	namespace_b->add_member(variable_b_i);
	semantic_graph->add_member(function_test);



	//
	//name lookup test
	//

	//look up a::j from function test, must find a::j
	{
		nested_identifier_or_template_id a_j_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("a"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("j")
		);
		auto found_entity = find<false, false, variable>(a_j_syntax_node, function_test);
		BOOST_CHECK_EQUAL(found_entity, variable_a_j);
	}

	//look up b::j from function test, must find a::j
	{
		nested_identifier_or_template_id b_j_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("b"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("j")
		);
		auto found_entity = find<false, false, variable>(b_j_syntax_node, function_test);
		BOOST_CHECK_EQUAL(found_entity, variable_a_j);
	}

	//look up a::i from function test, must find b::i
	{
		nested_identifier_or_template_id a_i_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("a"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("i")
		);
		auto found_entity = find<false, false, variable>(a_i_syntax_node, function_test);
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up b::i from function test, must find b::i
	{
		nested_identifier_or_template_id b_i_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("b"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("i")
		);
		auto found_entity = find<false, false, variable>(b_i_syntax_node, function_test);
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up b::k from function test, must find nothing
	{
		nested_identifier_or_template_id b_k_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("b"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("k")
		);
		auto found_entity = find<true, false, variable>(b_k_syntax_node, function_test);
		BOOST_CHECK(!found_entity.get());
	}
}

} //namespace name_lookup

