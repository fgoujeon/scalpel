/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "template_declaration.hpp"

#include "template_declaration_impl.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

template_declaration::template_declaration
(
    bool export_keyword,
    //template_parameter_list m_template_parameter_list;
    declaration&& a_declaration
):
	pimpl_
	(
		std::make_shared<template_declaration_impl>
		(
			export_keyword,
			a_declaration
		)
	)
{
}

bool
template_declaration::has_export_keyword() const
{
	return pimpl_->has_export_keyword();
}

const declaration&
template_declaration::get_declaration() const
{
	return pimpl_->get_declaration();
}

}}} //namespace socoa::cpp::syntax_tree
