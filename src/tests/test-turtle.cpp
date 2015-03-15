#include "../model/turtle.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestTurtle : public TestCase{
	CPPUNIT_TEST_SUITE(TestTurtle);
	CPPUNIT_TEST(testAngle);
	CPPUNIT_TEST(testForward);
	CPPUNIT_TEST_SUITE_END();

	public :
		stibbons::Turtle turtle = stibbons::Turtle(0);

		void setUp(){
			turtle=stibbons::Turtle(0);
		}

		void testAngle() {
			cout << "TestTurtle::testAngle" << endl;
			CPPUNIT_ASSERT_EQUAL (0.0, turtle.getAngle());
			turtle.turnRight(90.0);
			CPPUNIT_ASSERT_EQUAL (90.0, turtle.getAngle());
			turtle.turnLeft(90.0);
			CPPUNIT_ASSERT_EQUAL (0.0, turtle.getAngle());
			turtle.turnLeft(90.0);
			CPPUNIT_ASSERT_EQUAL (270.0, turtle.getAngle());
		}

		void testForward() {
			cout << "TestTurtle::testForward" << endl;
			CPPUNIT_ASSERT_EQUAL (0.0, turtle[0]);
			CPPUNIT_ASSERT_EQUAL (0.0, turtle[1]);
			turtle.forward(1.0);
			CPPUNIT_ASSERT_EQUAL (1.0, turtle[0]);
			CPPUNIT_ASSERT_EQUAL (0.0, turtle[1]);
			turtle.turnRight(90.0);
			turtle.forward(1.0);
			CPPUNIT_ASSERT_EQUAL (1.0, turtle[0]);
			CPPUNIT_ASSERT_EQUAL (1.0, turtle[1]);
		}
};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestTurtle, "TestTurtle" );

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: t
 * truncate-lines: 1
 * End:
 *
 * vim:set ft=cpp ts=4 sw=4 sts=4
 */
