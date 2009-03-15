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

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_NAMESPACE_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_NAMESPACE_HPP

#include <string>
#include <vector>
#include <boost/variant.hpp>
#include <boost/noncopyable.hpp>

namespace socoa { namespace cpp { namespace semantic_graph
{

///\todo should be noncopyable, but boost::variant doesn't support move semantics (yet?).
/**
Represents a C++ namespace.
*/
class namespace_//: public boost::noncopyable
{
    public:
		class member_t;

        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit
		namespace_(const std::string& name);

		/**
		 * Move constructor.
		 */
		//namespace_(namespace_&& n);

        /**
        @return the name of the namespace
        Anonymous namespaces return an empty string.
        */
        const std::string&
        get_name() const;

        /**
        @return true if the namespace has the given name
        */
        bool
        has_that_name(const std::string& name) const;

        /**
        @return the full name of the namespace, including all enclosing scopes (e.g. ::foo::bar)
        */
        const std::string
        get_full_name() const;

        bool
        is_a_type() const;

//        /**
//        @return true if the namespace is the global one, false otherwise
//        */
//        bool
//        is_global() const;
//
//        /**
//        @return true if the namespace has a enclosing scope scope
//        */
//        bool
//        has_enclosing_scope() const;
//
//        /**
//        @return the enclosing scope of the namespace
//        */
//        std::shared_ptr<name_tree_composite>
//        get_enclosing_scope();
//
//        /**
//        @return the enclosing scope of the namespace
//        */
//        const std::shared_ptr<name_tree_composite>
//        get_enclosing_scope() const;
//
//        /**
//        Sets the enclosing scope of the namespace.
//        */
//        void
//        set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope);
//
        /**
        @return the namespace's member list (i.e. the list of namespaces, classes, functions, etc.)
        */
        const std::vector<member_t>&
        get_members() const;

        void
        add(namespace_&& member);

        void
        clear();

//        inline
//        const std::vector<base_specifier>&
//        get_base_specifiers() const;

    private:
        std::string name_;
        std::vector<member_t> members_;
};

typedef
	boost::variant<namespace_>
	namespace_member_t
;

class namespace_::member_t: public namespace_member_t
{
	public:
		member_t(namespace_&& o): namespace_member_t(o){}
};

//inline
//const std::vector<base_specifier>&
//namespace_::get_base_specifiers() const
//{
//    return empty_base_specifiers_;
//}

}}} //namespace socoa::cpp::semantic_graph

#endif
