/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cassert>
#include "class_.h"
#include "enum_.h"
#include "typedef_.h"
#include "../util/null_deleter.h"

#include "namespace_.h"

namespace cppparser { namespace program_tree
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    m_name(name)
{
}

const std::string&
namespace_::name() const
{
    return m_name;
}

std::string
namespace_::full_name() const
{
    std::string full_name;

    if(!is_global())
    {
        full_name = parent()->full_name() + "::";
    }
    full_name += m_name;

    return full_name;
}

bool
namespace_::is_global() const
{
    return !has_parent();
}

const std::vector<std::shared_ptr<namespace_member>>&
namespace_::members() const
{
    return m_members;
}

template <>
const std::vector<std::shared_ptr<namespace_>>&
namespace_::members() const
{
    return m_namespaces;
}

template <>
const std::vector<std::shared_ptr<class_>>&
namespace_::members() const
{
    return m_classes;
}

template <>
const std::vector<std::shared_ptr<union_>>&
namespace_::members() const
{
    return m_unions;
}

}} //namespace cppparser::program_tree
