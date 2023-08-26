#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace kiko
{
	class SpriteRenderComponent : public RenderComponent //* 
	{
	public:
		CLASS_DECLARATION(SpriteRenderComponent)

		bool Initialize() override;
		void Update(float dt) override; //*
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }//*

		

	public:
		Rect source;
		std::string textureName;
		res_t<Texture> m_texture;
	};
}

//NOTES:
//	class SpriteRenderComponent : public RenderComponent // specifying something that is inherited that isn's declare as public will default to private

//		void Update(float dt) override; // virtual at the beginning would make it so Sprite could override this component


// Gets CircumRadius of Sprite = half the distance of the diagonal  x and y // Length: 1 Vector // Distance = when you have 2 Vectors 
//virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }