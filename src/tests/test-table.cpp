#include "../model/table.h"
#include "../model/number.h"
#include "../model/string.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace stibbons;
using namespace std;
using namespace CppUnit;

class TestTable : public TestCase {
	CPPUNIT_TEST_SUITE(TestTable);
	CPPUNIT_TEST(append);
	CPPUNIT_TEST(getValues);
	CPPUNIT_TEST(changeValue);
	CPPUNIT_TEST_SUITE_END();

	public :
		TablePtr t;

		void setUp() {
			t = make_shared<Table>();
			pair<string,ValuePtr> paire("chasse", make_shared<Number>(6.0));
			pair<string,ValuePtr> deuxieme("couleur", make_shared<String>("chat"));

			t->setValue(paire);
			t->setValue(deuxieme);
		}

		void append() {
			cout << "TestTable::append" << endl;

			t->append(make_shared<String>("truc"));
			t->append(make_shared<String>("machin"));

			auto truc = t->getValue(0);
			CPPUNIT_ASSERT (Type::STRING == truc->getType());
			auto truc_reel = dynamic_pointer_cast<String>(truc);
			CPPUNIT_ASSERT_EQUAL (string("truc"), truc_reel->getValue());

			auto machin = t->getValue(1);
			CPPUNIT_ASSERT (Type::STRING == machin->getType());
			auto machin_reel = dynamic_pointer_cast<String>(machin);
			CPPUNIT_ASSERT_EQUAL (string("machin"), machin_reel->getValue());
		}

		void getValues() {
			cout << "TestTable::getValues" << endl;

			auto chasse = t->getValue("chasse");
			CPPUNIT_ASSERT (Type::NUMBER == chasse->getType());
			auto chasse_reel = dynamic_pointer_cast<Number>(chasse);
			CPPUNIT_ASSERT_EQUAL (6.0, chasse_reel->getValue());

			auto couleur = t->getValue("couleur");
			CPPUNIT_ASSERT (Type::STRING == couleur->getType());
			auto couleur_reel = dynamic_pointer_cast<String>(couleur);
			CPPUNIT_ASSERT_EQUAL (string("chat"), couleur_reel->getValue());
		}

		void changeValue(){
			cout << "TestTable::changeValue" << endl;

			t->setValue("chasse", make_shared<Number>(7.7));
			auto search = t->getValue("chasse");
			CPPUNIT_ASSERT (Type::NUMBER == search->getType());
			auto search_reel = dynamic_pointer_cast<Number>(search);
			CPPUNIT_ASSERT_EQUAL (7.7, search_reel->getValue());
		}

};

/* enregistrement du nom des test dans le registre */
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestTable, "TestTable");

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
