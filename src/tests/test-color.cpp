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

#include "../model/color.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestColor : public TestCase {
	CPPUNIT_TEST_SUITE(TestColor);
	CPPUNIT_TEST(getValues);
	CPPUNIT_TEST(outOfBoundValues);
	CPPUNIT_TEST(longString);
	CPPUNIT_TEST(shortString);
	CPPUNIT_TEST(invalidString);
	CPPUNIT_TEST(toString);
	CPPUNIT_TEST_SUITE_END();

	public:
		stibbons::Color grey;
		stibbons::Color red;
		stibbons::Color green;
		stibbons::Color blue;

		void setUp() {
			grey = stibbons::Color(0.5, 0.5, 0.5);
			red  = stibbons::Color(4.0, -4.0, 0.0);
			green = stibbons::Color("#00FF00");
			blue = stibbons::Color("#00F");
		}

		void getValues() {
			cout << "TestColor::getValues" << endl;
			CPPUNIT_ASSERT_EQUAL (grey.r(), 0.5);
			CPPUNIT_ASSERT_EQUAL (grey.g(), 0.5);
			CPPUNIT_ASSERT_EQUAL (grey.b(), 0.5);
		}

		void outOfBoundValues() {
			cout << "TestColor::outOfBoundValues" << endl;
			CPPUNIT_ASSERT_EQUAL (red.r(), 1.0);
			CPPUNIT_ASSERT_EQUAL (red.g(), 0.0);
			CPPUNIT_ASSERT_EQUAL (red.b(), 0.0);
		}

		void longString() {
			cout << "TestColor::longString" << endl;
			CPPUNIT_ASSERT_EQUAL (green.r(), 0.0);
			CPPUNIT_ASSERT_EQUAL (green.g(), 1.0);
			CPPUNIT_ASSERT_EQUAL (green.b(), 0.0);
		}

		void shortString() {
			cout << "TestColor::shortString" << endl;
			CPPUNIT_ASSERT_EQUAL (blue.r(), 0.0);
			CPPUNIT_ASSERT_EQUAL (blue.g(), 0.0);
			CPPUNIT_ASSERT_EQUAL (blue.b(), 1.0);
		}

		void invalidString() {
			cout << "TestColor::invalidString" << endl;
			CPPUNIT_ASSERT_THROW (stibbons::Color("Not a color"), domain_error);
		}

		void toString() {
			cout << "TestColor::toString" << endl;
			CPPUNIT_ASSERT_EQUAL (string("#7f7f7f"), grey.toString());
			CPPUNIT_ASSERT_EQUAL (string("#ff0000"), red.toString());
			CPPUNIT_ASSERT_EQUAL (string("#00ff00"), green.toString());
			CPPUNIT_ASSERT_EQUAL (string("#0000ff"), blue.toString());
		}
};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestColor, "TestColor");

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
