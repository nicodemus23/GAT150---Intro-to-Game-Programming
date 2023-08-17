#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{	
	class ModelRenderComponent : public RenderComponent
	{
	public:

		CLASS_DECLARATION(ModelRenderComponent);

		bool Initialize() override;

		void Update(float dt) override; // virtual at the beginning would make it so Sprite could override this component
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); } // overriding v function 

	public:
		std::string modelName;
		res_t<Model> m_model;


	};


}