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
