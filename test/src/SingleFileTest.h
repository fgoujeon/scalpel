#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <CppParser/Grammar.h>

class SingleFileTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SingleFileTest);
    CPPUNIT_TEST(parse_files);
    CPPUNIT_TEST_SUITE_END();

    public:
        void parse_files();

    private:
        CppParser::Grammar grammar;
};

