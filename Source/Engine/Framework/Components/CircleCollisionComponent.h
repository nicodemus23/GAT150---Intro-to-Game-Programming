#pragma once
#include "Framework/Components/CollisionComponent.h"


namespace kiko
{
	class CircleCollisionComponent : public CollisionComponent 
	{
	public:
		virtual void Update(float dt) override;

		// this is already in CollisionComponent.h ???? Ask Maple
		virtual bool CheckCollision(CollisionComponent* collision);

		//virtual bool CheckCollision(CollisionComponent);

	};
}