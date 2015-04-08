#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace CppUnit;

Test *suite() {
	auto &registry = TestFactoryRegistry::getRegistry();

	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestAgent"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestBreed"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestColor"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestFunction"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestPoint"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestNumber"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestTable"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestTurtle"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestValue"));
	registry.registerFactory(&TestFactoryRegistry::getRegistry("TestWorld"));

	return registry.makeTest();
}

int main (int argc, char* argv[]) {
	TextUi::TestRunner runner;
	runner.addTest(suite());

	return !runner.run("");
}

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
