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

BOOST_AUTO_TEST_CASE(test_case_11)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	class c
	{
		~c();

		c
		operator+(const c&);

		operator double*();

		operator int*();
	};

	bool
	operator!=(const c&, const c&);

	bool
	operator==(const c&, const c&);
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;

	//classes
	auto class_c = new class_("c");

	//functions
	auto c_constructor = new constructor(function_parameter_list(), false, member_accessibility::PUBLIC, false, false);
	auto c_destructor = new destructor(member_accessibility::PUBLIC, false, false, false);
	auto c_operator_function_plus = new operator_member_function
	(
		scalpel::cpp::semantic_entities::overloadable_operator::PLUS,
		fundamental_type::BOOL,
		function_parameter_list(),
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false
	);
	auto c_conversion_function_double_ptr = new conversion_function
	(
		pointer(fundamental_type::DOUBLE),
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);
	auto c_conversion_function_int_ptr = new conversion_function
	(
		pointer(fundamental_type::INT),
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);
	auto operator_function_not_equal = new operator_function
	(
		scalpel::cpp::semantic_entities::overloadable_operator::EXCLAMATION_EQUAL,
		fundamental_type::BOOL,
		function_parameter_list(),
		false,
		false
	);
	auto operator_function_equal = new operator_function
	(
		scalpel::cpp::semantic_entities::overloadable_operator::DOUBLE_EQUAL,
		fundamental_type::BOOL,
		function_parameter_list(),
		false,
		false
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<class_>(class_c));
	class_c->add_member(std::unique_ptr<constructor>(c_constructor));
	class_c->set_destructor(std::unique_ptr<destructor>(c_destructor));
	class_c->add_member(std::unique_ptr<conversion_function>(c_conversion_function_double_ptr));
	class_c->add_member(std::unique_ptr<conversion_function>(c_conversion_function_int_ptr));
	class_c->add_member(std::unique_ptr<operator_member_function>(c_operator_function_plus));
	semantic_graph.add_member(std::unique_ptr<operator_function>(operator_function_not_equal));
	semantic_graph.add_member(std::unique_ptr<operator_function>(operator_function_equal));



	//
	//name lookup test
	//

	//look up operator==() from global namespace, must find it
	{
		operator_function* found_entity =
			find<identification_policies::by_overloaded_operator, false, false, operator_function>
			(
				scalpel::cpp::semantic_entities::overloadable_operator::DOUBLE_EQUAL,
				&semantic_graph
			)
		;
		BOOST_CHECK_EQUAL(found_entity, operator_function_equal);
	}

	//look up c::operator+() from global namespace, must find it
	{
		operator_member_function* found_entity =
			find<identification_policies::by_overloaded_operator, false, false, operator_member_function>
			(
				false,
				nested_name_specifier
				(
					identifier("c"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				scalpel::cpp::semantic_entities::overloadable_operator::PLUS,
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK_EQUAL(found_entity, c_operator_function_plus);
	}

	//look up c::c() from global namespace, must find it
	{
		constructor* found_entity =
			find<identification_policies::by_nothing, false, false, constructor>
			(
				false,
				nested_name_specifier
				(
					identifier("c"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				0,
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK_EQUAL(found_entity, c_constructor);
	}

	//look up c::~c() from global namespace, must find it
	{
		destructor* found_entity =
			find<identification_policies::by_nothing, false, false, destructor>
			(
				false,
				nested_name_specifier
				(
					identifier("c"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				0,
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK_EQUAL(found_entity, c_destructor);
	}

	//look up c::operator int*() from global namespace, must find it
	{
		conversion_function* found_entity =
			find<identification_policies::by_return_type, false, false, conversion_function>
			(
				false,
				nested_name_specifier
				(
					identifier("c"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				pointer(fundamental_type::INT),
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK_EQUAL(found_entity, c_conversion_function_int_ptr);
	}
}

} //namespace name_lookup

