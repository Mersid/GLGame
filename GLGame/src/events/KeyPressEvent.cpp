#include "KeyPressEvent.h"

KeyPressEvent::KeyPressEvent(int key, int scancode, int action, int mods) :
key(key), scancode(scancode), action(action), mods(mods)
{
	sid = "";
}