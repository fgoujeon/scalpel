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

BOOST_AUTO_TEST_CASE(test_case_9)
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
		namespace b
		{
			void f();
		}
		using namespace b;
	}

	namespace c
	{
		namespace d
		{
			void f();
		}
	}

	using namespace a;
	using namespace c::d;

	void a::f(){}
	void b::f(){}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");
	auto namespace_b = new namespace_("b");
	auto namespace_c = new namespace_("c");
	auto namespace_d = new namespace_("d");

	//functions
	auto function_a_b_f = new simple_function
	(
		"f",
		fundamental_type::VOID
	);
	auto function_c_d_f = new simple_function
	(
		"f",
		fundamental_type::VOID
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(std::unique_ptr<namespace_>(namespace_b));
	namespace_b->add_member(std::unique_ptr<simple_function>(function_a_b_f));
	//namespace_a->add_using_directive_namespace(*namespace_b);
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_c));
	namespace_c->add_member(std::unique_ptr<namespace_>(namespace_d));
	namespace_d->add_member(std::unique_ptr<simple_function>(function_c_d_f));
	//semantic_graph.add_using_directive_namespace(*namespace_a);
	//semantic_graph.add_using_directive_namespace(*namespace_d);



	//
	//name lookup test
	//

	//look up a::f() (undefined function's declaration) from global namespace, must find nothing
	{
		simple_function* found_entity =
			find<identification_policies::by_name, true, false, simple_function>
			(
				false,
				nested_name_specifier
				(
					identifier("a"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK(!found_entity);
	}

	//look up b::f() (undefined function's declaration) from global namespace, must find a::b::f()
	{
		nested_identifier_or_template_id b_f_syntax_node
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
			identifier("f")
		);
		auto found_entity =
			find<identification_policies::by_name, false, false, simple_function>
			(
				false,
				nested_name_specifier
				(
					identifier("b"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				&semantic_graph,
				false
			)
		;
		BOOST_CHECK_EQUAL(found_entity, function_a_b_f);
	}
}

} //namespace name_lookup

