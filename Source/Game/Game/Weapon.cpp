#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent < kiko::CollisionComponent>();
		if (collisionComponent)
		{
			
		}
		//debug: During Initialization
		std::cout << "Rocket collision radius: " << collisionComponent << std::endl;

		return true;

		
	}

	void Weapon::Update(float dt)
	{


		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollisionEnter(Actor* other)
	{
		if (other->tag != tag)//*
		{
			destroyed = true;
		}
		
		//debug: Rocket on collision
		std::cout << "Rocket collided with actor tag: " << other->tag << std::endl;
	}

	// speed
	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value); // reads in type, name, prototype, tag, lifespan, transform... then speed. 

		READ_DATA(value, speed);

		//debug: after reading from Json
		std::cout << "Rocket speed: " << speed << std::endl;
	}
}



// if we collide with something, just say it's destroyed 
//if (other->tag != tag) // if the Weapon's tag is NOT equal to my tag, destroy ourselves // we were hit 


