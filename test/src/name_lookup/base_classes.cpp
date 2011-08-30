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

BOOST_AUTO_TEST_CASE(base_classes)
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

	scalpel::cpp::semantic_graph semantic_graph;
	auto struct_c0 = new class_("c0");
	auto struct_c0_inner = new member_class("inner", member_accessibility::PUBLIC);
	auto function_c0_inner_f = new simple_member_function
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
	auto function_c0_f = new simple_member_function
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
	auto struct_c1base = new class_("c1base");
	auto function_c1base_f = new simple_member_function
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
	auto function_c1base_g = new simple_member_function
	(
		"g",
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
	auto struct_c1 = new class_("c1");
	auto function_c1_g = new simple_member_function
	(
		"g",
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
	auto struct_c = new class_("c");
	auto function_g_test = new simple_member_function
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

	semantic_graph.add_member(std::unique_ptr<class_>(struct_c0));
	struct_c0->add_member(std::unique_ptr<member_class>(struct_c0_inner));
	struct_c0_inner->add_member(std::unique_ptr<simple_member_function>(function_c0_inner_f));
	struct_c0->add_member(std::unique_ptr<simple_member_function>(function_c0_f));
	semantic_graph.add_member(std::unique_ptr<class_>(struct_c1base));
	struct_c1base->add_member(std::unique_ptr<simple_member_function>(function_c1base_f));
	struct_c1base->add_member(std::unique_ptr<simple_member_function>(function_c1base_g));
	semantic_graph.add_member(std::unique_ptr<class_>(struct_c1));
	struct_c1->add_base_class(base_class(struct_c1base, member_accessibility::PUBLIC, false));
	struct_c1->add_member(std::unique_ptr<simple_member_function>(function_c1_g));
	semantic_graph.add_member(std::unique_ptr<class_>(struct_c));
	struct_c->add_base_class(base_class(struct_c0, member_accessibility::PUBLIC, false));
	struct_c->add_base_class(base_class(struct_c1, member_accessibility::PUBLIC, false));
	struct_c->add_member(std::unique_ptr<simple_member_function>(function_g_test));


	//
	//name lookup test
	//
	{
		auto found_entities = find<identification_policies::by_name, false, true, simple_member_function>("f", function_g_test);
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(function_c0_f) != found_entities.end());
			BOOST_CHECK(found_entities.find(function_c1base_f) != found_entities.end());
		}
	}

	{
		auto found_entity = find<identification_policies::by_name, false, false, simple_member_function>("g", function_g_test);
		BOOST_CHECK_EQUAL(found_entity, function_c1_g);
	}

	{
		auto found_entity = find<identification_policies::by_name, false, false, member_class>("inner", function_g_test);
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
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				function_g_test
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
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				function_g_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, function_c0_f);
	}

	{
		nested_name_specifier_last_part_seq nested_name_specifier_last_part_seq_node;
		nested_name_specifier_last_part_seq_node.push_back
		(
			nested_name_specifier_last_part
			(
				optional_node<predefined_text_node<str::template_>>(),
				identifier("inner"),
				predefined_text_node<str::double_colon>()
			)
		);

		auto found_entity =
			find<identification_policies::by_name, false, false, simple_member_function>
			(
				false,
				nested_name_specifier
				(
					identifier("c0"),
					predefined_text_node<str::double_colon>(),
					std::move(nested_name_specifier_last_part_seq_node)
				),
				"f",
				function_g_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, function_c0_inner_f);
	}
}

} //namespace name_lookup

