#include "../ujvm.h"

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>


class AlgTestSuite : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(AlgTestSuite);
    CPPUNIT_TEST(testRegExp1);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  protected:
  void testRegExp1();
};

void AlgTestSuite::setUp()
{
  
}

void AlgTestSuite::tearDown()
{
  
}

void AlgTestSuite::testRegExp1()
{
  
}


int main(int argc, char *argv[])
{
  CppUnit::TextUi::TestRunner testRunner;
  testRunner.addTest(AlgTestSuite::suite());
  return !testRunner.run();
}
