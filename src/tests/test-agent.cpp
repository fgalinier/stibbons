#include "../model/agent.h"
#include "../model/zone.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/color.h"

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
	CPPUNIT_TEST(getValuesW);
	CPPUNIT_TEST_SUITE_END();

	public :
		TurtlePtr t;
		ZonePtr z;
		WorldPtr w;

		void setUp() {
			pair<string,ValuePtr> paire("chasse", make_shared<Number>(6.0));
			pair<string,ValuePtr> deuxieme("couleur", make_shared<String>("chat"));
			pair<string,ValuePtr> troisieme("tortue", make_shared<String>("bleu"));
			pair<string,ValuePtr> quatrieme("color", make_shared<Color>());

			auto worldSize = Size(2);
			worldSize.setValue(0, 10);
			worldSize.setValue(1, 10);
			auto zoneSize = Size(2);
			zoneSize.setValue(0, 10);
			zoneSize.setValue(1, 10);
			w=World::construct(worldSize, zoneSize);
			w->setProperty(troisieme);
			w->setProperty(quatrieme);

			z = Zone::construct(w);
			z->setProperty(deuxieme);

			t=Turtle::construct(w, 0);
			t->setProperty(paire);
			t->setProperty(deuxieme);
		}

		void getValuesT() {
			cout << "TestAgent::getValuesT" << endl;
			auto chasse = t->getProperty("chasse");
			CPPUNIT_ASSERT (Type::NUMBER == chasse->getType());
			auto chasse_reel = dynamic_pointer_cast<Number>( chasse);
			CPPUNIT_ASSERT_EQUAL (6.0, chasse_reel->getValue());
		}

		void changeValueT(){
		cout << "TestAgent::changeValueT" << endl;
		pair<string,ValuePtr> paire("chasse", make_shared<Number>(7.7));
		t->setProperty(paire);

		auto search = t->getProperty(paire.first);
		CPPUNIT_ASSERT (
			search->getType() == Type::NUMBER &&
			dynamic_pointer_cast<Number>(search)->getValue() == 7.7
		);
		}

		void getValuesZ(){
		cout << "TestAgent::getValuesZ" << endl;
		auto couleur = z->getProperty("couleur");
		CPPUNIT_ASSERT (Type::STRING == couleur->getType());
		auto couleur_reel = dynamic_pointer_cast<String> (couleur);
		CPPUNIT_ASSERT ("chat" == couleur_reel->getValue());
		}

		void getValuesW(){
		cout << "TestAgent::getValuesW" << endl;
		auto couleur = w->getProperty("color");
		CPPUNIT_ASSERT (Type::COLOR == couleur->getType());
		auto tortue = w->getProperty("tortue");
		auto tt = dynamic_pointer_cast<String> (tortue);
		CPPUNIT_ASSERT ("bleu" == tt->getValue());
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
