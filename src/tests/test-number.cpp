#include "../model/number.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestNumber : public TestCase {
	CPPUNIT_TEST_SUITE(TestNumber);
	CPPUNIT_TEST(getValue);
	CPPUNIT_TEST_SUITE_END();

	public:
		stibbons::Number two;

		void setUp() {
			two = stibbons::Number(2.0);
		}

		void getValue() {
			cout << "TestNumber::getValue" << endl;
			CPPUNIT_ASSERT_EQUAL (2.0, two.getValue());
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
