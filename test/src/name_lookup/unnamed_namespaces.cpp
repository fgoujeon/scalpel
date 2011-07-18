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

BOOST_AUTO_TEST_CASE(unnamed_namespaces)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		namespace
		{
			int i;
		}
		void f()
		{
			i++;
		}

		namespace a
		{
			namespace
			{
				int i;
				int j;
			}
			void g()
			{
				i++;
			}
		}

		using namespace a;
		void h()
		{
			i++;
			a::i++;
			j++;
		}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_xxx = new unnamed_namespace();
	auto namespace_a = new namespace_("a");
	auto namespace_a_xxx = new unnamed_namespace();

	//functions
	auto function_f = new simple_function
	(
		"f",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		false,
		false
	);
	auto function_a_g = new simple_function
	(
		"g",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		false,
		false
	);
	auto function_h = new simple_function
	(
		"h",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		false,
		false
	);

	//variables
	auto variable_xxx_i = new variable
	(
		"i",
		fundamental_type::INT
	);
	auto variable_a_xxx_i = new variable
	(
		"i",
		fundamental_type::INT
	);
	auto variable_a_xxx_j = new variable
	(
		"j",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.set_unnamed_namespace(std::unique_ptr<unnamed_namespace>(namespace_xxx));
	namespace_xxx->add_member(std::unique_ptr<variable>(variable_xxx_i));
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_f));

	//look up i from function f(), must find <unnamed>::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				"i",
				function_f
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_xxx_i);
	}

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->set_unnamed_namespace(std::unique_ptr<unnamed_namespace>(namespace_a_xxx));
	namespace_a_xxx->add_member(std::unique_ptr<variable>(variable_a_xxx_i));
	namespace_a_xxx->add_member(std::unique_ptr<variable>(variable_a_xxx_j));
	namespace_a->add_member(std::unique_ptr<simple_function>(function_a_g));

	//look up i from function a::g(), must find a::<unnamed>::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				"i",
				function_a_g
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_a_xxx_i);
	}

	//assembling
	semantic_graph.add_using_directive_namespace(*namespace_a);
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_h));

	//look up i from function h(), must find <unnamed>::i and a::<unnamed>::i
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, variable>
			(
				"i",
				function_h
			)
		;

		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(variable_xxx_i) != found_entities.end());
			BOOST_CHECK(found_entities.find(variable_a_xxx_i) != found_entities.end());
		}
	}

	//look up a::i from function h(), must find a::<unnamed>::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("a"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_h
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_a_xxx_i);
	}

	//look up j from function h(), must find a::<unnamed>::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				"j",
				function_h
			)
		;

		BOOST_CHECK_EQUAL(found_entity, variable_a_xxx_j);
	}
}

} //namespace name_lookup

