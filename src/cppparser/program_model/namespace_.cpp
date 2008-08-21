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
#include <algorithm>
#include <stdexcept>
#include "class_.h"
#include "enum_.h"
#include "typedef_.h"

#include "namespace_.h"

namespace cppparser { namespace program_model
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    m_name(name)
{
}

namespace_::~namespace_()
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
        full_name = parent().lock()->full_name() + "::";
    }
    full_name += m_name;

    return full_name;
}

bool
namespace_::is_global() const
{
    return has_parent();
}

std::shared_ptr<namespace_>
namespace_::find_namespace(const std::string& name) const
{
    ///@todo use STL algo. instead
    for
    (
        std::vector<std::shared_ptr<namespace_>>::const_iterator i = m_namespaces.begin();
        i != m_namespaces.end();
        ++i
    )
    {
        std::shared_ptr<namespace_> n = *i;
        if(n->name() == name)
        {
            return n;
        }
    }

    return std::shared_ptr<namespace_>();
}

const std::vector<std::shared_ptr<namespace_item>>&
namespace_::items() const
{
    return m_items;
}
/*
void
namespace_::add(std::shared_ptr<namespace_item> a_namespace_item)
{
    //check whether no already existing namespace has the same name
    if(contains_namespace(a_namespace_item->name()))
    {
        throw std::runtime_error(m_name + " already contains a namespace named \"" + a_namespace_item->name() + "\".");
    }

    m_items.push_back(a_namespace_item);
}*/

void
namespace_::add(std::shared_ptr<namespace_> a_namespace)
{
    //check whether no already existing namespace has the same name
    if(find_namespace(a_namespace->name()))
    {
        throw std::runtime_error(m_name + " already contains a namespace named \"" + a_namespace->name() + "\".");
    }

    m_namespaces.push_back(a_namespace);
    m_items.push_back(a_namespace);
}

}} //namespace cppparser::program_model
