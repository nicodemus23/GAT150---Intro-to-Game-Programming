#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent < kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale * 0.75f;
			}
		}
		//debug: During Initialization
		std::cout << "Rocket collision radius: " << collisionComponent << std::endl;

		return true;

		
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation); // calculate rocket rotation with forward vector
		transform.position += forward * speed * kiko::g_time.GetDeltaTime(); // forward vector * speed * Delta time 
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth()); // wrap x
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight()); // wrap y

		// debug: rocket movement during update
		std::cout << "Rocket position: (" << transform.position.x << ", " << transform.position.y << ")" << std::endl;
		std::cout << "Forward vector: (" << forward.x << ", " << forward.y << ")" << std::endl;
		std::cout << "Rocket speed: " << speed << std::endl;
		std::cout << "Delta time: " << kiko::g_time.GetDeltaTime() << std::endl;
	}

	void Weapon::OnCollision(Actor* other)
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


