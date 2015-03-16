#include "changeable.h"

namespace stibbons {

Changeable::Changeable () : callback(nullptr) {}

void Changeable::onChanged (std::function<void()> callback) {
	this->callback = callback;
}

void Changeable::changed () {
	if (callback)
		callback();
}

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
