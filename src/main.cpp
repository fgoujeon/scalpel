#include <iostream>
#include <cstring>
#include <boost/spirit.hpp>
#include "CppParser/Grammar.h"

using namespace boost::spirit;
using namespace std;

int
main()
{
    CppParser::Grammar grammar;

    const char* tests[][2] =
    {
        /*{
            "test<double(friend ...)>;",
            "ok"
        },
        {
            "0543;",
            "ok"
        },
        {
            "vector<char(friend, typedef, ...)>;",
            "ok"
        },
        {
            "vector<char(friend, typedef, auto, register, static, bool...)>;",
            "ok"
        },
        {
            "vector<char(friend, typedef, auto, inline, virtual, char, bool...)>;",
            "ok"
        },
        {
            "vector<vector<char>>;",
            "ok"
        },
        {
            "operator/;",
            "ok"
        },
        {
            "operatora;",
            "ok"
        },
        {
            "operator double* const;",
            "ok"
        },
        {
            "operator struct;",
            "nok"
        },
        {
            "class<>;",
            "nok"
        },
        {
            "::operator *;",
            "ok"
        },
        {
            "::test;",
            "ok"
        },
        {
            "::test<machin<>>;",
            "ok"
        },
        {
            "::char<machin<>>;",
            "nok"
        },
        {
            "test::truc;",
            "ok"
        },
        {
            "test::template;",
            "nok"
        },
        {
            "test::templatea;",
            "ok"
        },
        {
            "::test :: templatea;",
            "ok"
        },
        {
            "::test::bidule::truc::machin;",
            "ok"
        },
        {
            "::test::template bidule::truc::template machin;",
            "ok"
        },
        {
            "vector<truc::template bidule>;",
            "ok"
        },
        {
            "operator double ::machin::template bidule::* const;",
            "ok"
        },
        {
            "operator double machin::template bidule::* const;",
            "ok"
        },
        {
            "vector<enum truc::bidule::chouette>;",
            "ok"
        },
        {
            "vector<enum truc::bidule::chouette machin<plouf>>;",
            "ok"
        },
        {
            "vector<typename truc::bidule::template machin<plouf>>;",
            "ok"
        },
        {
            "vector<typename ::truc::bidule::template machin<plouf>>;",
            "ok"
        },
        {
            "vector<typename truc::bidule::machin>;",
            "ok"
        },
        {
            "vector<class truc::bidule::chouette machin<plouf>>;",
            "ok"
        },
        {
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
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = (double)1,\n"
            "       TWO=this,\n"
            "       THREE\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = (double)1 .* 3->*0x23,\n"
            "       TWO=this,\n"
            "       THREE\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = 4 * 0.25 / 0x1\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = number == 1 ? number : 1\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = ++(double)1\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = *(double)1\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector\n"
            "<\n"
            "   enum\n"
            "   {\n"
            "       ONE = sizeof(double)\n"
            "   }\n"
            ">;",
            "ok"
        },
        {
            "vector<sizeof(double)>;",
            "ok"
        },
        {
            "(cond1 && cond2);",
            "ok"
        },
        {
            "number = 42;",
            "ok"
        },
        {
            "dynamic_cast<double>(42);",
            "ok"
        },
        {
            "typeid(something);",
            "ok"
        },
        {
            "typename truc::bidule::chouette();",
            "ok"
        },
        {
            "typename truc::bidule::chouette<double, const char*>();",
            "ok"
        },
        {
            "char();",
            "ok"
        },
        {
            "++i;",
            "ok"
        },
        {
            "i++;",
            "ok"
        },
        {
            "table[34];",
            "ok"
        },
        {
            "object.~object;",
            "ok"
        },
        {
            "std::vector.::std::~vector;",
            "ok"
        },
        {
            "new Potatoe(RED, 50);",
            "ok"
        },
        {
            "new ::Networking::HttpClient;",
            "ok"
        },
        {
            "::new (42, 32 + 3)(bubble)(STRAWBERRY);",
            "ok"
        },
        {
            "new double&[plouf];",
            "ok"
        },
        {
            "delete this;",
            "ok"
        },
        {
            "label: do_this();",
            "ok"
        },
        {
            "case 2: do_this();",
            "ok"
        },
        {
            "{"
            "   i++;"
            "}",
            "ok"
        },
        {
            "for(i = 0; i < 23; ++i)"
            "{"
            "    do_something();"
            "}",
            "ok"
        },
        {
            "return return_value;",
            "ok"
        },
        {
            "const unsigned int i;",
            "ok"
        },
        {
            "asm"
            "("
            "    \"movb 0x61,\%al\""
            ");",
            "ok"
        },*/
        {
            "namespace io = boost::iostreams;",
            "ok"
        },
        {
            "using namespace boost::iostreams;",
            "ok"
        },
        {
            "using std::vector::push_back;",
            "ok"
        },
        {
            "namespace CppParser"
            "{"
            "    int i;"
            "}",
            "ok"
        },
        {
            "namespace"
            "{"
            "    int i;"
            "}",
            "ok"
        },
        {
            "extern \"C\" int i;",
            "ok"
        },
        {
            "extern \"C\" double d;",
            "ok"
        },
        {
            "extern \"C\""
            "{"
            "    int i;"
            "    double d;"
            "}",
            "ok"
        },
        {
            "template int i;",
            "ok"
        },
        {
            "template<> int i;",
            "ok"
        },
        {
            "::test::bidule::truc::machin;",
            "ok"
        },
        {
            "int i;",
            "ok"
        },
        {
            "int i, j;",
            "ok"
        },
        {
            "const double d, d2;",
            "ok"
        },
        {
            "const Object o;",
            "ok"
        },
        {
            "Object;",
            "ok"
        },
        {
            "const Object& object;",
            "ok"
        },
        {
            "double* const d, *d2;",
            "ok"
        },
        {
            "std::vector<double> v;",
            "ok"
        },
        {
            "::Factories::CowFactory f;",
            "ok"
        },
        {
            "Object o = {};",
            "ok"
        },
        {
            "Pen pen(Color::BLUE, 15, Geometry::CENTIMETER);",
            "ok"
        },
        {
            "bool bigger = number > this->size;",
            "ok"
        },
        {
            "std::vector<int> v = {0, 23, 65};",
            "ok"
        },
        {
            "int square(Object)"
            "{"
            "}",
            "ok"
        },
        {
            "",
            ""
        }
    };

    const string ok("ok");

    unsigned int nerror = 0;

    for(unsigned int i = 0; strcmp(tests[i][0], "") != 0; ++i)
    {
        cout << tests[i][0] << "\n";

        parse_info<> info = parse(tests[i][0], grammar, space_p);

        if(tests[i][1] == ok) //should success
        {
            if(info.full) //success
            {
                cout << "Parsing succeeded as expected... Success!\n";
            }
            else
            {
                cout << "-------------------------\n";
                cout << "Parsing failed\n";
                cout << "stopped at: \": " << info.stop << "\"\n";
                cout << "-------------------------\n";
                ++nerror;
            }
        }
        else //should fail
        {
            if(info.full)
            {
                cout << "-------------------------\n";
                cout << "Parsing succeeded, shouldn't\n";
                cout << "-------------------------\n";
                ++nerror;
            }
            else
            {
                cout << "Parsing failed as expected... Success!\n";
            }
        }

        cout << "\n";
    }

    cout << nerror << " error(s)";

    return 0;
}
