#include "ContactListener.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) // make sure valid data 
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);
			// convert pointers back to Actors
			if (actorA->destroyed || actorB->destroyed) return;

			auto collisionA = actorA->GetComponent<CollisionComponent>();
			if (collisionA)
			{
				//collisionA->OnCollisionEnter(actorB);
			}

			auto collisionB = actorB->GetComponent<CollisionComponent>();
			if (collisionB)
			{
				//collisionB->OnCollisionEnter(actorA);
			}
		}
	}
	void ContactListener::EndContact(b2Contact* contact)
	{

	}
}