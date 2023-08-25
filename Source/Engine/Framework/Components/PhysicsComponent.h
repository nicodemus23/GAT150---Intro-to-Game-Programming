#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace kiko
{

	class PhysicsComponent : public Component
	{
	public:

		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0; // not pure virtual since initializing with value 

		virtual void SetVelocity(const vec2& velocity) { this->velocity = velocity; }

	public:
		vec2 velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;

	};
}