#include "../model/agent.h"
#include "../model/zone.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace CppUnit;

class TestAgent : public TestCase {
	CPPUNIT_TEST_SUITE(TestAgent);
	CPPUNIT_TEST(getValues);
	CPPUNIT_TEST(changeValue);
	CPPUNIT_TEST_SUITE_END();

	public :
		stibbons::Turtle* t;
		//stibbons::Zone z;

		void setUp() {
			t=new  stibbons::Turtle(0);
			pair<string,stibbons::Value*> paire("chasse", new stibbons::Number(6.0));
			pair<string,stibbons::Value*> deuxieme("couleur", new stibbons::String("chat"));
			t->setProperty(paire);
			t->setProperty(deuxieme);
		}

		void getValues() {
			cout << "TestAgent::getValues" << endl;
			auto chasse = t->getProperty("chasse");
			CPPUNIT_ASSERT (stibbons::Type::NUMBER == chasse->getType());
			//auto chasse_reel = (stibbons::Number *) chasse;
			//CPPUNIT_ASSERT_EQUAL (6.0, chasse_reel->getValue());
		}

		void changeValue(){
		cout << "TestAgent::changeValue" << endl;
		pair<string,stibbons::Value*> paire("chasse", new stibbons::Number(7.7));
		t->setProperty(paire);
		unordered_map<string,stibbons::Value*>::const_iterator search = (t->getProperties()).find ("chasse");
		if (search == (t->getProperties()).end()){
		cout<<"pas trouver"<<endl;
		//auto valeur=(stibbons::Number)search->second;
		//CPPUNIT_ASSERT_EQUAL(7.7, valeur);
		}
		
		}

};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestAgent, "TestAgent");

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
