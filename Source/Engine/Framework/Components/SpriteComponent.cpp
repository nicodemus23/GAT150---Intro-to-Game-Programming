#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"


namespace kiko
{
	void kiko::SpriteComponent::Update(float dt)
	{

	}

	void kiko::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(),m_owner->m_transform.position.x, m_owner->m_transform.position.y, RadiansToDegrees(m_owner->m_transform.rotation)); //m_texture.get() gets the pointer to m_texture
	}

}
