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

#include "analyzer.hpp"
#include <boost/test/unit_test.hpp>

namespace semantic_analysis
{

BOOST_AUTO_TEST_CASE(complex_class)
{
	using namespace scalpel::cpp::semantic_entities;

	std::shared_ptr<scalpel::cpp::semantic_graph> semantic_graph = analyze
	(
		"namespace n "
		"{ "
		"	namespace n2 "
		"	{ "
		"		class super_test "
		"		{ "
		"		}; "
		"	} "
		"} "
		" "
		"class virtual_base "
		"{ "
		"}; "
		" "
		"class virtual_base2 "
		"{ "
		"}; "
		" "
		"class test: public n::n2::super_test, virtual virtual_base, protected virtual virtual_base2 "
		"{ "
		"	public: "
		//"		explicit "
		"		test(int i); "
		" "
		"		test(const int& t); "
		//"		test(const test& t); "
		" "
		//"		virtual "
		"		~test(); "
		" "
		//"		const test& "
		//"		operator=(const test& t); "
		//" "
		//"		bool "
		//"		operator==(const test& t) const; "
		" "
		"		void* "
		"		operator new[](long unsigned int, void*); "
		" "
		"		void "
		"		operator delete[](void*); "
		" "
		"		operator int() const; "
		" "
		"		static "
		"		bool "
		"		static_function(); "
		" "
		"		inline "
		"		int "
		"		value() const; "
		" "
		"		virtual "
		"		void "
		"		pure_virtual(); "
		//"		pure_virtual() = 0; "
		" "
		"	protected: "
		"		void "
		"		update(); "
		" "
		"	private: "
		"		int value_; "
		"		static const bool b = false; "
		"}; "
		" "
		//"test::test(int) "
		//"{ "
		//"} "
		//" "
		//"test::test(const test&) "
		//"{ "
		//"} "
		//" "
		//"test::~test() "
		//"{ "
		//"} "
		//" "
		//"const test& "
		//"test::operator=(const test& rhs) "
		//"{ "
		//"	value_ = rhs.value_; "
		//"	return *this; "
		//"} "
		//" "
		//"bool "
		//"test::operator==(const test& rhs) const "
		//"{ "
		//"	return value_ == rhs.value_; "
		//"} "
		//" "
		//"void* "
		//"test::operator new[](long unsigned int, void*) "
		//"{ "
		//"	return 0; "
		//"} "
		//" "
		//"void "
		//"test::operator delete[](void*) "
		//"{ "
		//"} "
		//" "
		//"test::operator int() const "
		//"{ "
		//"	return value_; "
		//"} "
		//" "
		//"bool "
		//"test::static_function() "
		//"{ "
		//"	return b; "
		//"} "
		//" "
		//"inline "
		//"int "
		//"test::value() const "
		//"{ "
		//"	return value_; "
		//"} "
		//" "
		//"void "
		//"test::pure_virtual() "
		//"{ "
		//"} "
	);

	//namespaces
	auto expected_semantic_graph = namespace_::make_shared();
	auto namespace_n = namespace_::make_shared("n");
	auto namespace_n2 = namespace_::make_shared("n2");

	//classes
	auto class_virtual_base = class_::make_shared("virtual_base");
	auto class_virtual_base2 = class_::make_shared("virtual_base2");
	auto class_super_test = class_::make_shared("super_test");
	auto class_test = class_::make_shared("test");

	//constructors/destructor
	auto constructor_test = std::make_shared<constructor>
	(
		function_parameter_list
		(
			{
				std::make_shared<function_parameter>
				(
					fundamental_type::INT,
					"i"
				)
			}
		)/*,
		true*/
	);
	auto constructor_test_copy = std::make_shared<constructor>
	(
		function_parameter_list
		(
			{
				std::make_shared<function_parameter>
				(
					std::make_shared<const reference>
					(
						std::make_shared<const const_>
						(
							//std::shared_ptr<const class_>(class_test)
							fundamental_type::INT
						)
					),
					"t"
				)
			}
		)
	);
	auto destructor_test = std::make_shared<destructor>(false, false);

	//operator functions
	auto operator_function_test_new_array = std::make_shared<operator_member_function>
	(
		overloadable_operator::NEW_ARRAY,
		std::make_shared<const pointer>
		(
			fundamental_type::VOID
		),
		function_parameter_list
		(
			{
				std::make_shared<function_parameter>
				(
					fundamental_type::UNSIGNED_LONG_INT,
					""
				),
				std::make_shared<function_parameter>
				(
					std::make_shared<const pointer>
					(
						fundamental_type::VOID
					),
					""
				)
			}
		)
	);
	auto operator_function_test_delete_array = std::make_shared<operator_member_function>
	(
		overloadable_operator::DELETE_ARRAY,
		fundamental_type::VOID,
		function_parameter_list
		(
			{
				std::make_shared<function_parameter>
				(
					std::make_shared<const pointer>
					(
						fundamental_type::VOID
					),
					""
				)
			}
		)
	);

	//conversion function
	auto conversion_function_test_int = std::make_shared<conversion_function>
	(
		fundamental_type::INT,
		false,
		true
	);

	//simple functions
	auto simple_function_test_static_function =
		std::make_shared<simple_member_function>
		(
			"static_function",
			fundamental_type::BOOL,
			function_parameter_list(),
			false,
			true
		)
	;
	auto simple_function_test_value =
		std::make_shared<simple_member_function>
		(
			"value",
			fundamental_type::INT,
			function_parameter_list(),
			true,
			false,
			true
		)
	;
	auto simple_function_test_pure_virtual =
		std::make_shared<simple_member_function>
		(
			"pure_virtual",
			fundamental_type::VOID,
			function_parameter_list(),
			false,
			false,
			false,
			false,
			true,
			/*true*/ false
		)
	;
	auto simple_function_test_update =
		std::make_shared<simple_member_function>
		(
			"update",
			fundamental_type::VOID
		)
	;

	//variables
	auto variable_test_value = std::make_shared<variable>("value_", fundamental_type::INT);
	auto variable_test_b =
		std::make_shared<variable>
		(
			"b",
			std::make_shared<const const_>(fundamental_type::BOOL),
			true
		)
	;

	//assembling
	expected_semantic_graph->add_member(namespace_n);
	namespace_n->add_member(namespace_n2);
	namespace_n2->add_member(class_super_test);
	expected_semantic_graph->add_member(class_virtual_base);
	expected_semantic_graph->add_member(class_virtual_base2);
	expected_semantic_graph->add_member(class_test);
	class_test->add_base_class(class_super_test);
	class_test->add_base_class(class_virtual_base, class_::access::PRIVATE, true);
	class_test->add_base_class(class_virtual_base2, class_::access::PROTECTED, true);
	class_test->add_member(constructor_test);
	class_test->add_member(constructor_test_copy);
	class_test->set_destructor(destructor_test);
	class_test->add_member(operator_function_test_new_array);
	class_test->add_member(operator_function_test_delete_array);
	class_test->add_member(conversion_function_test_int);
	class_test->add_member(simple_function_test_static_function);
	class_test->add_member(simple_function_test_value);
	class_test->add_member(simple_function_test_pure_virtual);
	class_test->add_member(simple_function_test_update, class_::access::PROTECTED);
	class_test->add_member(variable_test_value, class_::access::PRIVATE);
	class_test->add_member(variable_test_b, class_::access::PRIVATE);

	BOOST_CHECK(*semantic_graph == *expected_semantic_graph);
}

} //namespace semantic_analysis

