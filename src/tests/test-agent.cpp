#include "../model/agent.h"
#include "../model/zone.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace stibbons;
using namespace std;
using namespace CppUnit;

class TestAgent : public TestCase {
	CPPUNIT_TEST_SUITE(TestAgent);
	CPPUNIT_TEST(getValuesT);
	CPPUNIT_TEST(getValuesZ);
	CPPUNIT_TEST(changeValueT);
	CPPUNIT_TEST_SUITE_END();

	public :
		stibbons::Turtle* t;
		stibbons::Zone* z;

		void setUp() {
			t=new  stibbons::Turtle(0);
			pair<string,Value*> paire("chasse", new Number(6.0));
			pair<string,Value*> deuxieme("couleur", new String("chat"));
			t->setProperty(paire);
			t->setProperty(deuxieme);

			z=new stibbons::Zone();
			z->setProperty(deuxieme);
		}

		void getValuesT() {
			cout << "TestAgent::getValuesT" << endl;
			auto chasse = t->getProperty("chasse");
			CPPUNIT_ASSERT (Type::NUMBER == chasse->getType());
			auto chasse_reel = dynamic_cast<Number*>( chasse);
			CPPUNIT_ASSERT_EQUAL (6.0, chasse_reel->getValue());
		}

		void changeValueT(){
		cout << "TestAgent::changeValueT" << endl;
		pair<string,Value*> paire("chasse", new Number(7.7));
		t->setProperty(paire);
		unordered_map<string,Value*>::const_iterator search = (t->getProperties()).find ("chasse");
		if (search == (t->getProperties()).end()){
		cout<<"pas trouver"<<endl;
		auto valeur=dynamic_cast<Number*>(search->second);
		CPPUNIT_ASSERT_EQUAL(7.7, valeur->getValue());
		}
		
		}

		void getValuesZ(){
		cout << "TestAgent::getValuesZ" << endl;
		auto couleur = z->getProperty("couleur");
		CPPUNIT_ASSERT (Type::STRING == couleur->getType());
		auto couleur_reel = dynamic_cast<String*> (couleur);
		CPPUNIT_ASSERT ("chat" == couleur_reel->getValue());
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
