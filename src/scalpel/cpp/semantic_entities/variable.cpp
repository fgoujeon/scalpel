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

#include "variable.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

variable::variable
(
	const std::string& name,
	const weak_type_variant& type,
	bool is_static
):
	type_(type),
	name_(name),
	is_static_(is_static)
{
}

variable::variable(const variable& rhs):
	type_(rhs.type_),
	name_(rhs.name_),
	is_static_(rhs.is_static_)
{
}

variable::variable(variable&& rhs):
	type_(rhs.type_),
	name_(std::move(rhs.name_)),
	is_static_(rhs.is_static_)
{
}

const variable&
variable::operator=(variable&& rhs)
{
	type_ = rhs.type_;
	name_ = std::move(rhs.name_);
	is_static_ = rhs.is_static_;

	return *this;
}

type_variant
variable::type() const
{
	return to_type_variant(type_);
}

const std::string&
variable::name() const
{
	return name_;
}

bool
variable::is_static() const
{
	return is_static_;
}

bool
variable::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_shared_ptr_variant
variable::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
variable::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

bool
operator==(const variable& lhs, const variable& rhs)
{
	return cycle_proof_equals(lhs, rhs, 0);
}

bool
operator!=(const variable& lhs, const variable& rhs)
{
	return !operator==(lhs, rhs);
}

unsigned int
get_declarative_region_back_index
(
	declarative_region_shared_ptr_variant current_declarative_region,
	const std::weak_ptr<const class_>& class_to_be_found,
	const unsigned int max_back_index
)
{
	unsigned int back_index = 1;

	while(back_index <= max_back_index)
	{
		if(const std::shared_ptr<class_>* opt_current_class = utility::get<class_>(&current_declarative_region))
		{
			if(*opt_current_class == class_to_be_found.lock()) return back_index;
		}

		//iterate to the enclosing declarative region
		current_declarative_region = get_enclosing_declarative_region(current_declarative_region);
		++back_index;
	}

	return 0;
}

bool
safe_type_comparison
(
	const variable& lhs,
	const variable& rhs,
	const unsigned int enclosing_declarative_region_count
)
{
	if(enclosing_declarative_region_count > 0)
	{
		if(!have_same_qualifiers(lhs.type(), rhs.type()))
			return false;

		const std::weak_ptr<const class_>* opt_lhs_type;
		const std::weak_ptr<const class_>* opt_rhs_type;

		const unqualified_type_variant& lhs_unqualified_type = get_unqualified_type(to_weak_type_variant(lhs.type()));
		const unqualified_type_variant& rhs_unqualified_type = get_unqualified_type(to_weak_type_variant(rhs.type()));
		if
		(
			(opt_lhs_type = utility::get<std::weak_ptr<const class_>>(&lhs_unqualified_type)) &&
			(opt_rhs_type = utility::get<std::weak_ptr<const class_>>(&rhs_unqualified_type))
		)
		{
			const unsigned int lhs_back_index = get_declarative_region_back_index
			(
				lhs.enclosing_declarative_region(),
				*opt_lhs_type,
				enclosing_declarative_region_count
			);
			const unsigned int rhs_back_index = get_declarative_region_back_index
			(
				rhs.enclosing_declarative_region(),
				*opt_rhs_type,
				enclosing_declarative_region_count
			);

			if(lhs_back_index != 0 && rhs_back_index != 0)
				return lhs_back_index == rhs_back_index;
		}
	}

	//directly compare lhs' and rhs' types
	return equals(lhs.type(), rhs.type());
}

bool
cycle_proof_equals
(
	const variable& lhs,
	const variable& rhs,
	const unsigned int enclosing_declarative_region_count
)
{
	return
		lhs.name() == rhs.name() &&
		lhs.is_static() == rhs.is_static() &&
		safe_type_comparison(lhs, rhs, enclosing_declarative_region_count)
	;
}

}}} //namespace scalpel::cpp::semantic_entities

