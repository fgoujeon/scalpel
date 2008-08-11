#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <CppParser/Grammar.h>

class SingleExpressionTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SingleExpressionTest);
    CPPUNIT_TEST(parse_well_formed_expressions);
    CPPUNIT_TEST(parse_ill_formed_expressions);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();
        void parse_well_formed_expressions();
        void parse_ill_formed_expressions();

    private:
        CppParser::Grammar grammar;
        std::vector<std::string> well_formed_expressions;
        std::vector<std::string> ill_formed_expressions;
};

