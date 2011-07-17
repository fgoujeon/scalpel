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

BOOST_AUTO_TEST_CASE(using_declarations)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		namespace n
		{
			class c;

			enum e{};

			typedef int integer;

			void f();
			void f(int);

			bool operator==(c&, c&);

			int i;
		}

		using n::c;
		using n::e;
		using n::integer;
		using n::f;
		using n::operator==;
		using n::i;

		void test()
		{
			i++;
		}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_n = new namespace_("n");

	//classes
	auto class_n_c = new class_("c");

	//enums
	auto enum_n_e = new enum_t(basic_enum<int>("e"));

	//typedef
	auto typedef_n_integer = new typedef_("integer", fundamental_type::INT);

	//functions
	auto function_n_f = new simple_function
	(
		"f",
		fundamental_type::VOID
	);

	function_parameter_list function_n_f_int_parameter_list;
	function_n_f_int_parameter_list.push_back
	(
		std::unique_ptr<function_parameter>(new function_parameter(fundamental_type::VOID))
	);
	auto function_n_f_int = new simple_function
	(
		"f",
		fundamental_type::VOID,
		std::move(function_n_f_int_parameter_list)
	);

	function_parameter_list function_operator_equal_parameter_list;
	function_operator_equal_parameter_list.push_back
	(
		std::unique_ptr<function_parameter>(new function_parameter(class_n_c))
	);
	function_operator_equal_parameter_list.push_back
	(
		std::unique_ptr<function_parameter>(new function_parameter(class_n_c))
	);
	auto function_n_operator_equal = new operator_function
	(
		overloadable_operator::EQUAL,
		fundamental_type::VOID,
		std::move(function_operator_equal_parameter_list)
	);

	auto function_test = new simple_function
	(
		"test",
		fundamental_type::VOID
	);

	//variables
	auto variable_n_i = new variable
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_n));
	namespace_n->add_member(std::unique_ptr<class_>(class_n_c));
	namespace_n->add_member(std::unique_ptr<enum_t>(enum_n_e));
	namespace_n->add_member(std::unique_ptr<typedef_>(typedef_n_integer));
	namespace_n->add_member(std::unique_ptr<simple_function>(function_n_f));
	namespace_n->add_member(std::unique_ptr<simple_function>(function_n_f_int));
	namespace_n->add_member(std::unique_ptr<operator_function>(function_n_operator_equal));
	namespace_n->add_member(std::unique_ptr<variable>(variable_n_i));
	semantic_graph.add_member(entity_alias<class_>(*class_n_c));
	semantic_graph.add_member(entity_alias<enum_t>(*enum_n_e));
	semantic_graph.add_member(entity_alias<typedef_>(*typedef_n_integer));
	semantic_graph.add_member(entity_alias<simple_function>(*function_n_f));
	semantic_graph.add_member(entity_alias<simple_function>(*function_n_f_int));
	semantic_graph.add_member(entity_alias<operator_function>(*function_n_operator_equal));
	semantic_graph.add_member(entity_alias<variable>(*variable_n_i));
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_test));

	//look up c from function test(), must find n::c
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, class_>
			(
				"c",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, class_n_c);
	}

	//look up e from function test(), must find n::e
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, enum_t>
			(
				"e",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, enum_n_e);
	}

	//look up integer from function test(), must find n::integer
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, typedef_>
			(
				"integer",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, typedef_n_integer);
	}

	//look up f from function test(), must find n::f() and n::f(int)
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, simple_function>
			(
				"f",
				function_test
			)
		;

		BOOST_CHECK(found_entities.size() == 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(function_n_f) != found_entities.end());
			BOOST_CHECK(found_entities.find(function_n_f_int) != found_entities.end());
		}
	}

	//look up operator== from function test(), must find n::operator==
	{
		auto found_entities =
			find<identification_policies::by_overloaded_operator, false, true, operator_function>
			(
				overloadable_operator::EQUAL,
				function_test
			)
		;

		BOOST_CHECK(found_entities.size() == 1);
		if(found_entities.size() == 1)
		{
			BOOST_CHECK(found_entities.find(function_n_operator_equal) != found_entities.end());
		}
	}

	//look up i from function test(), must find n::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				"i",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_n_i);
	}
}

} //namespace name_lookup

