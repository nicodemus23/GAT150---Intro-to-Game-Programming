#pragma once
// derives form RenderComponent
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent // specifying something that is inherited that isn's declare as public will default to private
	{
	public:
		void Update(float dt) override; // virtual at the beginning would make it so Sprite could override this component
		void Draw(class Renderer& renderer) override;
	public:
		res_t<Texture> m_texture;
	};
}