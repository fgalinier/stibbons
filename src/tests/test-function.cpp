#include "../model/agent.h"
#include "../model/breed.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/color.h"
#include "../model/user-function.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace stibbons;
using namespace std;
using namespace CppUnit;

class TestFunction : public TestCase {
	CPPUNIT_TEST_SUITE(TestFunction);
	CPPUNIT_TEST(getParams);
	CPPUNIT_TEST_SUITE_END();

	public :
		Function* f;

		void setUp() {
			f=new UserFunction(nullptr, {"nb", "val"});
		}

		void getParams() {
			cout << "TestFunction::getParams" << endl;
			CPPUNIT_ASSERT (2 == f->getParams().size());
			CPPUNIT_ASSERT ("nb" == f->getParams()[0]);
			CPPUNIT_ASSERT ("val" == f->getParams()[1]);

		}


};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestFunction,"TestFunction");

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

