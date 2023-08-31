#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{

	class Player : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		Player() = default;

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float turnRate = 0;

		// pointer to physics comp
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};

}