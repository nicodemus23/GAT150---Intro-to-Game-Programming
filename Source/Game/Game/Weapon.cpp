#include "Weapon.h"
#include "Renderer/Renderer.h"


void Weapon::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());
}

void Weapon::OnCollision(Actor* other)
{  // if we collide with something, just say it's destroyed 
	if (other->m_tag != m_tag) // if the weapon's tag is NOT equal to my tag, destroy ourselves // we were hit 
	{
		m_destroyed = true;
	}
}


