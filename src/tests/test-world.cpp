/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../model/world.h"
#include "../model/number.h"
#include "../model/agent.h"
#include "../model/user-function.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;
using namespace stibbons;

class TestWorld : public TestCase{
	CPPUNIT_TEST_SUITE(TestWorld);
	CPPUNIT_TEST(testAjoutTurtle);
	CPPUNIT_TEST(testExporte);
	CPPUNIT_TEST_SUITE_END();

	public :
		WorldPtr world;
		Line* line;
		TurtlePtr turtle;
		FunctionPtr f;

		void setUp(){
			auto worldSize = Size(2);
			worldSize.setValue(0, 3);
			worldSize.setValue(1, 3);
			auto zoneSize = Size(2);
			zoneSize.setValue(0, 10);
			zoneSize.setValue(1, 10);
			auto warp = vector<BorderType>();
			warp.push_back(BorderType::NONE);
			warp.push_back(BorderType::NONE);
			world = stibbons::World::construct(worldSize, zoneSize, warp);
			line=new Line(Point());
			turtle=Turtle::construct();
			f=make_shared<UserFunction>(nullptr);
		}

		void testAjoutTurtle() {
			cout << "TestWorld::testAjoutTurtle" << endl;
			world->createBreed(f,"setup");
		}

		void testExporte() {
			cout << "TestWorld::testExporte" << endl;
			FunctionPtr function=nullptr;

			NumberPtr n=make_shared<Number>(4);
			pair<string,NumberPtr> p("a",n);
			BooleanPtr find=make_shared<Boolean>(true);
			pair<string,BooleanPtr> bo("find",find);
			StringPtr str=make_shared<String>("Kelly");
			pair<string,StringPtr> strin("name",str);

			TurtlePtr t=world->createBreed(function,"lila")->createTurtle();
			TurtlePtr t2=world->createBreed(function)->createTurtle();
			t->setProperty("a",n);
			t->setProperty("find",find);
			t->setProperty("name",str);

			world->exporte();
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
