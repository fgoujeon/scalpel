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

#include "test_case_11.hpp"
#include <scalpel/cpp/detail/semantic_analysis/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/shared_ptr_variant.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_11()
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::detail::semantic_analysis::name_lookup;
	using namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	class c
	{
		c
		operator+(const c&);
	};

	bool
	operator!=(const c&, const c&);

	bool
	operator==(const c&, const c&);

	void
	test()
	{
		c c1, c2;
		operator==(c1, c2);
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();

	//classes
	auto class_c = class_::make_shared("c");

	//functions
	auto operator_function_plus = std::make_shared<operator_function>
	(
		scalpel::cpp::semantic_entities::overloadable_operator::PLUS,
		fundamental_type_shared_ptrs::bool_
	);
	auto operator_function_not_equal = std::make_shared<operator_function>
	(
		scalpel::cpp::semantic_entities::overloadable_operator::EXCLAMATION_EQUAL,
		fundamental_type_shared_ptrs::bool_
	);
	auto operator_function_equal = std::make_shared<operator_function>
	(
		scalpel::cpp::semantic_entities::overloadable_operator::DOUBLE_EQUAL,
		fundamental_type_shared_ptrs::bool_
	);
	auto function_test = simple_function::make_shared
	(
		"test",
		fundamental_type_shared_ptrs::void_
	);

	//assembling
	semantic_graph->add_member(class_c);
	class_c->add_member(operator_function_plus);
	semantic_graph->add_member(operator_function_not_equal);
	semantic_graph->add_member(operator_function_equal);
	semantic_graph->add_member(function_test);
	function_test->body(std::make_shared<statement_block>());



	//
	//name lookup test
	//

	//look up operator== from function test, must find it
	{
		std::shared_ptr<operator_function> found_entity =
			find<identifier_getting_policies::get_operator, false, false, operator_function>
			(
				scalpel::cpp::semantic_entities::overloadable_operator::DOUBLE_EQUAL,
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, operator_function_equal);
	}

	//look up c::operator+ from function test, must find it
	{
		std::shared_ptr<operator_function> found_entity =
			find<identifier_getting_policies::get_operator, false, false, operator_function>
			(
				false,
				nested_name_specifier
				(
					identifier("c"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				scalpel::cpp::semantic_entities::overloadable_operator::PLUS,
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, operator_function_plus);
	}
}

} //namespace name_lookup

