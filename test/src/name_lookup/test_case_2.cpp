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
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(test_case_2)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	struct c0
	{
		struct inner
		{
			void f();
		};

		void f();
	};

	struct c1base
	{
		void f();
		void g();
	};

	struct c1: public c1base
	{
		void g();
	};

	struct c: public c0, public c1
	{
		void test()
		{
			//look from here
			f();
			g();
			inner();
			c1base::f();
			::c0::f();
			c0::inner::f();
		}
	};
	*/

	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto struct_c0 = class_::make_shared("c0");
	auto struct_c0_inner = class_::make_shared("inner");
	auto function_c0_inner_f = std::make_shared<simple_member_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_c0_f = std::make_shared<simple_member_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto struct_c1base = class_::make_shared("c1base");
	auto function_c1base_f = std::make_shared<simple_member_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_c1base_g = std::make_shared<simple_member_function>
	(
		"g",
		fundamental_type::VOID
	);
	auto struct_c1 = class_::make_shared("c1");
	auto function_c1_g = std::make_shared<simple_member_function>
	(
		"g",
		fundamental_type::VOID
	);
	auto struct_c = class_::make_shared("c");
	auto function_g_test = std::make_shared<simple_member_function>
	(
		"test",
		fundamental_type::VOID
	);

	semantic_graph->add_member(struct_c0);
	struct_c0->add_member(struct_c0_inner);
	struct_c0_inner->add_member(function_c0_inner_f);
	struct_c0->add_member(function_c0_f);
	semantic_graph->add_member(struct_c1base);
	struct_c1base->add_member(function_c1base_f);
	struct_c1base->add_member(function_c1base_g);
	semantic_graph->add_member(struct_c1);
	struct_c1->add_base_class(*struct_c1base);
	struct_c1->add_member(function_c1_g);
	semantic_graph->add_member(struct_c);
	struct_c->add_base_class(*struct_c0);
	struct_c->add_base_class(*struct_c1);
	struct_c->add_member(function_g_test);


	//
	//name lookup test
	//
	{
		auto found_entities = find<identification_policies::by_name, false, true, simple_member_function>("f", function_g_test.get());
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(function_c0_f) != found_entities.end());
			BOOST_CHECK(found_entities.find(function_c1base_f) != found_entities.end());
		}
	}

	{
		auto found_entity = find<identification_policies::by_name, false, false, simple_member_function>("g", function_g_test.get());
		BOOST_CHECK_EQUAL(found_entity, function_c1_g);
	}

	{
		auto found_entity = find<identification_policies::by_name, false, false, class_>("inner", function_g_test.get());
		BOOST_CHECK_EQUAL(found_entity, struct_c0_inner);
	}

	{
		auto found_entity =
			find<identification_policies::by_name, false, false, simple_member_function>
			(
				false,
				nested_name_specifier
				(
					identifier("c1base"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				function_g_test.get()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, function_c1base_f);
	}

	{
		auto found_entity =
			find<identification_policies::by_name, false, false, simple_member_function>
			(
				true,
				nested_name_specifier
				(
					identifier("c0"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				function_g_test.get()
			)
		;

		BOOST_CHECK_EQUAL(found_entity, function_c0_f);
	}
//
//	{
//		nested_name_specifier_last_part_seq nested_name_specifier_last_part_seq_node;
//		nested_name_specifier_last_part_seq_node.push_back
//		(
//			nested_name_specifier_last_part_seq::item
//			(
//				space(""),
//				space(""),
//				nested_name_specifier_last_part
//				(
//					optional_node<predefined_text_node<str::template_>>(),
//					optional_node<space>(),
//					identifier("inner"),
//					optional_node<space>(),
//					predefined_text_node<str::double_colon>()
//				)
//			)
//		);
//
//		auto found_entity =
//			find<identification_policies::by_name, false, false, simple_member_function>
//			(
//				false,
//				nested_name_specifier
//				(
//					identifier("c0"),
//					space(""),
//					predefined_text_node<str::double_colon>(),
//					space(""),
//					std::move(nested_name_specifier_last_part_seq_node)
//				),
//				"f",
//				function_g_test.get()
//			)
//		;
//		BOOST_CHECK_EQUAL(found_entity, function_c0_inner_f);
//	}
}

} //namespace name_lookup

