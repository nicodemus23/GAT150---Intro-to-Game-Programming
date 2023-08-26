#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{

	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		// no need for constructor - read from JSON

		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}