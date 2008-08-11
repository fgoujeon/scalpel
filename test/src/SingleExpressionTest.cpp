#include <sstream>
#include <boost/spirit.hpp>
#include <CppParser/Grammar.h>
#include <cppunit/TestSuite.h>

#include "SingleExpressionTest.h"

using namespace boost::spirit;
using namespace std;

void SingleExpressionTest::setUp()
{
    /*
     * Well formed expressions
    */
    well_formed_expressions.push_back("test<double(friend ...)>;");
    well_formed_expressions.push_back("0543;");
    well_formed_expressions.push_back("vector<char(friend, typedef, ...)>;");
    well_formed_expressions.push_back("vector<char(friend, typedef, auto, register, static, bool...)>;");
    well_formed_expressions.push_back("vector<char(friend, typedef, auto, inline, virtual, char, bool...)>;");
    well_formed_expressions.push_back("vector<vector<char>>;");
    well_formed_expressions.push_back("operator/;");
    well_formed_expressions.push_back("operatora;");
    well_formed_expressions.push_back("operator double* const;");
    well_formed_expressions.push_back("::operator *;");
    well_formed_expressions.push_back("::test;");
    well_formed_expressions.push_back("::test<machin<>>;");
    well_formed_expressions.push_back("test::truc;");
    well_formed_expressions.push_back("test::templatea;");
    well_formed_expressions.push_back("::test :: templatea;");
    well_formed_expressions.push_back("::test::bidule::truc::machin;");
    well_formed_expressions.push_back("::test::template bidule::truc::template machin;");
    well_formed_expressions.push_back("vector<truc::template bidule>;");
    well_formed_expressions.push_back("operator double ::machin::template bidule::* const;");
    well_formed_expressions.push_back("operator double machin::template bidule::* const;");
    well_formed_expressions.push_back("vector<enum truc::bidule::chouette>;");
    well_formed_expressions.push_back("vector<enum truc::bidule::chouette machin<plouf>>;");
    well_formed_expressions.push_back("vector<typename truc::bidule::template machin<plouf>>;");
    well_formed_expressions.push_back("vector<typename ::truc::bidule::template machin<plouf>>;");
    well_formed_expressions.push_back("vector<typename truc::bidule::machin>;");
    well_formed_expressions.push_back("vector<class truc::bidule::chouette machin<plouf>>;");
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = 1,\n"
        "       TWO=this,\n"
        "       THREE,\n"
        "       FOUR = vector\t\n"
        "       <\n"
        "           enum\n"
        "           {\n"
        "               MONDAY = 0.1,\n"
        "               TUESDAY= something,\n"
        "               WEDNESDAY\n"
        "           }\n"
        "       >\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = (double)1,\n"
        "       TWO=this,\n"
        "       THREE\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = (double)1 .* 3->*0x23,\n"
        "       TWO=this,\n"
        "       THREE\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = 4 * 0.25 / 0x1\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = number == 1 ? number : 1\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = ++(double)1\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = *(double)1\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back
    (
        "vector\n"
        "<\n"
        "   enum\n"
        "   {\n"
        "       ONE = sizeof(double)\n"
        "   }\n"
        ">;"
    );
    well_formed_expressions.push_back("vector<sizeof(double)>;");
    well_formed_expressions.push_back("(cond1 && cond2);");
    well_formed_expressions.push_back("number = 42;");
    well_formed_expressions.push_back("dynamic_cast<double>(42);");
    well_formed_expressions.push_back("typeid(something);");
    well_formed_expressions.push_back("typename truc::bidule::chouette();");
    well_formed_expressions.push_back("typename truc::bidule::chouette<double, const char*>();");
    well_formed_expressions.push_back("char();");
    well_formed_expressions.push_back("++i;");
    well_formed_expressions.push_back("i++;");
    well_formed_expressions.push_back("table[34];");
    well_formed_expressions.push_back("object.~object;");
    well_formed_expressions.push_back("std::vector.::std::~vector;");
    well_formed_expressions.push_back("new Potatoe(RED, 50);");
    well_formed_expressions.push_back("new ::Networking::HttpClient;");
    well_formed_expressions.push_back("::new (42, 32 + 3)(bubble)(STRAWBERRY);");
    well_formed_expressions.push_back("new double&[plouf];");
    well_formed_expressions.push_back("delete this;");
    well_formed_expressions.push_back("label: do_this();");
    well_formed_expressions.push_back("case 2: do_this();");
    well_formed_expressions.push_back
    (
        "{"
        "   i++;"
        "}"
    );
    well_formed_expressions.push_back
    (
        "for(i = 0; i < 23; ++i)"
        "{"
        "    do_something();"
        "}"
    );
    well_formed_expressions.push_back("return return_value;");
    well_formed_expressions.push_back("const unsigned int i;");
    well_formed_expressions.push_back
    (
        "asm"
        "("
        "    \"movb 0x61,al\""
        ");"
    );
    well_formed_expressions.push_back("namespace io = boost::iostreams;");
    well_formed_expressions.push_back("using namespace boost::iostreams;");
    well_formed_expressions.push_back("using std::vector::push_back;");
    well_formed_expressions.push_back
    (
        "namespace CppParser"
        "{"
        "    int i;"
        "}"
    );
    well_formed_expressions.push_back
    (
        "namespace"
        "{"
        "    int i;"
        "}"
    );
    well_formed_expressions.push_back("extern \"C\" int i;");
    well_formed_expressions.push_back("extern \"C\" double d;");
    well_formed_expressions.push_back
    (
        "extern \"C\""
        "{"
        "    int i;"
        "    double d;"
        "}"
    );
    well_formed_expressions.push_back("template int i;");
    well_formed_expressions.push_back("template<> int i;");
    well_formed_expressions.push_back("::test::bidule::truc::machin;");
    well_formed_expressions.push_back("int i;");
    well_formed_expressions.push_back("int i, j;");
    well_formed_expressions.push_back("const double d, d2;");
    well_formed_expressions.push_back("const Object o;");
    well_formed_expressions.push_back("Object;");
    well_formed_expressions.push_back("const Object& object;");
    well_formed_expressions.push_back("double* const d, *d2;");
    well_formed_expressions.push_back("std::vector<double> v;");
    well_formed_expressions.push_back("::Factories::CowFactory f;");
    well_formed_expressions.push_back("Object o = {};");
    well_formed_expressions.push_back("Pen pen(Color::BLUE, 15, Geometry::CENTIMETER);");
    well_formed_expressions.push_back("bool bigger = number > this->size;");
    well_formed_expressions.push_back("std::vector<int> v = {0, 23, 65};");
    well_formed_expressions.push_back
    (
        "int square(Object)"
        "{"
        "}"
    );
    well_formed_expressions.push_back("Test<(1 > 2)> test;");


    /*
     * Ill formed expressions
    */
    ill_formed_expressions.push_back("operator struct;");
    ill_formed_expressions.push_back("class<>;");
    ill_formed_expressions.push_back("::char<machin<>>;");
    ill_formed_expressions.push_back("test::template;");
}

void SingleExpressionTest::tearDown()
{
    well_formed_expressions.clear();
    ill_formed_expressions.clear();
}

void SingleExpressionTest::parse_well_formed_expressions()
{
    for(vector<string>::const_iterator i = well_formed_expressions.begin(); i != well_formed_expressions.end(); ++i)
    {
        parse_info<> info = parse(i->c_str(), grammar, space_p);

        ostringstream failure_message;
        failure_message << "Failed to parse:\n\t" << *i << "\n";
        failure_message << "Parsing stopped at:\n\t" << info.stop;

        CPPUNIT_ASSERT_MESSAGE
        (
            failure_message.str(),
            info.full
        );
    }
}

void SingleExpressionTest::parse_ill_formed_expressions()
{
    for(vector<string>::const_iterator i = ill_formed_expressions.begin(); i != ill_formed_expressions.end(); ++i)
    {
        parse_info<> info = parse(i->c_str(), grammar, space_p);

        ostringstream failure_message;
        failure_message << "Unexpectedly succeeded in parsing:\n\t" << *i;

        CPPUNIT_ASSERT_MESSAGE
        (
            failure_message.str(),
            !info.full
        );
    }
}
