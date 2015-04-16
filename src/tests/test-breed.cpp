#include "values.h"

#include "../model/breed.h"
#include "../model/boolean.h"
#include "../model/color.h"
#include "../model/nil.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/user-function.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;
using namespace stibbons;

class TestBreed : public TestCase {
	CPPUNIT_TEST_SUITE(TestBreed);
	CPPUNIT_TEST(ajout);
	CPPUNIT_TEST_SUITE_END();

	public:
		FunctionPtr f;
		BreedPtr breed;

		void setUp() {
			cout << "TestBreed::" << endl;
			f=make_shared<UserFunction>(nullptr);
			breed=make_shared<Breed>(f);
		}

		void ajout() {
			cout << "TestBreed::ajout" << endl;
			TurtlePtr t=breed->createTurtle();
			WorldPtr w=breed->getWorld();
			if (w != nullptr)
			CPPUNIT_ASSERT(w->getType() == Type::WORLD);
			CPPUNIT_ASSERT(t->getType() == Type::TURTLE);
		}
};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestBreed, "TestBreed");

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
