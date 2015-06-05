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

#include "../model/number.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestNumber : public TestCase {
	CPPUNIT_TEST_SUITE(TestNumber);
	CPPUNIT_TEST(getValue);
	CPPUNIT_TEST(compare);
	CPPUNIT_TEST_SUITE_END();

	public:
		stibbons::NumberPtr two;
		stibbons::NumberPtr three;

		void setUp() {
			two = make_shared<stibbons::Number>(2.0);
			three = make_shared<stibbons::Number>(3.0);
		}

		void getValue() {
			cout << "TestNumber::getValue" << endl;
			CPPUNIT_ASSERT_EQUAL (2.0, two->getValue());
		}

		void compare() {
			cout << "TestNumber::compare" << endl;
			CPPUNIT_ASSERT (!two->isEqual(three));
			CPPUNIT_ASSERT (two->isDifferent(three));
			CPPUNIT_ASSERT (two->isLower(three));
			CPPUNIT_ASSERT (!two->isGreater(three));
			CPPUNIT_ASSERT (two->isLowerOrEqual(three));
			CPPUNIT_ASSERT (!two->isGreaterOrEqual(three));
		}
};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestNumber, "TestNumber");

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
