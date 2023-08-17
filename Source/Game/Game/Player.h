#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform) :
		Actor{ transform},
		speed{ speed },
		m_turnRate{ turnRate }
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float speed = 0;
	float m_turnRate = 0;

	// pointer to physics comp
	kiko::PhysicsComponent* m_physicsComponent = nullptr;
};