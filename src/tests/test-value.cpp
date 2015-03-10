#include "values.h"

#include "../model/color.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestValue : public TestCase {
	CPPUNIT_TEST_SUITE(TestValue);
	CPPUNIT_TEST(checkColor);
	CPPUNIT_TEST_SUITE_END();

	public:
		stibbons::Color color;

		void checkColor() {
			cout << "TestValue::checkColor" << endl;
			CPPUNIT_ASSERT (stibbons::Type::COLOR == color.getType());
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
