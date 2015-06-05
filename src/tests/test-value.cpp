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

#include "values.h"

#include "../model/boolean.h"
#include "../model/color.h"
#include "../model/nil.h"
#include "../model/number.h"
#include "../model/string.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestValue : public TestCase {
	CPPUNIT_TEST_SUITE(TestValue);
	CPPUNIT_TEST(checkBoolean);
	CPPUNIT_TEST(checkColor);
	CPPUNIT_TEST(checkNil);
	CPPUNIT_TEST(checkNumber);
	CPPUNIT_TEST(checkString);
	CPPUNIT_TEST_SUITE_END();

	public:
		stibbons::Boolean boolean;
		stibbons::Color color;
		shared_ptr<stibbons::Nil> nil;
		stibbons::Number number;
		stibbons::String string;

		void setUp() {
			nil = stibbons::Nil::getInstance();
		}

		void checkBoolean() {
			cout << "TestValue::checkBoolean" << endl;
			CPPUNIT_ASSERT (stibbons::Type::BOOLEAN == boolean.getType());
		}

		void checkColor() {
			cout << "TestValue::checkColor" << endl;
			CPPUNIT_ASSERT (stibbons::Type::COLOR == color.getType());
		}

		void checkNil() {
			cout << "TestValue::checkNil" << endl;
			CPPUNIT_ASSERT (stibbons::Type::NIL == nil->getType());
		}

		void checkNumber() {
			cout << "TestValue::checkNumber" << endl;
			CPPUNIT_ASSERT (stibbons::Type::NUMBER == number.getType());
		}

		void checkString() {
			cout << "TestValue::checkString" << endl;
			CPPUNIT_ASSERT (stibbons::Type::STRING == string.getType());
		}
};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestValue, "TestValue");

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
