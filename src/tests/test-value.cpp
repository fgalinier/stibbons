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
		stibbons::Nil& nil = stibbons::Nil::getInstance();
		stibbons::Number number;
		stibbons::String string;

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
			CPPUNIT_ASSERT (stibbons::Type::NIL == nil.getType());
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
