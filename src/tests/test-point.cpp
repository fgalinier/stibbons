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

#include "../model/point.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestPoint : public TestCase {
	CPPUNIT_TEST_SUITE(TestPoint);
	CPPUNIT_TEST(getValues);
	CPPUNIT_TEST(dimension);
	CPPUNIT_TEST_SUITE_END();

	public :
		stibbons::Point point2d;

		void setUp() {
			point2d.setValue(0, 2.0);
			point2d.setValue(1, 4.0);
		}

		void getValues() {
			cout << "TestPoint::getValues" << endl;
			CPPUNIT_ASSERT_EQUAL (point2d[0], 2.0);
			CPPUNIT_ASSERT_EQUAL (point2d[1], 4.0);
		}

		void dimension() {
			cout << "TestPoint::dimension" << endl;
			CPPUNIT_ASSERT_THROW    (point2d[-1], out_of_range);
			CPPUNIT_ASSERT_NO_THROW (point2d[0]);
			CPPUNIT_ASSERT_NO_THROW (point2d[1]);
			CPPUNIT_ASSERT_THROW    (point2d[2], out_of_range);
		}
};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestPoint, "TestPoint");

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
