#pragma once
#include "Framework/Singleton.h"
#include "Box2D/include/box2d/b2_world.h"
#include "Core/Math/Vector2.h"
#include <memory>

#define VEC2_TO_B2VEC2(vec) (*(b2Vec2*)(&vec))
#define B2VEC2_TO_VEC2(vec) (*(kiko::Vector2*)(&vec))

namespace kiko
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		struct RigidBodyData
		{
			float gravityScale = 1;
			float damping = 0;
			float angularDamping = 0;
			bool constrainAngle = false;
			bool isDynamic = true;
		};


		struct CollisionData
		{
			vec2 size;
			float density = 1;
			float friction = 1;
			float restitution = 0.3f;
			bool isTrigger = false;
		};
	public:
		bool Initialize();
		void Update(float dt);
		
		friend class Singleton;
	private:
		PhysicsSystem() = default;
	private:
		std::unique_ptr<b2World> m_world;
	};
}
