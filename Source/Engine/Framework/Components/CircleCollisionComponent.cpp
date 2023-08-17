#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(CircleCollisionComponent)

	void CircleCollisionComponent::Update(float dt)
	{

	}

	bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}

	// will cause linker errors if you don't call when declaring a virtual function
	void CircleCollisionComponent::Read(const json_t& value)
	{
		//
	}

}


