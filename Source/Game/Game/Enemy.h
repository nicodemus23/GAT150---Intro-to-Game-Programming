#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{

	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		Enemy() = default;

	/*	Enemy(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{
			m_fireRate = 2.0f;
			m_fireTimer = m_fireRate;
		}*/

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
		float turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}