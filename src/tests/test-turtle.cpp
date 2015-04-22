#include "../model/turtle.h"
#include "../model/value.h"
#include "../model/number.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;
using namespace stibbons;

class TestTurtle : public TestCase{
	CPPUNIT_TEST_SUITE(TestTurtle);
	CPPUNIT_TEST(testAngle);
	CPPUNIT_TEST(testForward);
	CPPUNIT_TEST(testCommunication);
	CPPUNIT_TEST_SUITE_END();

	public :
/*Explication : pas de constructeur vide ds tortue, donc on ne peux pas laisser turtle, et seg fault si redefinit dans le setUp => pointeur ou constructeur vide dans tortue*/
		stibbons::TurtlePtr turtle;// stibbons::Turtle(0, nullptr);
     	stibbons::TurtlePtr t2;

		void setUp(){
			turtle = stibbons::Turtle::construct();
			t2 = stibbons::Turtle::construct();
		}

		void testAngle() {
			cout << "TestTurtle::testAngle" << endl;
			CPPUNIT_ASSERT_EQUAL (0.0, turtle->getAngle());
			turtle->turnRight(90.0);
			CPPUNIT_ASSERT_EQUAL (90.0, turtle->getAngle());
			turtle->turnLeft(90.0);
			CPPUNIT_ASSERT_EQUAL (0.0, turtle->getAngle());
			turtle->turnLeft(90.0);
			CPPUNIT_ASSERT_EQUAL (270.0, turtle->getAngle());
		}

		void testForward() {
			cout << "TestTurtle::testForward" << endl;
			auto position = turtle->getPosition();
			CPPUNIT_ASSERT_EQUAL (0.0, position.getValue(0));
			CPPUNIT_ASSERT_EQUAL (0.0, position.getValue(1));
			turtle->forward(1.0);
			position = turtle->getPosition();
			CPPUNIT_ASSERT_EQUAL (1.0, position.getValue(0));
			CPPUNIT_ASSERT_EQUAL (0.0, position.getValue(1));
			turtle->turnRight(90.0);
			turtle->forward(1.0);
			position = turtle->getPosition();
			CPPUNIT_ASSERT_EQUAL (1.0, position.getValue(0));
			CPPUNIT_ASSERT_EQUAL (1.0, position.getValue(1));
		}

		void testCommunication(){
			cout << "TestTurtle::testCommunication" << endl;
			auto v=make_shared<Number>(2);
			turtle->send(t2,v);
			auto r=t2->recv();
			auto n=dynamic_pointer_cast<Number>(r.second);
			auto n2=dynamic_pointer_cast<Number>(v);
			CPPUNIT_ASSERT_EQUAL(n->getValue(),n2->getValue());
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
