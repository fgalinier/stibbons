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
			auto worldSize = Size(2);
			worldSize.setValue(0, 10);
			worldSize.setValue(1, 10);
			auto zoneSize = Size(2);
			zoneSize.setValue(0, 10);
			zoneSize.setValue(1, 10);
			auto warp = vector<bool>();
			warp.push_back(false);
			warp.push_back(false);
			w=World::construct(worldSize, zoneSize, warp);
			w->setProperty("tortue", make_shared<String>("bleu"));
			w->setProperty("color", make_shared<Color>());

			z = Zone::construct(w);
			z->setProperty("couleur", make_shared<String>("chat"));

			t=Turtle::construct(w, 0);
			t->setProperty("chasse", make_shared<Number>(6.0));
			t->setProperty("couleur", make_shared<String>("chat"));
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
		t->setProperty("chasse", make_shared<Number>(7.7));

		auto search = t->getProperty("chasse");
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
