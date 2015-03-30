#include "../model/agent.h"
#include "../model/breed.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/color.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace stibbons;
using namespace std;
using namespace CppUnit;

class TestFunction : public TestCase {
	CPPUNIT_TEST_SUITE(TestFunction);
	CPPUNIT_TEST(AjoutArg);
	CPPUNIT_TEST_SUITE_END();

	public :
		Function* f;
		string nombre;
		Tree *t;

		void setUp() {
			cout << "TestFunction::setup" << endl;
			t=new Tree(2,nullptr);
			nombre="nb";
			f=new Function(*t,vector<string>());
}

		void AjoutArg() {
			cout << "TestFunction::AjoutArg" << endl;
			f->setArg(nombre);
			vector<string> vector=f->getArg();
			for (auto i : vector){
				CPPUNIT_ASSERT("nb" == i);
			}

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

