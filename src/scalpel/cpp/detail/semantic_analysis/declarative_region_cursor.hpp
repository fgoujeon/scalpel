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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_DECLARATIVE_REGION_CURSOR_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_DECLARATIVE_REGION_CURSOR_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <boost/noncopyable.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class declarative_region_cursor: public boost::noncopyable
{
	public:
		typedef utility::shared_ptr_vector<semantic_entities::declarative_region> declarative_regions_t;

		declarative_region_cursor();

		void
		initialize(std::shared_ptr<semantic_entities::declarative_region> global_declarative_region);

		declarative_regions_t::range
		declarative_region_path();

		declarative_regions_t::const_range
		declarative_region_path() const;

		std::shared_ptr<semantic_entities::declarative_region>
		global_declarative_region();

		std::shared_ptr<semantic_entities::declarative_region>
		current_declarative_region();

		void
		enter_declarative_region(std::shared_ptr<semantic_entities::declarative_region> a_declarative_region);

		void
		enter_last_added_declarative_region();

		void
		leave_current_declarative_region();

	private:
		declarative_regions_t declarative_region_path_;
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
