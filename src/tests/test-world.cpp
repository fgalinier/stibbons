#include "../model/world.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;
using namespace stibbons;

class TestWorld : public TestCase{
	CPPUNIT_TEST_SUITE(TestWorld);
	CPPUNIT_TEST(testAjoutTurtle);
	CPPUNIT_TEST_SUITE_END();

	public :
		World* world;
		Line* line;
		Turtle* turtle;

		void setUp(){
			world=new stibbons::World(nullptr,10,10);
			line=new Line();
			turtle=new Turtle(nullptr);
		}

		void testAjoutTurtle() {
			cout << "TestWorld::testAjoutTurtle" << endl;
			turtle->turnRight(90);
			world->addTurtle(turtle);
			auto vector=world->getTurtles();
			for (auto i=vector.begin();i<vector.end();i++)
			{
				CPPUNIT_ASSERT_EQUAL (90.0, (*i)->getAngle());
			}
		}

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestWorld, "TestWorld" );

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
