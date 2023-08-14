#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent //* 
	{
	public:
		void Update(float dt) override; //*
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }//*

	public:
		res_t<Texture> m_texture;
	};
}

//	class SpriteComponent : public RenderComponent // specifying something that is inherited that isn's declare as public will default to private

//		void Update(float dt) override; // virtual at the beginning would make it so Sprite could override this component


// Gets CircumRadius of Sprite = half the distance of the diagonal  x and y // Length: 1 Vector // Distance = when you have 2 Vectors 
//virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }