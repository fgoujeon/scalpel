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

BOOST_AUTO_TEST_CASE(test_case_3)
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
		namespace b
		{
			namespace c
			{
				int i;
			}
			using namespace a::b::c;
			void f1()
			{
				i = 5; // OK, c::i visible in b and hides a::i
			}
		}
		namespace d
		{
			void f2()
			{
				using namespace b::c;
				i = 5; // ambiguous, b::c::i or a::i?
			}
		}
		void f3()
		{
			i = 5; // uses a::i
		}
	}
	void f4()
	{
		i = 5; // ill-formed; neither i is visible
	}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");
	auto namespace_b = new namespace_("b");
	auto namespace_c = new namespace_("c");
	auto namespace_d = new namespace_("d");

	//functions
	auto function_a_b_f1 = std::make_shared<simple_function>
	(
		"f1",
		fundamental_type::VOID
	);
	auto function_a_d_f2 = std::make_shared<simple_function>
	(
		"f2",
		fundamental_type::VOID
	);
	auto function_a_f3 = std::make_shared<simple_function>
	(
		"f3",
		fundamental_type::VOID
	);
	auto function_f4 = std::make_shared<simple_function>
	(
		"f4",
		fundamental_type::VOID
	);

	//variables
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto variable_a_b_c_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(variable_a_i);
	namespace_a->add_member(std::unique_ptr<namespace_>(namespace_b));
	namespace_b->add_member(std::unique_ptr<namespace_>(namespace_c));
	namespace_c->add_member(variable_a_b_c_i);
	//namespace_b->add_using_directive_namespace(*namespace_c);
	namespace_b->add_member(function_a_b_f1);
	function_a_b_f1->body(std::make_shared<statement_block>());
	namespace_a->add_member(std::unique_ptr<namespace_>(namespace_d));
	namespace_d->add_member(function_a_d_f2);
	function_a_d_f2->body(std::make_shared<statement_block>());
	//function_a_d_f2->body()->add_using_directive_namespace(*namespace_c);
	namespace_a->add_member(function_a_f3);
	function_a_f3->body(std::make_shared<statement_block>());
	semantic_graph.add_member(function_f4);
	function_f4->body(std::make_shared<statement_block>());



	//
	//name lookup test
	//

	//look up i from a::b::f1(), must find a::b::c::i
	{
		variable* found_entity = find<identification_policies::by_name, false, false, variable>("i", function_a_b_f1->body().get());
		BOOST_CHECK_EQUAL(found_entity, variable_a_b_c_i.get());
	}

	//look up i from a::d::f2(), must find a::i and a::b::c::i
	{
		std::set<variable*> found_entities = find<identification_policies::by_name, false, true, variable>("i", function_a_d_f2->body().get());
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(variable_a_i.get()) != found_entities.end());
			BOOST_CHECK(found_entities.find(variable_a_b_c_i.get()) != found_entities.end());
		}
	}

	//look up i from a::f3(), must find a::i
	{
		variable* found_entity = find<identification_policies::by_name, false, false, variable>("i", function_a_f3->body().get());
		BOOST_CHECK_EQUAL(found_entity, variable_a_i.get());
	}

	//look up i from f4(), must find nothing
	{
		variable* found_entity = find<identification_policies::by_name, true, false, variable>("i", function_f4->body().get());
		BOOST_CHECK(!found_entity);
	}
}

} //namespace name_lookup

