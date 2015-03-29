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
/* le Function f ne marche pas : pas de Function() définit, j'ai crée un cas par défaut, pour quoi ca ne marche pas ? à voir avec adrien */
		Function* f;
		Number* i=new Number();
		Tree *t;



		void setUp() {
			cout << "TestFunction::setup" << endl;
			t=new Tree(2,nullptr);
			i->setValue(2.0);
			f=new Function(vector<Value*>(),*t);
}

		void AjoutArg() {
			cout << "TestFunction::AjoutArg" << endl;
			f->setArg(i);
			vector<Value*> vector=f->getArg();
			for (auto i : vector){
				CPPUNIT_ASSERT (Type::NUMBER == i->getType());
				auto reel = dynamic_cast<Number*>(i);
				CPPUNIT_ASSERT_EQUAL (2.0,reel->getValue());
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

