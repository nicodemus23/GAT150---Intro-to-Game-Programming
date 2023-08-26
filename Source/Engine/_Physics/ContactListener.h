#pragma once
#include <box2d/include/box2d/box2d.h>

namespace kiko
{
	class ContactListener : public b2ContactListener // contact events
	{
	public:
		void BeginContact(b2Contact* contact) override; // pass in pointer
		void EndContact(b2Contact* contact) override;
	};
}