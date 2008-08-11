#include <cppunit/ui/text/TestRunner.h>
#include "SingleExpressionTest.h"

int main(int argc, char **argv)
{
	CppUnit::TextUi::TestRunner runner;

	runner.addTest(SingleExpressionTest::suite());
	runner.run();

	return 0;
}

