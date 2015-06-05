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
		TurtlePtr turtle;// stibbons::Turtle(0, nullptr);
		TurtlePtr t2;
		WorldPtr world;
		

		void setUp(){
			auto worldSize = Size(2);
			worldSize.setValue(0, 10);
			worldSize.setValue(1, 10);
			auto zoneSize = Size(2);
			zoneSize.setValue(0, 10);
			zoneSize.setValue(1, 10);
			auto warp = vector<BorderType>();
			warp.push_back(BorderType::NONE);
			warp.push_back(BorderType::NONE);
			world = stibbons::World::construct(worldSize, zoneSize, warp);
			turtle = stibbons::Turtle::construct(nullptr, world);
			t2 = stibbons::Turtle::construct(nullptr, world);
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
