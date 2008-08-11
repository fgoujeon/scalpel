#include <cppunit/ui/text/TestRunner.h>
#include "SingleExpressionTest.h"
#include "SingleFileTest.h"

int main(int argc, char **argv)
{
	CppUnit::TextUi::TestRunner runner;

	runner.addTest(SingleExpressionTest::suite());
	runner.addTest(SingleFileTest::suite());
	runner.run();

	return 0;
}

