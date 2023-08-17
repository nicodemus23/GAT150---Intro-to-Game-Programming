#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"


namespace kiko
{
	CLASS_DEFINITION(SpriteRenderComponent)

	bool SpriteRenderComponent::Initialize()
	{
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer); // !if not empty get the resource

		return true;
	}

	void SpriteRenderComponent::Update(float dt)
	{

	}

	void SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(),m_owner->transform); //m_texture.get() gets the pointer to m_texture
	}

	void SpriteRenderComponent::Read(const json_t& value)
	{
		kiko::Json::Read(value, "textureName", textureName);
	}

}
