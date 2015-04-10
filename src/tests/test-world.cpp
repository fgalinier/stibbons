#include "../model/world.h"

#include "../model/user-function.h"

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
		Function* f;

		void setUp(){
			auto worldSize = Size(2);
			worldSize.setValue(0, 10);
			worldSize.setValue(1, 10);
			auto zoneSize = Size(2);
			zoneSize.setValue(0, 10);
			zoneSize.setValue(1, 10);
			world=new stibbons::World(worldSize, zoneSize);
			line=new Line();
			turtle=new Turtle();
			f=new UserFunction(nullptr);
		}

		void testAjoutTurtle() {
			cout << "TestWorld::testAjoutTurtle" << endl;
			world->createBreed(*f,"setup");
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
