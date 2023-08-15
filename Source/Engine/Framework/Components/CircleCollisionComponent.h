#pragma once
#include "CollisionComponent.h"


namespace kiko
{

	class CircleCollisionComponent : public CollisionComponent 
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponent)

		virtual void Update(float dt) override;

		// this is already in CollisionComponent.h ???? Ask Maple
		virtual bool CheckCollision(CollisionComponent* collision) override;

		//virtual bool CheckCollision(CollisionComponent);

	};
}