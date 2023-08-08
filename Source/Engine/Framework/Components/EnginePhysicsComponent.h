#pragma once
#include "PhysicsComponent.h"


namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		Update(float dt) = 0.5f;

	};

}