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

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag)//*
		{
			destroyed = true;
		}
	}

	// speed
	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value); // reads in type, name, prototype, tag, lifespan, transform... then speed. 

		READ_DATA(value, speed);
	}
}



// if we collide with something, just say it's destroyed 
//if (other->tag != tag) // if the Weapon's tag is NOT equal to my tag, destroy ourselves // we were hit 


