#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_Image.h"


namespace kiko
{

	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG(" Texture is not initialized, homey\n");
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING -- FINISH!
			WARNING_LOG(" There's all kinds o' crazy going on in Texture.cpp CreateTextureFromSurface\n");
			return false;
		}
		return true;
	}
	vec2 Texture::GetSize()
	{
		// ASSERT texture is not null
		SDL_Point point;

		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture

		SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}

	bool Texture::Create(std::string filename, ...)

	{	// va_list holds the information about variable arguments
		va_list args;

		// va_start enables acces too variadic function arguments
		va_start(args, filename);

		// va_arg access the next variadic function arguments
		Renderer& renderer = va_arg(args, Renderer);

		return Load(filename, renderer);

	}
	
}
