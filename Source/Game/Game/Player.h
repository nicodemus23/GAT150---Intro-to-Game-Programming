#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform) :
		Actor{ transform},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 2 * m_turnRate;
	float m_turnRate = .5;
};