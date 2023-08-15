#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"


namespace kiko
{
	CLASS_DEFINITION(SpriteRenderComponent)

	void SpriteRenderComponent::Update(float dt)
	{

	}

	void SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(),m_owner->m_transform); //m_texture.get() gets the pointer to m_texture
		//renderer.DrawTexture(m_texture.get(),m_owner->m_transform.position.x, m_owner->m_transform.position.y, RadiansToDegrees(m_owner->m_transform.rotation)); //m_texture.get() gets the pointer to m_texture
	}

}
