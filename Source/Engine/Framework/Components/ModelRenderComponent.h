#pragma once
#include "Framework/RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt) override; // virtual at the beginning would make it so Sprite could override this component
		void Draw(class Renderer& renderer) override;
	public:
		res_t<Model> m_texture;

	};


}