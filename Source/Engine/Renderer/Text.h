#pragma once
#include "Renderer/Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>

namespace kiko
{
	class Text // friend of Font class 
	{
	public:
		Text() = default; // default constructor 
		Text(std::shared_ptr<Font> font) : m_font{font} { }
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);

		
	private:
		std::shared_ptr<Font> m_font;
		struct SDL_Texture* m_texture = nullptr;
	};
}