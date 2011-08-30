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

BOOST_AUTO_TEST_CASE(class_using_declarations)
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
			void f();
		};

		struct s2: s
		{
			using s::f;

			void f(int);

			void test();
		};
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;

	//classes
	auto class_s = new class_("s");
	auto class_s2 = new class_("s2");

	//functions
	auto function_s_f = new simple_member_function
	(
		"f",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);

	function_parameter_list function_s2_f_parameter_list;
	function_s2_f_parameter_list.push_back
	(
		std::unique_ptr<function_parameter>(new function_parameter(fundamental_type::INT))
	);
	auto function_s2_f = new simple_member_function
	(
		"f",
		fundamental_type::INT,
		std::move(function_s2_f_parameter_list),
		false,
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);

	auto function_s2_test = new simple_member_function
	(
		"test",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		member_accessibility::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<class_>(class_s));
	class_s->add_member(std::unique_ptr<simple_member_function>(function_s_f));
	semantic_graph.add_member(std::unique_ptr<class_>(class_s2));
	class_s2->add_base_class(base_class(class_s, member_accessibility::PUBLIC, false));
	class_s2->add_member(member_entity_alias<simple_member_function>(*function_s_f, member_accessibility::PUBLIC));
	class_s2->add_member(std::unique_ptr<simple_member_function>(function_s2_f));
	class_s2->add_member(std::unique_ptr<simple_member_function>(function_s2_test));

	//look up f from function s2::test(), must find s::f() and s2::f(int)
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, simple_member_function>
			(
				"f",
				function_s2_test
			)
		;

		BOOST_CHECK(found_entities.size() == 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(function_s_f) != found_entities.end());
			BOOST_CHECK(found_entities.find(function_s2_f) != found_entities.end());
		}
	}
}

} //namespace name_lookup

