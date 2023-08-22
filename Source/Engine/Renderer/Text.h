#pragma once
#include "Font.h"
#include "Core/Math/Color.h"
#include <string>
#include <memory>


struct SDL_Texture;

namespace kiko
{
	class Renderer;

	class Text // friend of Font class 
	{
	public:
		Text() = default; // default constructor 
		Text(std::shared_ptr<Font> font) : m_font{font} { }
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, const class Transform& transform);

		
	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}