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

BOOST_AUTO_TEST_CASE(nested_unnamed_namespaces)
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
			namespace
			{
				class c{};
			}
		}

		c c0;
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_xxx = new unnamed_namespace();
	auto namespace_xxx_xxx = new unnamed_namespace();

	//classes
	auto class_xxx_xxx_c = new class_("c");

	//assembling
	semantic_graph.set_unnamed_namespace(std::unique_ptr<unnamed_namespace>(namespace_xxx));
	namespace_xxx->set_unnamed_namespace(std::unique_ptr<unnamed_namespace>(namespace_xxx_xxx));
	namespace_xxx_xxx->add_member(std::unique_ptr<class_>(class_xxx_xxx_c));

	//look up c from global namespace, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, class_>
			(
				"c",
				&semantic_graph
			)
		;

		BOOST_CHECK_EQUAL(found_entity, class_xxx_xxx_c);
	}
}

} //namespace name_lookup

