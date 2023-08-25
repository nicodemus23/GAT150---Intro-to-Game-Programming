#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon) // to Register in order to Clone() // contains const json_t value Read()
	
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
		kiko::PhysicsComponent* m_physicsComponent = nullptr;

	};
}


